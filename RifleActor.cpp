#include "RifleActor.h"

#include "Actor.h"
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

	mRifleMesh = new MeshComponent(this);
	mRifleMesh->SetMesh(game->GetRenderer()->GetMesh("Meshes/Rifle.gpmesh"));
}

RifleActor::~RifleActor()
{
	if (mRifleMesh)
	{
		delete mRifleMesh;
		mRifleMesh = nullptr;
	}
}
