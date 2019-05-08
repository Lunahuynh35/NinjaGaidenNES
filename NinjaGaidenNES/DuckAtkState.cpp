#include "DuckAtkState.h"
#include "DuckState.h"
#include "IdleState.h"

void DuckAtkState::handleKeyInput(bool keyStates[])
{
}

void DuckAtkState::updateAfterDeltaTime(float deltaT)
{
	LPMAINCHAR mainChar = MainCharacter::getInstance();
	if (atkTime <= 0)
	{
		mainChar->setState(&BaseState::ducking);
		atkTime = ATK_TIME;
	}
	atkTime -= deltaT;
}
