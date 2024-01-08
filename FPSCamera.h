#pragma once

#include "CameraComponent.h"

class FPSCamera : public CameraComponent
{
public:
	FPSCamera() = delete;
	FPSCamera(class Actor* owner);
	~FPSCamera() = default;

	void Update(float deltaTime) override;
};