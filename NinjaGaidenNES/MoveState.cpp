#include "MoveState.h"
#include "IdleState.h"
#include "DuckState.h"
#include "JumpState.h"
#include "StandAtkState.h"
#include "DuckAtkState.h"
#include <dinput.h>


void MoveState::handleKeyInput(bool keyStates[])
{
	LPMAINCHAR mainChar = MainCharacter::getInstance();

	if (keyStates[DIK_LEFT] && !keyStates[DIK_RIGHT])
	{
		mainChar->setDirection(-1);
		mainChar->setVelocity(-MOVE_SPEED, 0);
	}
	else if (keyStates[DIK_RIGHT] && !keyStates[DIK_LEFT])
	{
		mainChar->setDirection(1);
		mainChar->setVelocity(MOVE_SPEED, 0);
	}
	else
	{
		mainChar->setState(&BaseState::idling);
		mainChar->setVelocity(0, 0);
	}

	if (keyStates[DIK_DOWN])
	{
		mainChar->setState(&BaseState::ducking);
		mainChar->setVelocity(0, 0);
	}

	if (keyStates[DIK_SPACE])
	{
		mainChar->setState(&BaseState::standatking);
		mainChar->setVelocity(0, 0);
	}

	if (keyStates[DIK_UP])
	{
		D3DXVECTOR2 velocity = mainChar->getVelocity();
		mainChar->setVelocity(velocity.x, JUMP_SPEED);
		mainChar->setState(&BaseState::jumping);
	}

}

void MoveState::updateAfterDeltaTime(float deltaT)
{
	LPMAINCHAR mainChar = MainCharacter::getInstance();
	D3DXVECTOR2 position = mainChar->getPosition() + mainChar->getVelocity() * deltaT;
	mainChar->setPosition(position.x, position.y);
}
