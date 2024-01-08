#include "FPSActor.h"

#include "AudioComponent.h"
#include "AudioSystem.h"
#include "Game.h"
#include "MoveComponent.h"
#include "Renderer.h"

#include <SDL/SDL.h>

FPSActor::FPSActor(Game* game)
	:
	Actor(game),
	mLastFootstep(0.0f)
{
	mAudioComp = new AudioComponent(this);
	mMoveComp = new MoveComponent(this);

	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetPaused(true);
}

FPSActor::~FPSActor()
{
	if (mMoveComp)
	{
		delete mMoveComp;
		mMoveComp = nullptr;
	}
	if (mAudioComp)
	{
		delete mAudioComp;
		mAudioComp = nullptr;
	}
}

void FPSActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	mLastFootstep -= deltaTime;
	if ((!Math::NearZero(mMoveComp->GetForwardSpeed()) || !Math::NearZero(mMoveComp->GetStrafeSpeed())) && mLastFootstep <= 0.0f)
	{
		mFootstep.SetPaused(false);
		mFootstep.Restart();
		mLastFootstep = 0.5f;
	}

	Vector3 cameraPos = GetPosition();
	Vector3 target = GetPosition() + GetForward() * 100.0f;
	Vector3 up = Vector3::UnitZ;
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	GetGame()->GetRenderer()->SetViewMatrix(view);
	/*GetGame()->GetAudioSystem()->SetListener(view); */
}

void FPSActor::ActorInput(const uint8_t* keys)
{
	//Keyboard stuff
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;

	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 200.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 200.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		strafeSpeed -= 200.0f;
	}
	if (keys[SDL_SCANCODE_D])
	{
		strafeSpeed += 200.0f;
	}

	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetStrafeSpeed(strafeSpeed);

	// Mouse stuff:
	int x;
	int y;
	uint32_t buttons = SDL_GetRelativeMouseState(&x, &y);

	const float maxMouseSpeed = 500.0f;
	const float maxAngularSpeed = Math::Pi * 8.0f;

	float angularSpeed = 0.0f;

	if (x != 0)
	{
		angularSpeed = x / maxMouseSpeed;
		angularSpeed *= maxAngularSpeed;
	}

	mMoveComp->SetAngularSpeed(angularSpeed);
}
