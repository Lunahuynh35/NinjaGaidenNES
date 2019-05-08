#include "TextureCollection.h"
#include "AnimationCollection.h"
#include "Animation.h"
#include "Sprite.h"
#include "helperFunction.h"
#include "MainCharacter.h"
#include "IdleState.h"
#include "MoveState.h"
#include "DuckState.h"
#include "JumpState.h"
#include "StandAtkState.h"
#include "DuckAtkState.h"
#include "BoundBox.h"
#include "GameWorld.h"
#include <sstream>

LPMAINCHAR MainCharacter::instance = NULL;
IdleState BaseState::idling;
MoveState BaseState::moving;
DuckState BaseState::ducking;
JumpState BaseState::jumping;
StandAtkState BaseState::standatking;
DuckAtkState BaseState::duckatking;

MainCharacter::MainCharacter()
{
	setState(&BaseState::idling);
}

MainCharacter::~MainCharacter()
{
	delete animations;
}

LPMAINCHAR MainCharacter::getInstance()
{
	if (instance == NULL)
		instance = new MainCharacter();
	return instance;
}

void MainCharacter::loadResource()
{
	LPDIRECT3DTEXTURE9 texture = TextureCollection::getInstance()->getTexture(MAINCHARACTER_TEXTUREID);
	std::vector<std::string> textureInfoLines = getAllLineInTextFile(TEXTURE_INFO_FILE);
	animations = new AnimationCollection();
	LPANIMATION animation;
	for (int i = 2; i < textureInfoLines.size(); i += 2)
	{
		int id, left, top, right, bot, centerX, centerY;
		std::stringstream iss(textureInfoLines[i]);
		iss >> id;
		iss >> left;
		iss >> top; 
		iss >> right;
		iss >> bot;
		iss >> centerX;
		iss >> centerY;
		animation = animations->getAnimation(id);
		if (animation == NULL)
		{
			animation = new Animation(100);
			animations->addAnimation(id, animation);
		}

		LPSPRITE sprite = new Sprite(texture, top, left, right, bot, centerX, centerY);
		animation->addFrameSprite(sprite);
	}
}

void MainCharacter::handleKeyInput(bool keyStates[])
{
	state->handleKeyInput(keyStates);
}

void MainCharacter::render(D3DXVECTOR2 cam_wP)
{
	bool flipX = direction == 1 ? false : true;
	if (state == &BaseState::idling)
	{
		animations->getAnimation(IDLE_ANI_ID)->setTransform(flipX, false, D3DXVECTOR2(1, 1));
		animations->getAnimation(IDLE_ANI_ID)->render(position, cam_wP);
	}
	else if (state == &BaseState::moving)
	{
		animations->getAnimation(MOVE_ANI_ID)->setTransform(flipX, false, D3DXVECTOR2(1, 1));
		animations->getAnimation(MOVE_ANI_ID)->render(position, cam_wP);
	}
	else if (state == &BaseState::ducking)
	{
		animations->getAnimation(DUCK_ANI_ID)->setTransform(flipX, false, D3DXVECTOR2(1, 1));
		animations->getAnimation(DUCK_ANI_ID)->render(position, cam_wP);
	}
	else if (state == &BaseState::jumping)
	{
		animations->getAnimation(JUMP_ANI_ID)->setTransform(flipX, false, D3DXVECTOR2(1, 1));
		animations->getAnimation(JUMP_ANI_ID)->render(position, cam_wP); 
	}
	else if (state == &BaseState::standatking)
	{
		animations->getAnimation(STANDATK_ANI_ID)->setTransform(flipX, false, D3DXVECTOR2(1, 1));
		animations->getAnimation(STANDATK_ANI_ID)->render(position, cam_wP);
	}
	else if (state == &BaseState::duckatking)
	{
		animations->getAnimation(DUCKATK_ANI_ID)->setTransform(flipX, false, D3DXVECTOR2(1, 1));
		animations->getAnimation(DUCKATK_ANI_ID)->render(position, cam_wP);
	}
}

void MainCharacter::updateAfterDeltaTime(float deltaT)
{
	state->updateAfterDeltaTime(deltaT);
}


void MainCharacter::setState(LPBASESTATE newstate)
{
	state = newstate;
}

void MainCharacter::setDirection(int direction)
{
	if (direction == 1 || direction == -1)
		this->direction = direction;
	else
		this->direction = 1;
}

BoundBox MainCharacter::getBoundBox(float dt)
{
	return BoundBox();
}
