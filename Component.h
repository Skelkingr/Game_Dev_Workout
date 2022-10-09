#pragma once

#include "Actor.h"

class Component
{
public:
	Component(Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime) = 0;

	Actor* GetOwner() const { return this->mOwner; }
	int GetUpdateOrder() const { return this->mUpdateOrder; }
protected:
	Actor* mOwner;
	int mUpdateOrder;
};
