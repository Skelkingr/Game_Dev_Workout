#include "AudioComponent.h"

#include "AudioSystem.h"
#include "Game.h"

AudioComponent::AudioComponent(Actor* owner, int updateOrder)
	:
	Component(owner, updateOrder),
	mEvents2D({}),
	mEvents3D({})
{}

AudioComponent::~AudioComponent()
{
	StopAllEvents();
}

void AudioComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	auto iter = mEvents2D.begin();
	if (iter != mEvents2D.end())
	{
		if (!iter->IsValid())
		{
			iter = mEvents2D.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	iter = mEvents3D.begin();
	if (iter != mEvents3D.end())
	{
		if (!iter->IsValid())
		{
			iter = mEvents3D.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void AudioComponent::OnUpdateWorldTransform()
{
	Matrix4 world = mOwner->GetWorldTransform();
	
	for (auto& event : mEvents3D)
	{
		if (event.IsValid())
		{
			event.Set3DAttributes(world);
		}
	}
}

SoundEvent AudioComponent::PlayEvent(const std::string& name)
{
	SoundEvent event = mOwner->GetGame()->GetAudioSystem()->PlayEvent(name);
	
	if (event.Is3D())
	{
		mEvents3D.emplace_back(event);
		event.Set3DAttributes(mOwner->GetWorldTransform());
	}
	else
	{
		mEvents2D.emplace_back(event);
	}

	return event;
}

void AudioComponent::StopAllEvents()
{
	for (auto& event : mEvents2D)
	{
		event.Stop();
	}

	for (auto& event : mEvents3D)
	{
		event.Stop();
	}

	mEvents2D.clear();
	mEvents3D.clear();
}


