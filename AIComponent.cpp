#include "AIComponent.h"

#include <SDL_log.h>

void AIComponent::Update(float deltaTime)
{
	if (mCurrentState)
	{
		mCurrentState->Update(deltaTime);
	}
}

void AIComponent::RegisterState(AIState* state)
{
	mStateMap.emplace(state->GetName(), state);
}

void AIComponent::ChangeState(const std::string& name)
{
	if (mCurrentState)
	{
		mCurrentState->OnExit();
	}

	auto iter = mStateMap.find(name);
	if (iter != mStateMap.end())
	{
		mCurrentState = iter->second;
		mCurrentState->OnEnter();
	}
	else
	{
		SDL_Log("[ERROR] Could not find AIState %s in state map.", name.c_str());
		mCurrentState = nullptr;
	}
}
