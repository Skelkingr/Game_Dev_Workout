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
	Vector2 GetForward() const;
	Vector2 GetPosition() const { return mPosition; }
	float GetRotation() const { return mRotation; }
	float GetScale() const { return mScale; }
	int GetState() const { return mState; }

	void SetPosition(Vector2 position) { mPosition = position; }
	void SetScale(float scale) { mScale = scale; }
	void SetRotation(float rotation) { mRotation = rotation; }

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	std::vector<class Component*> mComponents;
	class Game* mGame;
};
