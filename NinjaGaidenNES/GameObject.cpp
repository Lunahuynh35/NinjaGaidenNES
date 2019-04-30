#include "GameObject.h"

void GameObject::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void GameObject::setVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void GameObject::setSize(float x, float y)
{
	size.x = x;
	size.y = y;
}

D3DXVECTOR2 GameObject::getPosition()
{
	return position;
}

D3DXVECTOR2 GameObject::getVelocity()
{
	return velocity;
}

D3DXVECTOR2 GameObject::getSize()
{
	return size;
}