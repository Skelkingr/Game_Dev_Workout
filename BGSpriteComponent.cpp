#include "BGSpriteComponent.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder)
	:
	SpriteComponent(owner, drawOrder),
	mScrollSpeed(0.0f),
	mInputComponent(nullptr),
	mShip(nullptr)
{}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	
	for (auto& bg : mBGTextures)
	{
		float forwardX = mShip->GetForward().x;
		float forwardY = mShip->GetForward().y;

		float shipAngle = Math::Atan2(-forwardY, forwardX);

		// @TODO : Find the perfect recipe
		bg.mOffset.x += mScrollSpeed * Math::Sgn(forwardX) * deltaTime;
		bg.mOffset.y += forwardY * Math::Sgn(forwardY);
		

		// @TODO: Manage Left
		if (bg.mOffset.x < -mScreenSize.x)
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}

		if (bg.mOffset.y < -mScreenSize.y)
		{
			bg.mOffset.y = (mBGTextures.size() - 1) * mScreenSize.y - 1;
		}
	}
}

// @TODO: Fix loss of data
void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& bg : mBGTextures)
	{
		SDL_Rect rect = {};

		rect.w = mScreenSize.x;
		rect.h = mScreenSize.y;

		rect.x = mOwner->GetPosition().x - rect.w / 2.0f + bg.mOffset.x;
		rect.y = mOwner->GetPosition().y - rect.h / 2.0f + bg.mOffset.y;

		SDL_RenderCopy(
			renderer,
			bg.mTexture,
			nullptr,
			&rect
		);
	}
}

void BGSpriteComponent::ProcessInput(const uint8_t* keyState)
{
	float scrollSpeed = 0.0f;

	if (keyState[mInputComponent->GetForwardKey()])
	{
		scrollSpeed -= 150.0f;
	}
	if (keyState[mInputComponent->GetBackKey()])
	{
		scrollSpeed += 75.0f;
	}
	SetScrollSpeed(scrollSpeed);
}

// @TODO : 9 textures total patchwork
void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int i = -1;
	/*int j = -1;

	for (; i < 1; ++i)
	{
		for (; j < 1; ++j)
		{
			BGTexture temp;
			temp.mTexture = textures[j + 1];
			temp.mOffset.x = i * mScreenSize.x;
			temp.mOffset.y = j * mScreenSize.y;
			mBGTextures.emplace_back(temp);
		}
	}*/

	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		temp.mOffset.x = i * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		++i;
	}
}
