#include "AnimationCollection.h"
#include "helperFunction.h"

AnimationCollection::~AnimationCollection()
{
	for (unsigned int i = 0; i < ids.size(); i++)
		delete animationCollection[ids[i]];
}

void AnimationCollection::addAnimation(int id, LPANIMATION ani)
{
	for (unsigned int i = 0; i < ids.size(); i++)
		if (id == ids[i])
		{
			showBug((wchar_t*)L"[ERROR]: Animation ID \"%d\" existed\n", id);
			return;
		}
	ids.push_back(id);
	animationCollection[id] = ani;
}

LPANIMATION AnimationCollection::getAnimation(int id)
{
	for (unsigned int i = 0; i < ids.size(); i++)
		if (id == ids[i])
			return animationCollection[id];
	showBug((wchar_t*)L"[ERROR] Animation collection doesn't have ID: ""%d""\n", id);
	return NULL;
}
