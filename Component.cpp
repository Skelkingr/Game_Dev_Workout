#include "Component.h"

Component::Component()
	:
	mOwner(nullptr),
	mUpdateOrder(0)
{}

Component::Component(Actor* owner, int updateOrder)
	:
	mOwner(owner),
	mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{}

void Component::ProcessInput(const InputState& state)
{}

void Component::OnUpdateWorldTransform()
{}
