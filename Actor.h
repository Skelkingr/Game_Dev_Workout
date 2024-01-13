#pragma once

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
	Actor() = default;
	Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);
	
	void ProcessInput(const uint8_t* keys);
	virtual void ActorInput(const uint8_t* keys);

	const Vector3& GetPosition() const { return mPosition; }
	float GetScale() const { return mScale; }
	const Quaternion& GetRotation() const { return mRotation; }

	void SetPosition(const Vector3& position);
	void SetScale(float scale);
	void SetRotation(const Quaternion& rotation);

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	Vector3 GetForward() const;
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, mRotation); }
	
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }
	
	class Game* GetGame() const { return mGame; }

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	State mState;
	
	Matrix4 mWorldTransform;
	Vector3 mPosition;
	Quaternion mRotation;
	float mScale;
	bool mRecomputWorldTransform;
	
	std::vector<class Component*> mComponents;
	class Game* mGame;
};
