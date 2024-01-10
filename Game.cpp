#include "Game.h"

#include "Actor.h"
#include "AudioSystem.h"
#include "FPSActor.h"
#include "Math.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Actor.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "Texture.h"

#include <fmod_studio.hpp>

#include <algorithm>
#include <iostream>

Game::Game()
	:
	mRenderer(nullptr),
	mAudioSystem(nullptr),
	mTicksCount(0),
	mIsRunning(true),
	mUpdatingActors(false),
	mFPSActor(nullptr)
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

	mAudioSystem = new AudioSystem(this);
	if (!mAudioSystem->Initialize())
	{
		SDL_Log("Failed to initialize audio system.");
		delete mAudioSystem;
		mAudioSystem = nullptr;
		return false;
	}
	mReverbSnap = mAudioSystem->PlayEvent("snapshot:/WithReverb");

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
		default:
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
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

	mAudioSystem->Update(deltaTime);
}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}

void Game::LoadData()
{
	Actor* act = new Actor();
	MeshComponent* meshComp = new MeshComponent();
	Texture* currTexture = new Texture();

	// Create floor
	currTexture->Load("Assets/Plane.png");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			act = new Actor(this);
			act->SetScale(10.25f);
			act->SetPosition(Vector3(i * TEXTURE_WIDTH, j * TEXTURE_WIDTH, -200.0f));
			meshComp = new MeshComponent(act);
			meshComp->SetMesh(mRenderer->GetMesh("Meshes/Plane.gpmesh"));
		}
	}

	/* Create walls */
	currTexture->Load("Assets/Brick.png");

	// Left
	Quaternion quat = Quaternion(Vector3::UnitX, Math::PiOver2);

	for (int i = 0; i < 4; i++)
	{
		act = new Actor(this);
		act->SetScale(10.25f);
		act->SetRotation(quat);
		act->SetPosition(Vector3(i * TEXTURE_WIDTH, -TEXTURE_WIDTH / 2.0f, 45.0f));
		meshComp = new MeshComponent(act);
		meshComp->SetTextureIndex(1);
		meshComp->SetMesh(mRenderer->GetMesh("Meshes/Plane.gpmesh"));
	}

	// Forward
	quat = Quaternion::Concatenate(quat, Quaternion(Vector3::UnitZ, Math::PiOver2));
	for (int i = 0; i < 4; i++)
	{
		act = new Actor(this);
		act->SetScale(10.25f);
		act->SetRotation(quat);
		act->SetPosition(Vector3(TEXTURE_WIDTH * 3.5f, TEXTURE_WIDTH * i, 45.0f));
		meshComp = new MeshComponent(act);
		meshComp->SetTextureIndex(1);
		meshComp->SetMesh(mRenderer->GetMesh("Meshes/Plane.gpmesh"));
	}

	// Right
	quat = Quaternion(Vector3::UnitX, Math::PiOver2);

	for (int i = 0; i < 4; i++)
	{
		act = new Actor(this);
		act->SetScale(10.25f);
		act->SetRotation(quat);
		act->SetPosition(Vector3(i * TEXTURE_WIDTH, TEXTURE_WIDTH * 3.5f, 45.0f));
		meshComp = new MeshComponent(act);
		meshComp->SetTextureIndex(1);
		meshComp->SetMesh(mRenderer->GetMesh("Meshes/Plane.gpmesh"));
	}

	// Back
	quat = Quaternion::Concatenate(quat, Quaternion(Vector3::UnitZ, Math::PiOver2));
	for (int i = 0; i < 4; i++)
	{
		act = new Actor(this);
		act->SetScale(10.25f);
		act->SetRotation(quat);
		act->SetPosition(Vector3(-TEXTURE_WIDTH + (TEXTURE_WIDTH / 2.0f), TEXTURE_WIDTH * i, 45.0f));
		meshComp = new MeshComponent(act);
		meshComp->SetTextureIndex(1);
		meshComp->SetMesh(mRenderer->GetMesh("Meshes/Plane.gpmesh"));
	}
	/* Finished creating walls */

	// Let there be light !
	mRenderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.7f, -0.7f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);

	// Add Healthbar
	act = new Actor(this);
	act->SetPosition(Vector3(-350.0f, -350.0f, 0.0f));
	SpriteComponent* spriteComp = new SpriteComponent(act);
	spriteComp->SetTexture(mRenderer->GetTexture("Assets/HealthBar.png"));

	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");
	mMusicEvent.SetVolume(0.125f);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GetRelativeMouseState(nullptr, nullptr);
	mFPSActor = new FPSActor(this);
	mFPSActor->SetPosition(Vector3(1388.0f, 1647.0f, 0.0f));
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
		mRenderer->Shutdown();
	}

	if (mAudioSystem)
	{
		mAudioSystem->Shutdown();
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

