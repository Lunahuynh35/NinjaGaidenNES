#pragma once

class JumpState;

#include "MainCharacter.h"

class JumpState : public BaseState
{
	void handleKeyInput(bool keyStates[]);
	void updateAfterDeltaTime(float deltaT);
};