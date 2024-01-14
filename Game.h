#pragma once

#include "SoundEvent.h"

#include <SDL/SDL.h>

#include <string>
#include <unordered_map>
#include <vector>

constexpr int CLIENT_WIDTH = 1024;
constexpr int CLIENT_HEIGHT = 768;

constexpr float TEXTURE_WIDTH = 1024.0f;

class Game
{
public:
	Game();
	~Game() = default;

	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	class FPSActor* GetFPSActor() const { return mFPSActor; }
	class RifleActor* GetRifleActor() const { return mRifleActor; }

	class AudioSystem* GetAudioSystem() const { return mAudioSystem; }
	class Renderer* GetRenderer() const { return mRenderer; }
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	void LoadData();
	void UnloadData();
private:
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	class AudioSystem* mAudioSystem;
	class Renderer* mRenderer;
	
	Uint32 mTicksCount;

	bool mIsRunning;
	bool mUpdatingActors;

	SoundEvent mMusicEvent;
	SoundEvent mReverbSnap;

	class FPSActor* mFPSActor;
	class RifleActor* mRifleActor;
};