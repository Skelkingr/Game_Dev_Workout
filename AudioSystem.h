#pragma once

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
	void ShutDown();
	void Update(float deltaTime);

	void PlayEvent(const std::string& name);
private:
	void LoadBank(const std::string& name);
	void UnloadBank(const std::string& name);
	void UnloadAllBanks();
private:
	class Game* mGame;

	std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;
	std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;
	std::unordered_map<std::string, FMOD::Studio::Bus*> mBuses;

	FMOD::Studio::System* mSystem;
	FMOD::System* mLowLevelSystem;
};

