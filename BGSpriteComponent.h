#pragma once

#include "Game.h"
#include "InputComponent.h"
#include "SpriteComponent.h"

#include <SDL.h>

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);

	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void ProcessInput(const uint8_t* keyState) override;

	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	void SetScreenSize(const Vector2& screenSize) { mScreenSize = screenSize; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	void SetInputComponent(InputComponent* inputComponent) { mInputComponent = inputComponent; }

	float GetScrollSpeed() const { return mScrollSpeed; }
	InputComponent* GetInputComponent() const { return mInputComponent; }

	Vector2 GetShipNormal() const { return mOwner->GetGame()->GetShip()->GetForward(); }
private:
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;

	InputComponent* mInputComponent;
};