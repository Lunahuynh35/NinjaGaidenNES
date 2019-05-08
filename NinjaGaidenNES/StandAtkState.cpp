#include "IdleState.h"
#include "JumpState.h"
#include "StandAtkState.h"

void StandAtkState::handleKeyInput(bool keyStates[])
{
}

void StandAtkState::updateAfterDeltaTime(float deltaT)
{
	LPMAINCHAR mainChar = MainCharacter::getInstance();

	D3DXVECTOR2 velocity = mainChar->getVelocity();
	velocity += D3DXVECTOR2(0, -FALL_SPEED) * deltaT;
	mainChar->setVelocity(velocity.x, velocity.y);

	D3DXVECTOR2 position = mainChar->getPosition() + velocity * deltaT;

	if (position.y < 40)
	{
		mainChar->setVelocity(0, 0);
		position.y = 40;
	}
	mainChar->setPosition(position.x, position.y);

	if (atkTime <= 0)
	{
		if (position.y > 40)
			mainChar->setState(&BaseState::jumping);
		else
			mainChar->setState(&BaseState::idling);
		atkTime = ATK_TIME;
	}
	atkTime -= deltaT;
}
