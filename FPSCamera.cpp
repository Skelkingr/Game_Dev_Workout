#include "FPSCamera.h"

#include "Actor.h"

FPSCamera::FPSCamera(Actor* owner)
	:
	CameraComponent(owner)
{}

void FPSCamera::Update(float deltaTime)
{
	Vector3 cameraPos = mOwner->GetPosition();
	Vector3 target = cameraPos + mOwner->GetForward() * 100.0f;
	Vector3 up = Vector3::UnitZ;

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}