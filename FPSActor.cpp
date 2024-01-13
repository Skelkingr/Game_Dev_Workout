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
	mLastFootstep(0.0f)
{
	mAudioComp = new AudioComponent(this);
	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetVolume(0.125f);
	mFootstep.SetPaused(true);

	mCameraComp = new FPSCamera(this);

	mMoveComp = new MoveComponent(this);

	mRifle = new RifleActor(game);
}

FPSActor::~FPSActor()
{
	GetGame()->RemoveActor(mRifle);

	if (mMoveComp)
	{
		delete mMoveComp;
		mMoveComp = nullptr;
	}
	if (mCameraComp)
	{
		delete mCameraComp;
		mCameraComp = nullptr;
	}
	if (mAudioComp)
	{
		delete mCameraComp;
		mCameraComp = nullptr;
	}
}

void FPSActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	mLastFootstep -= deltaTime;
	if (!Math::NearZero(mMoveComp->GetForwardSpeed()) && mLastFootstep <= 0.0f)
	{
		mFootstep.SetPaused(false);
		mFootstep.Restart();
		mLastFootstep = 0.45f;
	}

	UpdateRifle();
}

void FPSActor::ActorInput(const uint8_t* keys)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;

	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += MEDIUM_SPEED;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= MEDIUM_SPEED;
	}
	if (keys[SDL_SCANCODE_A])
	{
		strafeSpeed -= MEDIUM_SPEED;
	}
	if (keys[SDL_SCANCODE_D])
	{
		strafeSpeed += MEDIUM_SPEED;
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

void FPSActor::UpdateRifle()
{
	Vector3 position = GetPosition();
	Vector3 riflePosition = position + Vector3(12.0f, 10.0f, -10.0f);
	mRifle->SetPosition(riflePosition);
	Vector3 target = GetPosition() + GetForward() * 100.0f;
	Vector3 up = Vector3::UnitZ;

	Matrix4 view = Matrix4::CreateLookAt(position, target, up);
	GetGame()->GetRenderer()->SetViewMatrix(view);
}
