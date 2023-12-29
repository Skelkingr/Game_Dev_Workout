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
	Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	void ProcessInput(const uint8_t* keyState);

	virtual void UpdateActor(float deltaTime);
	virtual void ActorInput(const uint8_t* keyState);

	class Game* GetGame() const { return mGame; }
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }
	const Vector2& GetPosition() const { return mPosition; }
	float GetRotation() const { return mRotation; }
	float GetScale() const { return mScale; }
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	int GetState() const { return mState; }

	void SetState(State state) { mState = state; }

	void SetPosition(Vector2 position);
	void SetScale(float scale);
	void SetRotation(float rotation);

	void ComputeWorldTransform();

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	State mState;
	
	Vector2 mPosition;
	float mScale;
	float mRotation;
	
	Matrix4 mWorldTransform;
	bool mRecomputWorldTransform;
	
	std::vector<class Component*> mComponents;

	class Game* mGame;
};
