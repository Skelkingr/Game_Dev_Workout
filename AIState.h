#pragma once

class AIState
{
public:
	AIState() = delete;
	AIState(class AIComponent* owner) : mOwner(owner) {}

	virtual void Update(float deltatime) = 0;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;

	virtual const char* GetName() const = 0;
protected:
	class AIComponent* mOwner;
};

