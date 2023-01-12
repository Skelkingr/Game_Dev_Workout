#pragma once

#include "Actor.h"

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void ProcessInput(const uint8_t* keyState);

	class Actor* GetOwner() const { return this->mOwner; }
	int GetUpdateOrder() const { return this->mUpdateOrder; }
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};
