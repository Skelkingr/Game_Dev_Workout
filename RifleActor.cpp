#include "RifleActor.h"

#include "Actor.h"
#include "FPSActor.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Renderer.h"


RifleActor::RifleActor(Game* game)
	:
	Actor(game)
{
	SetScale(0.75f);

	mRifleMeshComp = new MeshComponent(this);
	mRifleMeshComp->SetMesh(game->GetRenderer()->GetMesh("Meshes/Rifle.gpmesh"));
}

void RifleActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	FPSActor* fpsActor = GetGame()->GetFPSActor();

	Vector3 position = fpsActor->GetPosition();
	Vector3 riflePosition = position + Vector3(12.0f, 10.0f, -10.0f);
	SetPosition(riflePosition);
}

void RifleActor::ActorInput(const uint8_t* keys)
{}
