#include <vector>

#include "Game.h"

Game::Game()
{
	mWindow = nullptr;
	mRenderer = nullptr;
	mIsRunning = false;

	mWindowWidth = 1024;
	mWindowHeight = 768;

	mPaddleH = mWindowHeight / 4;
	mPaddlePos = {
		static_cast<float>(mThickness),
		static_cast<float>((mWindowHeight / 2.f) - mPaddleH / 2.f)
	};
	mPaddleDir = 0;

	mBallPos = {
		mWindowWidth / 2.f,
		mWindowHeight / 2.f
	};
	mBallVel = {
		-200.F,
		235.f
	};

	mTicksCount = 0;
}

bool Game::Initialize()
{
	int sdlInit = SDL_Init(SDL_INIT_VIDEO);

	if (sdlInit != 0)
	{
		SDL_Log("[ERROR] Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Skelkingr",
		200,
		200,
		static_cast<int>(mWindowWidth),
		static_cast<int>(mWindowHeight),
		0
	);
	mIsRunning = true;

	if (!mWindow)
	{
		SDL_Log("[ERR] Failed to initialize window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("[ERR] Failed to initialize renderer: %s", SDL_GetError());
		return false;
	}

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

void Game::ShutDown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
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
}

void Game::UpdateGame()
{
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;
	mTicksCount = SDL_GetTicks();

	/* Paddle */
	mPaddleDir = MovePaddle();

	if (mPaddleDir != 0)
	{
		std::string borderHit = PaddleHitsBorders();

		if (borderHit == "top")
			mPaddlePos.y = static_cast<float>(mThickness / 2.f);

		if (borderHit == "bottom")
		{
			mPaddlePos.y = mWindowHeight - static_cast<float>(mThickness / 2.f) - static_cast<float>(mPaddleH);
		}

		mPaddlePos.y += mPaddleDir * 300.f * deltaTime;
	}
	/* */

	/* Ball */
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	BallHitsBorders();
	BallHitsPaddle();
	/* */
}

void Game::GenerateOutput()
{
	/* Background */
	SetRenderDrawColor(0, 0, 0, 255);
	SDL_Rect background = GenerateRect(0, 0, mWindowWidth, mWindowHeight);
	SDL_RenderFillRect(mRenderer, &background);
	/* */

	/* Ball */
	SetRenderDrawColor(255, 255, 255, 255);
	SDL_Rect ball = GenerateRect(
		static_cast<int>(mBallPos.x - mThickness / 2.f),
		static_cast<int>(mBallPos.y - mThickness / 2.f),
		mThickness,
		mThickness
	);
	SDL_RenderFillRect(mRenderer, &ball);
	/* */

	/* Paddle */
	SetRenderDrawColor(255, 255, 255, 255);
	SDL_Rect paddle = GenerateRect(
		static_cast<int>(mPaddlePos.x * 3 - mThickness / 2.f),
		static_cast<int>(mPaddlePos.y),
		mThickness,
		mPaddleH
	);
	SDL_RenderFillRect(mRenderer, &paddle);
	/* */

	/* Borders */
	GenerateBorders(true);
	/* */
	
	SDL_RenderPresent(mRenderer);
	SDL_RenderClear(mRenderer);
}

int Game::SetRenderDrawColor(int red, int green, int blue, int alpha)
{
	return SDL_SetRenderDrawColor(
		this->mRenderer,
		red,
		green,
		blue,
		alpha
	);
}

void Game::GenerateBorders(bool topAndBottom)
{
	SetRenderDrawColor(255, 114, 118, 255);

	/* Left and right borders */
	SDL_Rect left = GenerateRect(0, 0, mThickness / 2, mWindowHeight);
	SDL_Rect right = GenerateRect(mWindowWidth - mThickness / 2, 0, mThickness / 2, mWindowHeight);
	/* */

	/* Top and bottom borders */
	SDL_Rect top{ 0, 0 }, bottom{ 0, 0 };

	if (topAndBottom)
	{
		top = GenerateRect(0, 0, mWindowWidth, mThickness / 2);
		bottom = GenerateRect(0, mWindowHeight - mThickness / 2, mWindowWidth, mThickness / 2);
	}
	/* */
	
	std::vector<SDL_Rect> borders;
	borders.push_back(left);
	borders.push_back(right);

	if (topAndBottom)
	{
		borders.push_back(top);
		borders.push_back(bottom);
	}
	
	for (SDL_Rect border : borders)
		SDL_RenderFillRect(mRenderer, &border);
}

SDL_Rect Game::GenerateRect(int x, int y, int width, int height)
{
	return SDL_Rect{
		x,
		y,
		width,
		height
	};
}

int Game::MovePaddle()
{
	mPaddleDir = 0;
	
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_UP])
		mPaddleDir -= 1;
		
		
	if (state[SDL_SCANCODE_DOWN])
		mPaddleDir += 1;

	return mPaddleDir;
}

std::string Game::PaddleHitsBorders()
{
	if (mPaddlePos.y <= static_cast<float>(mThickness / 2.f))
		return "top";
		
	if ((mPaddlePos.y + mPaddleH >= (mWindowHeight - static_cast<float>(mThickness / 2.f))))
		return "bottom";

	return "none";
}

void Game::BallHitsBorders()
{	
	float left = static_cast<float>(mThickness / 2.f);
	float right = (mWindowWidth - static_cast<float>(mThickness / 2.f));

	float top = static_cast<float>(mThickness / 2.f);
	float bottom = (mWindowHeight - static_cast<float>(mThickness / 2.f));

	// Ball hits left of right border
	if (mBallPos.x <= left || mBallPos.x >= right)
		mBallVel.x *= -1.0f;

	// Ball hits top or bottom border
	if (mBallPos.y <= top || mBallPos.y >= bottom)
		mBallVel.y *= -1.0f;
}

void Game::BallHitsPaddle()
{
	float paddleTop = mPaddlePos.y;
	float paddleBottom = mPaddlePos.y + mPaddleH;

	bool outOfPaddleArea = (mBallPos.y < paddleTop || mBallPos.y > paddleBottom);
	bool hitsPaddleRightSide = mBallPos.x <= static_cast<int>(mPaddlePos.x * 3 + mThickness / 2.f);

	if (mBallVel.x < 0.f && !outOfPaddleArea && hitsPaddleRightSide)
		mBallVel.x *= -1.0f;
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors)
		mPendingActors.emplace_back(actor);
	else
		mActors.emplace_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	if (VectorContainsActor(mActors, actor))
		remove(mActors.begin(), mActors.end(), actor);
	if (VectorContainsActor(mPendingActors, actor))
		remove(mPendingActors.begin(), mPendingActors.end(), actor);
}

bool Game::VectorContainsActor(std::vector<Actor*> v, Actor* actor)
{
	if (std::find(v.begin(), v.end(), actor) != v.end())
		return true;
	return false;
}
