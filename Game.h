#pragma once

#include "Asteroid.h"
#include "Ship.h"
#include "VertexArray.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <vector>

constexpr int CLIENT_WIDTH = 1024;
constexpr int CLIENT_HEIGHT = 768;

class Game
{
public:
	Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void InitSpriteVerts(const float* vertexBuffer, const unsigned int* indexBuffer);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

	void AddAsteroid(Asteroid* ast);
	void RemoveAsteroid(Asteroid* ast);
	std::vector<Asteroid*>& GetAsteroids() { return mAsteroids; }
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();	

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<class Actor*> mActors;

	std::vector<class Actor*> mPendingActors;

	VertexArray* mSpriteVerts;
	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_GLContext mContext;
	SDL_Renderer* mRenderer;
	Mix_Music* mMusic;

	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;

	Ship* mShip;
	std::vector<Asteroid*> mAsteroids;
};