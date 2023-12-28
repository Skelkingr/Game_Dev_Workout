#include "MoveComponent.h"

MoveComponent::MoveComponent()
	:
	Component(),
	mAngularSpeed(0.0f),
	mForwardSpeed(0.0f)
{}

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	:
	Component(owner),
	mAngularSpeed(0.0f),
	mForwardSpeed(0.0f)
{}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}

	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		mOwner->SetPosition(pos);
	}
}
