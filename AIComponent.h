#pragma once

#include "Actor.h"
#include "AIState.h"
#include "Component.h"

#include <string>
#include <unordered_map>

class AIComponent : public Component 
{
public:
	AIComponent() = delete;
	AIComponent(Actor* owner) : Component(owner) {}

	void Update(float deltaTime) override;
	void ChangeState(const std::string& name);

	void RegisterState(AIState* state);
private:
	std::unordered_map<std::string, AIState*> mStateMap;
	AIState* mCurrentState;
};

