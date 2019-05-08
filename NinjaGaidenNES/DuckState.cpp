#include "DuckState.h"
#include "MoveState.h"
#include "IdleState.h"
#include "DuckAtkState.h"
#include <dinput.h>

void DuckState::handleKeyInput(bool keyStates[])
{
	LPMAINCHAR mainChar = MainCharacter::getInstance();
	if (keyStates[DIK_SPACE])
	{
		mainChar->setState(&BaseState::duckatking);
		mainChar->setVelocity(0, 0);
	}

	if (keyStates[DIK_LEFT] && !keyStates[DIK_RIGHT])
	{
		mainChar->setDirection(-1);
	}
	else if (keyStates[DIK_RIGHT] && !keyStates[DIK_LEFT])
	{
		mainChar->setDirection(1);
	}

	if (!keyStates[DIK_DOWN])
		mainChar->setState(&BaseState::idling);

}

void DuckState::updateAfterDeltaTime(float deltaT)
{
}
