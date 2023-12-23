#include "AIDeath.h"

#include <SDL_log.h>

void AIDeath::Update(float deltaTime)
{
	SDL_Log("[INFO] Updating %s state.", GetName());
}

void AIDeath::OnEnter()
{
	SDL_Log("[INFO] Entering %s state.", GetName());
}

void AIDeath::OnExit()
{
	SDL_Log("[INFO] Exiting %s state.", GetName());
}
