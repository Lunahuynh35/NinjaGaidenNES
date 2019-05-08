#pragma once

class IdleState;

#include "MainCharacter.h"

class IdleState : public BaseState
{
	void handleKeyInput(bool keyStates[]);
	void updateAfterDeltaTime(float deltaT);
};
