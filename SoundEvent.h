#pragma once

#include "Math.h"

#include <string>

class SoundEvent
{
public:
	SoundEvent();

	bool IsValid() const;
	bool Is3D() const;

	void Restart();

	void Stop(bool allowFadeOut = true);

	void SetPaused(bool pause);
	void SetVolume(float value);
	void SetPitch(float value);
	void SetParameter(const std::string& name, float value);
	void Set3DAttributes(const Matrix4& worldTrans);

	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name);
protected:
	friend class AudioSystem;
	SoundEvent(class AudioSystem* system, unsigned int id);
private:
	AudioSystem* mSystem;
	unsigned int mID;
};

