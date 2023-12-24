#include "AIAttack.h"

#include <SDL_log.h>

void AIAttack::Update(float deltaTime)
{
	SDL_Log("[INFO] Updating %s state.", GetName());
}

void AIAttack::OnEnter()
{
	SDL_Log("[INFO] Entering %s state.", GetName());
}

void AIAttack::OnExit()
{
	SDL_Log("[INFO] Exiting %s state.", GetName());
}
