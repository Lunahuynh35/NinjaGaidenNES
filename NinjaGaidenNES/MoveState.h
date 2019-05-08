#pragma once

class MoveState;

#include "MainCharacter.h"

class MoveState : public BaseState
{
	void handleKeyInput(bool keyStates[]);
	void updateAfterDeltaTime(float deltaT);
};