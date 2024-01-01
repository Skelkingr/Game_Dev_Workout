#pragma once

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
private:
	class Game* mGame;

	FMOD::Studio::System* mSystem;
	FMOD::System* mLowLevelSystem;
};

