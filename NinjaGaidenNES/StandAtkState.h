#pragma once

class StandAtkState;

#include "MainCharacter.h"	

class StandAtkState : public BaseState
{
private:
	float atkTime = ATK_TIME;

public:
	void handleKeyInput(bool keyStates[]);
	void updateAfterDeltaTime(float deltaT);
};