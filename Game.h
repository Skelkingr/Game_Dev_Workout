#pragma once

#include <string>
#include <SDL.h>

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void ShutDown();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	int SetRenderDrawColor(int red, int green, int blue, int alpha);
	void GenerateBorders(bool topAndBottom);
	SDL_Rect GenerateRect(int x, int y, int width, int height);
	int MovePaddle();
	std::string PaddleHitsBorders();
	void BallHitsBorders();
	void BallHitsPaddle();
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	const std::string mWindowTitle = "Skelkingr";
	int mWindowWidth;
	int mWindowHeight;
private:
	const int mThickness = 15;
	Vector2 mPaddlePos;
	Vector2 mBallPos;
	Vector2 mBallVel;
	Uint32 mTicksCount;
	int mPaddleH;
	int mPaddleDir;
};