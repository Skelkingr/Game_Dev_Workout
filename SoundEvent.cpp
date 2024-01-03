#include "SoundEvent.h"

#include "AudioSystem.h"

#include <fmod_studio.hpp>

namespace
{
	FMOD_VECTOR VecToFMOD(const Vector3& in)
	{
		FMOD_VECTOR vec = {};
		vec.x = in.y;
		vec.y = in.z;
		vec.z = in.x;

		return vec;
	}
}

SoundEvent::SoundEvent()
	:
	mSystem(nullptr),
	mID(0)
{}

SoundEvent::SoundEvent(AudioSystem* system, unsigned int id)
	:
	mSystem(system),
	mID(id)
{}

bool SoundEvent::IsValid() const
{
	return (mSystem && mSystem->GetEventInstance(mID) != nullptr);
}

bool SoundEvent::Is3D() const
{
	bool result = false;
	
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		FMOD::Studio::EventDescription* eventDesc = nullptr;
		if (eventDesc)
		{
			eventDesc->is3D(&result);
		}
	}

	return result;
}

void SoundEvent::Restart()
{
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		event->start();
	}
}

void SoundEvent::Stop(bool allowFadeOut)
{
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		FMOD_STUDIO_STOP_MODE mode = allowFadeOut ? FMOD_STUDIO_STOP_ALLOWFADEOUT : FMOD_STUDIO_STOP_IMMEDIATE;
		event->stop(mode);
	}
}

void SoundEvent::SetPaused(bool pause)
{
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		event->setPaused(pause);
	}
}

void SoundEvent::SetVolume(float value)
{
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		event->setVolume(value);
	}
}

void SoundEvent::SetPitch(float value)
{
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		event->setPitch(value);
	}
}

void SoundEvent::SetParameter(const std::string& name, float value)
{
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		event->setParameterValue(name.c_str(), value);
	}
}

void SoundEvent::Set3DAttributes(const Matrix4& worldTrans)
{
	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		FMOD_3D_ATTRIBUTES attr = {};
		attr.position = VecToFMOD(worldTrans.GetTranslation());
		attr.forward = VecToFMOD(worldTrans.GetXAxis());
		attr.up = VecToFMOD(worldTrans.GetZAxis());

		attr.velocity = { 0.0f, 0.0f, 0.0f };

		event->set3DAttributes(&attr);
	}
}

bool SoundEvent::GetPaused() const
{
	bool result = false;

	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		event->getPaused(&result);
	}

	return result;
}

float SoundEvent::GetVolume() const
{
	float result = 0.0f;

	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		event->getVolume(&result);
	}

	return result;
}

float SoundEvent::GetPitch() const
{
	float result = 0.0f;

	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		event->getPitch(&result);
	}

	return result;
}

float SoundEvent::GetParameter(const std::string& name)
{
	float result = 0.0f;

	auto event = mSystem ? mSystem->GetEventInstance(mID) : nullptr;
	if (event)
	{
		event->getParameterValue(name.c_str(), &result);
	}

	return result;
}
