#pragma once

#include "AIState.h"

class AIAttack : public AIState
{
public:
	AIAttack() = delete;
	AIAttack(AIComponent* owner) : AIState(owner) {}

	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;

	const char* GetName() const override { return "Attack"; }
};

