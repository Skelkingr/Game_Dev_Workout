#pragma once

#include "Actor.h"
#include "Math.h"
#include "SpriteComponent.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class Game
{
public:
	Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	void AddSprite(SpriteComponent* sprite);
	void RemoveSprite(SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

	class Grid* GetGrid() { return mGrid; }
	std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	class Enemy* GetNearestEnemy(const Vector2& pos);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	void PlayMusic(const char* fileName);
	void PlaySoundFX(const char* fileName);
private:
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<Actor*> mActors;

	std::vector<Actor*> mPendingActors;

	std::vector<SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Mix_Music* mMusic;

	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;

	/* GAME SPECIFIC */
	std::vector<class Enemy*> mEnemies;
	class Grid* mGrid;
	float mNextEnemy;
	/* */
};