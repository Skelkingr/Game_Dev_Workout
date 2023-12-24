#include "AIPatrol.h"

#include <SDL_log.h>

void AIPatrol::Update(float deltaTime)
{
	SDL_Log("[INFO] Updating %s state.", GetName());

	bool dead = true;
	if (dead)
	{
		mOwner->ChangeState("Death");
	}
}

void AIPatrol::OnEnter()
{
	SDL_Log("[INFO] Entering %s state.", GetName());
}

void AIPatrol::OnExit()
{
	SDL_Log("[INFO] Exiting %s state.", GetName());
}
