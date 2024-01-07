#include "CameraActor.h"

#include "AudioComponent.h"
#include "AudioSystem.h"
#include "Game.h"
#include "MoveComponent.h"
#include "Renderer.h"

#include <SDL/SDL_scancode.h>

CameraActor::CameraActor(Game* game)
	:
	Actor(game),
	mIsDashing(false)
{
	mMoveComp = new MoveComponent(this);
	mAudioComp = new AudioComponent(this);

	mLastFootstep = 0.0f;
	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetVolume(0.25f);
	mFootstep.SetPaused(true);
}

void CameraActor::UpdateActor(float deltaTime)
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

	if (!Math::NearZero(mMoveComp->GetForwardSpeed()) && mLastFootstep <= 0.0f)
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
	GetGame()->GetAudioSystem()->SetListener(view);

	mFootstep.Set3DAttributes(this->GetWorldTransform());
}

void CameraActor::ActorInput(const InputState& state)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;

	if (state.Keyboard.GetKeyValue(SDL_SCANCODE_W))
	{
		if (state.Keyboard.GetKeyState(SDL_SCANCODE_LSHIFT) == EHeld)
		{
			mIsDashing = true;

			forwardSpeed += 400.0f;
			mFootstep.SetPitch(1.1f);
			mFootstep.SetVolume(0.75f);
		}
		else
		{
			mIsDashing = false;

			forwardSpeed += 200.0f;
			mFootstep.SetPitch(1.0f);
			mFootstep.SetVolume(0.25f);
		}
	}
	if (state.Keyboard.GetKeyValue(SDL_SCANCODE_S))
	{
		forwardSpeed -= 200.0f;
	}
	if (state.Keyboard.GetKeyValue(SDL_SCANCODE_A))
	{
		angularSpeed -= Math::PiOver2;
	}
	if (state.Keyboard.GetKeyValue(SDL_SCANCODE_D))
	{
		angularSpeed += Math::PiOver2;
	}

	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetAngularSpeed(angularSpeed);
}
