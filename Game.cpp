#include "Asteroid.h"
#include "Game.h"
#include "Math.h"
#include "Ship.h"
#include "SpriteComponent.h"

#include <GL/glew.h>

#include <algorithm>

Game::Game()
	:
	mWindow(nullptr),
	mContext(nullptr),
	mSpriteShader(nullptr),
	mSpriteVerts(nullptr),
	mTicksCount(0),
	mIsRunning(true),
	mUpdatingActors(false),
	mShip(nullptr)
{}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Skelkingr", 100, 100, CLIENT_WIDTH, CLIENT_HEIGHT, SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);
	if (!mContext)
	{
		SDL_Log("Failed to create OpenGL context: %s", SDL_GetError());
		return false;
	}

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW: %s", SDL_GetError());
		return false;
	}
	glGetError();

	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders: %s", SDL_GetError());
		return false;
	}

	CreateSpriteVerts();

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
	mUpdatingActors = false;
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	for (auto pending : mPendingActors)
	{
		pending->ComputeWorldTransform();
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();

	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}

	SDL_GL_SwapWindow(mWindow);
}

void Game::LoadData()
{
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(512.0f, 384.0f));
	mShip->SetRotation(Math::PiOver2);

	const int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}
}

bool Game::LoadShaders()
{
	mSpriteShader = new Shader();

	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(static_cast<float>(CLIENT_WIDTH), static_cast<float>(CLIENT_HEIGHT));
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	if (!mSpriteShader->Load("Shaders\\Transform.vert", "Shaders\\Basic.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();

	return true;
}

void Game::CreateSpriteVerts()
{
	float vertexBuffer[] = {
		-0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f,  0.0f,  0.0f,  1.0f
	};

	unsigned int indexBuffer[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertexBuffer, 4, indexBuffer, 6);
}

void Game::UnloadData()
{
	if (mSpriteShader != nullptr)
	{
		delete mSpriteShader;
		mSpriteShader = nullptr;
	}

	if (mSpriteVerts != nullptr)
	{
		delete mSpriteVerts;
		mSpriteVerts = nullptr;
	}
}

Texture* Game::GetTexture(const std::string& fileName)
{
	Texture* texture = nullptr;

	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		texture = iter->second;
	}
	else
	{
		texture = new Texture();
		if (texture->Load(fileName))
		{
			mTextures.emplace(fileName, texture);
		}
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

void Game::AddAsteroid(Asteroid* ast)
{
	mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), ast);
	if (iter != mAsteroids.end())
	{
		mAsteroids.erase(iter);
	}
}

void Game::Shutdown()
{
	UnloadData();
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	int myFuckingDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myFuckingDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

