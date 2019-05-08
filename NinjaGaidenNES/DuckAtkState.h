#pragma once

class DuckAtkState;

#include "MainCharacter.h"

class DuckAtkState : public BaseState
{
private:
	float atkTime = ATK_TIME;

public:
	void handleKeyInput(bool keyStates[]);
	void updateAfterDeltaTime(float deltaT);
};