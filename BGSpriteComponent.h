#pragma once

#include "SpriteComponent.h"

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(Actor* owner, int drawOrder = 10);

	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;

	void SetBGTextures(const std::vector<SDL_Texture*>& textures);

	void SetScreenSize(const Vector2& screenSize) { this->mScreenSize = screenSize; }
	void SetScrollSpeed(float speed) { this->mScrollSpeed = speed; }

	float GetScrollSpeed() { return this->mScrollSpeed; }
private:
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};