#include "FPSCamera.h"

#include "Actor.h"
#include "Math.h"

#include <iostream>

FPSCamera::FPSCamera(Actor* owner)
	:
	CameraComponent(owner),
	mPitch(0.0f),
	mMaxPitch(Math::Pi / 3.0f),
	mPitchSpeed(0.0f)
{}

void FPSCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	Vector3 cameraPos = mOwner->GetPosition();

	mPitch += mPitchSpeed * deltaTime;
	mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);

	Quaternion quat(mOwner->GetRight(), mPitch);

	Vector3 viewForward = Vector3::Transform(mOwner->GetForward(), quat);
	Vector3 target = cameraPos + viewForward * 100.0f;
	Vector3 up = Vector3::Transform(Vector3::UnitZ, quat);

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}