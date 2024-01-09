#pragma once

#include <cstdint>

class Component
{
public:
	Component() = delete;
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void ProcessInput(const uint8_t* keys);

	class Actor* GetOwner() const { return mOwner; }
	int GetUpdateOrder() const { return mUpdateOrder; }

	virtual void OnUpdateWorldTransform();
protected:
	class Actor* mOwner;
	int mUpdateOrder;
};
