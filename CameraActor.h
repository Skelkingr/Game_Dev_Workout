#pragma once

#include "Actor.h"
#include "InputSystem.h"
#include "SoundEvent.h"

class CameraActor :	public Actor
{
public:
	CameraActor() = delete;
	CameraActor(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const InputState& state) override;
private:
	class MoveComponent* mMoveComp;
	class AudioComponent* mAudioComp;

	SoundEvent mFootstep;
	float mLastFootstep;
};

