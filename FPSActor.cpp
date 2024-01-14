#include "FPSActor.h"

#include "AudioComponent.h"
#include "AudioSystem.h"
#include "FPSCamera.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Renderer.h"
#include "RifleActor.h"
#include "Shader.h"
#include "SoundEvent.h"

FPSActor::FPSActor(Game* game)
	:
	Actor(game),
	mLastFootstep(0.0f),
	mIsDashing(false)
{
	mAudioComp = new AudioComponent(this);
	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetVolume(0.125f);
	mFootstep.SetPaused(true);

	mCameraComp = new FPSCamera(this);

	mMoveComp = new MoveComponent(this);
}

void FPSActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	if (!mIsDashing)
	{
		mLastFootstep -= deltaTime;
	}
	else
	{
		mLastFootstep -= deltaTime * 1.5f;
	}

	if ((!Math::NearZero(mMoveComp->GetForwardSpeed()) || !Math::NearZero(mMoveComp->GetStrafeSpeed())) && mLastFootstep <= 0.0f)
	{
		mFootstep.SetPaused(false);
		mFootstep.Restart();
		mLastFootstep = 0.45f;
	}
}

void FPSActor::ActorInput(const uint8_t* keys)
{
	mIsDashing = false;

	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;

	if (keys[SDL_SCANCODE_W])
	{
		if (keys[SDL_SCANCODE_LSHIFT])
		{
			mIsDashing = true;
			forwardSpeed += DASHING_SPEED;
		}
		else
		{
			mIsDashing = false;
			forwardSpeed += NORMAL_SPEED;
		}
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= NORMAL_SPEED;
	}
	if (keys[SDL_SCANCODE_A])
	{
		strafeSpeed -= NORMAL_SPEED;
	}
	if (keys[SDL_SCANCODE_D])
	{
		strafeSpeed += NORMAL_SPEED;
	}

	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetStrafeSpeed(strafeSpeed);

	int x, y;
	SDL_GetRelativeMouseState(&x, &y);
	const float maxMouseSpeed = 500;
	const float maxAngularSpeed = Math::Pi * 8;
	float angularSpeed = 0.0f;
	if (x != 0)
	{
		angularSpeed = static_cast<float>(x) / maxMouseSpeed;
		angularSpeed *= maxAngularSpeed;
	}
	mMoveComp->SetAngularSpeed(angularSpeed);

	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{

		pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	mCameraComp->SetPitchSpeed(pitchSpeed);
}
