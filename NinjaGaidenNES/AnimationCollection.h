#pragma once

class AnimationCollection;
typedef class AnimationCollection * LPANIMATIONS;
class Animation;
typedef class Animation * LPANIMATION;

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <unordered_map>

class AnimationCollection
{
private:
	std::vector<int> ids;
	std::unordered_map<int, LPANIMATION> animationCollection;

public:
	AnimationCollection() {};
	~AnimationCollection();
	void addAnimation(int id, LPANIMATION ani);
	LPANIMATION getAnimation(int id);
};