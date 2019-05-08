#pragma once

class DuckState;

#include "MainCharacter.h"

class DuckState : public BaseState
{
	void handleKeyInput(bool keyStates[]);
	void updateAfterDeltaTime(float deltaT);
};