#include "JumpState.h"
#include "IdleState.h"
#include "StandAtkState.h"
#include <dinput.h>

void JumpState::handleKeyInput(bool keyStates[])
{
	LPMAINCHAR mainChar = MainCharacter::getInstance();
	D3DXVECTOR2 velocity = mainChar->getVelocity();
	if (keyStates[DIK_LEFT])
	{
		mainChar->setDirection(-1);
		mainChar->setVelocity(-MOVE_SPEED, velocity.y);
	}
	else if (keyStates[DIK_RIGHT])
	{
		mainChar->setDirection(1);
		mainChar->setVelocity(MOVE_SPEED, velocity.y);
	}
	else
	{
		mainChar->setVelocity(0, velocity.y);
	}

	if (keyStates[DIK_SPACE])
	{
		mainChar->setState(&BaseState::standatking);
	}
}

void JumpState::updateAfterDeltaTime(float deltaT)
{
	LPMAINCHAR mainChar = MainCharacter::getInstance();
	
	D3DXVECTOR2 velocity = mainChar->getVelocity();
	velocity += D3DXVECTOR2(0, -FALL_SPEED) * deltaT;
	mainChar->setVelocity(velocity.x, velocity.y);

	D3DXVECTOR2 position = mainChar->getPosition() + velocity * deltaT;

	if (position.y < 40)
	{
		mainChar->setVelocity(velocity.x, 0);
		mainChar->setState(&BaseState::idling);
		position.y = 40;
	}
	mainChar->setPosition(position.x, position.y);
}
