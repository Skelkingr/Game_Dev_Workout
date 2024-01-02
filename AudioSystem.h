#pragma once

#include "SoundEvent.h"

#include <string>
#include <unordered_map>

namespace FMOD
{
	class System;
	
	namespace Studio
	{
		class Bank;
		class Bus;
		class EventDescription;
		class EventInstance;
		class System;
	}
}

class AudioSystem
{
public:
	AudioSystem() = delete;
	AudioSystem(class Game* game);
	~AudioSystem() = default;

	bool Initialize();
	void Shutdown();
	void Update(float deltaTime);

	SoundEvent PlayEvent(const std::string& name);
protected:
	friend class SoundEvent;
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);
private:
	void LoadBank(const std::string& name);
	void UnloadBank(const std::string& name);
	void UnloadAllBanks();
private:
	class Game* mGame;

	std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> mEventInstances;
	std::unordered_map<std::string, FMOD::Studio::Bus*> mBuses;

	FMOD::Studio::System* mSystem;
	FMOD::System* mLowLevelSystem;

	static unsigned int sNextID;
};

