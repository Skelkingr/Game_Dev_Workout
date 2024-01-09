#include "Actor.h"

#include "Component.h"
#include "Game.h"
#include "Math.h"

#include <algorithm>

Actor::Actor(Game* game)
	:
	mState(EActive),
	mPosition(Vector3::Zero),
	mScale(1.0f),
	mRotation(Quaternion::Identity),
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
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::ProcessInput(const uint8_t* keys)
{
	if (mState == EActive)
	{
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keys);
		}

		ActorInput(keys);
	}
}

void Actor::UpdateActor(float deltaTime)
{}

void Actor::ActorInput(const uint8_t* keys)
{}

void Actor::SetPosition(const Vector3& position)
{
	mPosition = position;
	mRecomputWorldTransform = true;
}

void Actor::SetRotation(const Quaternion& rotation)
{
	mRotation = rotation;
	mRecomputWorldTransform = true;
}

void Actor::SetScale(float scale)
{
	mScale = scale;
	mRecomputWorldTransform = true;
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputWorldTransform)
	{
		mRecomputWorldTransform = false;

		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);
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