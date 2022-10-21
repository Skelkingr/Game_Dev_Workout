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

		bool cosNearZero = (Math::NearZero(Math::Cos(shipAngle), 0.01f));
		bool sinNearZero = (Math::NearZero(Math::Sin(shipAngle), 0.01f));

		if (sinNearZero)
		{
			
			bg.mOffset.x += Math::Sgn(forwardX) * mScrollSpeed * deltaTime;
			ResetOffsetX(&bg);
		}
		else if (cosNearZero)
		{
			bg.mOffset.y += Math::Sgn(forwardY) * mScrollSpeed * deltaTime;
		}
		else
		{
			bg.mOffset.x += Math::Sgn(forwardX) * mScrollSpeed * Math::Abs(Math::Cos(shipAngle)) * deltaTime;
			bg.mOffset.y += Math::Sgn(forwardY) * mScrollSpeed * Math::Abs(Math::Sin(shipAngle)) * deltaTime;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& bg : mBGTextures)
	{
		SDL_Rect rect;

		rect.w = static_cast<int>(mScreenSize.x);
		rect.h = static_cast<int>(mScreenSize.y);

		rect.x = static_cast<int>(mOwner->GetPosition().x - rect.w / 2 + bg.mOffset.x);
		rect.y = static_cast<int>(mOwner->GetPosition().y - rect.h / 2 + bg.mOffset.y);

		SDL_RenderCopy(renderer,
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
		scrollSpeed -= 200.0f;
	}
	if (keyState[mInputComponent->GetBackKey()])
	{
		scrollSpeed += 100.0f;
	}
	SetScrollSpeed(scrollSpeed);
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int i = 0;

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

void BGSpriteComponent::ResetOffsetX(BGTexture* texture)
{
	if (texture->mOffset.x < -mScreenSize.x)
	{
		texture->mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
	}
}
