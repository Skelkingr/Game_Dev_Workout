#pragma once

#include "InputSystem.h"
#include "Math.h"

#include <vector>

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
public:
	Actor() = delete;
	Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	void ProcessInput(const InputState& state);

	virtual void UpdateActor(float deltaTime);
	virtual void ActorInput(const InputState& state);

	class Game* GetGame() const { return mGame; }
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }
	const Vector3& GetPosition() const { return mPosition; }
	const Quaternion& GetRotation() const { return mRotation; }
	float GetScale() const { return mScale; }
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	int GetState() const { return mState; }

	void SetState(State state) { mState = state; }

	void SetPosition(const Vector3& position);
	void SetRotation(const Quaternion& rotation);
	void SetScale(float scale);

	void ComputeWorldTransform();

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	State mState;
	
	Vector3 mPosition;
	Quaternion mRotation;
	float mScale;
	
	Matrix4 mWorldTransform;
	bool mRecomputWorldTransform;
	
	std::vector<class Component*> mComponents;

	class Game* mGame;
};
