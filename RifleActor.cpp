#include "RifleActor.h"

#include "Actor.h"
#include "AudioComponent.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"

RifleActor::RifleActor(Game* game)
	:
	Actor(game)
{
	mAudioComp = new AudioComponent(this);
	
	this->SetScale(0.75f);
	mMeshComp = new MeshComponent(this);
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Meshes/Rifle.gpmesh"));
}

RifleActor::~RifleActor()
{
	if (mMeshComp)
	{
		delete mMeshComp;
		mMeshComp = nullptr;
	}
	if (mAudioComp)
	{
		delete mAudioComp;
		mAudioComp = nullptr;
	}
}

void RifleActor::UpdateActor(float deltaTime)
{}

void RifleActor::ActorInput(const uint8_t* keys)
{}
