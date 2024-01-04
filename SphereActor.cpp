#include "SphereActor.h"

#include "Actor.h"
#include "AudioComponent.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Renderer.h"

SphereActor::SphereActor(Game* game)
	:
	Actor(game),
	mDirection(1),
	mGoingForward(true)
{
	mAudioComp = new AudioComponent(this);

	mMeshComp = new MeshComponent(this);
	mMoveComp = new MoveComponent(this);

	mMeshComp->SetMesh(GetGame()->GetRenderer()->GetMesh("Meshes/Sphere.gpmesh"));

	mFireLoop = mAudioComp->PlayEvent("event:/FireLoop");
	mFireLoop.SetVolume(mFireLoop.GetVolume() / 2.0f);
}

SphereActor::~SphereActor()
{
	if (mMoveComp)
	{
		delete mMoveComp;
		mMoveComp = nullptr;
	}

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

void SphereActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	float forwardSpeed = 0.0f;
	SetDirection();
	
	if (mDirection == 1)
	{
		forwardSpeed += 400.0f;
	}
	if (mDirection == -1)
	{
		forwardSpeed -= 400.0f;
	}
	
	mMoveComp->SetForwardSpeed(forwardSpeed);
	mFireLoop.Set3DAttributes(this->GetWorldTransform());
}

void SphereActor::SetDirection()
{
	if (GetPosition().x > 1000.0f && mGoingForward)
	{
		mDirection = -1;
		mGoingForward = false;
	}
	if (GetPosition().x < -1000.0f && !mGoingForward)
	{
		mDirection = 1;
		mGoingForward = true;
	}
}
