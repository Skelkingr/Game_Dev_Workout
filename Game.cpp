#include "Game.h"

#include "Actor.h"
#include "Math.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"

#include <algorithm>

Game::Game()
	:
	mActors({}),
	mPendingActors({}),
	mRenderer(nullptr),
	mTicksCount(0),
	mIsRunning(true),
	mUpdatingActors(false)
{}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mRenderer = new Renderer(this);
	if (!mRenderer->Initialize(static_cast<float>(CLIENT_WIDTH), static_cast<float>(CLIENT_HEIGHT)))
	{
		SDL_Log("Failed to initialize renderer.");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

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

	for (auto actor : mActors)
	{
		actor->ProcessInput(keyState);
	}
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
	mRenderer->Draw();
}

void Game::LoadData()
{
	// Create Cube
	Actor* act = new Actor(this);
	act->SetPosition(Vector3(200.0f, 75.0f, 75.0f));
	act->SetScale(100.0f);

	Quaternion quat(Vector3::UnitY, -Math::PiOver2);
	quat = Quaternion::Concatenate(quat, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
	act->SetRotation(quat);

	MeshComponent* meshComp = new MeshComponent(act);
	meshComp->SetMesh(mRenderer->GetMesh("Meshes/Cube.gpmesh"));

	// Create Sphere
	act = new Actor(this);
	act->SetPosition(Vector3(200.0f, -75.0f, 0.0f));
	act->SetScale(3.0f);

	meshComp = new MeshComponent(act);
	meshComp->SetMesh(mRenderer->GetMesh("Meshes/Sphere.gpmesh"));
}

void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	if (mRenderer)
	{
		mRenderer->UnloadData();
	}
}

void Game::Shutdown()
{
	UnloadData();
	
	if (mRenderer)
	{
		mRenderer->ShutDown();
	}
	
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

