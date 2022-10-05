#pragma once

#include <vector>

#include "Component.h"
#include "Game.h"

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
	Actor(Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	std::vector<Component*> mComponents;
	Game* mGame;
};
