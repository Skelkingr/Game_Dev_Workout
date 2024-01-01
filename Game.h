#pragma once

#include <SDL/SDL.h>

#include <string>
#include <unordered_map>
#include <vector>

constexpr int CLIENT_WIDTH = 1024;
constexpr int CLIENT_HEIGHT = 768;

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

	class Renderer* GetRenderer() const { return mRenderer; }
	class AudioSystem* GetAudioSystem() const { return mAudioSystem; }
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	void LoadData();
	void UnloadData();
private:
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	class Renderer* mRenderer;
	class AudioSystem* mAudioSystem;

	Uint32 mTicksCount;

	bool mIsRunning;
	bool mUpdatingActors;
};