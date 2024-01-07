#pragma once

#include "Actor.h"
#include "InputSystem.h"

class Component
{
public:
	Component();
	Component(Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void ProcessInput(const InputState& state);

	Actor* GetOwner() const { return this->mOwner; }
	int GetUpdateOrder() const { return this->mUpdateOrder; }

	virtual void OnUpdateWorldTransform();
protected:
	Actor* mOwner;
	int mUpdateOrder;
};
