#pragma once

#include "CameraComponent.h"

class FPSCamera : public CameraComponent
{
public:
	FPSCamera() = delete;
	FPSCamera(class Actor* owner);
	~FPSCamera() = default;

	void Update(float deltaTime) override;

	float GetPitch() const { return mPitch; }
	float GetMaxPitch() const { return mMaxPitch; }
	float GetPitchSpeed() const { return mPitchSpeed; }

	void SetMaxPitch(float maxPitch) { mMaxPitch = maxPitch; }
	void SetPitchSpeed(float pitchSpeed) { mPitchSpeed = pitchSpeed; }
private:
	float mPitch;
	float mMaxPitch;
	float mPitchSpeed;
};