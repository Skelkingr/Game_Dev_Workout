#include "Actor.h"
#include "Component.h"
#include "Game.h"

#include <algorithm>

Actor::Actor(Game* game)
	:
	mState(EActive),
	mPosition(Vector3::Zero),
	mScale(1.0f),
	mRotation(0.0f),
	mWorldTransform(Matrix4::Identity),
	mRecomputWorldTransform(true),
	mGame(game)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		ComputeWorldTransform();

		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		ComputeWorldTransform();
	}

	for (auto comp : mComponents)
	{
		comp->OnUpdateWorldTransform();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}

void Actor::UpdateActor(float deltaTime)
{}

void Actor::ActorInput(const uint8_t* keyState)
{}

void Actor::SetPosition(Vector3 position)
{
	mPosition = position;
	mRecomputWorldTransform = true;
}

void Actor::SetScale(float scale)
{
	mScale = scale;
	mRecomputWorldTransform = true;
}

void Actor::SetRotation(float rotation)
{
	mRotation = rotation;
	mRecomputWorldTransform = true;
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputWorldTransform)
	{
		mRecomputWorldTransform = false;

		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));
	}

	for (auto comp : mComponents)
	{
		comp->OnUpdateWorldTransform();
	}
}

void Actor::AddComponent(Component* component)
{
	int myFuckingOrder = component->GetUpdateOrder();

	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myFuckingOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}