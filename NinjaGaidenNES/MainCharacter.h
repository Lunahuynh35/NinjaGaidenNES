#pragma once

#define MAINCHARACTER_TEXTUREID 0004
#define IDLE_ANI_ID 000
#define DUCK_ANI_ID 001
#define MOVE_ANI_ID 002
#define STANDATK_ANI_ID 003
#define DUCKATK_ANI_ID 004
#define JUMP_ANI_ID 005
#define TEXTURE_INFO_FILE "Resource/Sprite/MainCharacter.txt"
#define MOVE_SPEED 75
#define FALL_SPEED 450
#define JUMP_SPEED 200
#define ATK_TIME 0.35f

class MainCharacter;
typedef class MainCharacter * LPMAINCHAR;
class AnimationCollection;
typedef class AnimationCollection * LPANIMATIONS;
class BaseState;
typedef class BaseState * LPBASESTATE;
class IdleState;
class MoveState;
class DuckState;
class JumpState;
class StandAtkState;
class DuckAtkState;

#include "InteractiveObject.h"

class MainCharacter : public InteractiveObject
{
private:
	static LPMAINCHAR instance;

	int direction;
	LPANIMATIONS animations;
	LPBASESTATE state;
	MainCharacter();
	
public:
	~MainCharacter();
	static LPMAINCHAR getInstance();
	void setState(LPBASESTATE newstate);
	void setDirection(int direction);

	void loadResource();
	void handleKeyInput(bool keyStates[]);
	void render(D3DXVECTOR2 cam_wP);
	void updateAfterDeltaTime(float deltaT);
	
	BoundBox getBoundBox(float dt);
};

class BaseState
{
public:
	static IdleState idling;
	static MoveState moving;
	static DuckState ducking;
	static JumpState jumping;
	static StandAtkState standatking;
	static DuckAtkState duckatking;

	virtual void handleKeyInput(bool keyStates[]) = 0;
	virtual void updateAfterDeltaTime(float deltaT) = 0;
};