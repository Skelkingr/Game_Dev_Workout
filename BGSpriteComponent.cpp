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

		// @TODO: Compute black gap between two textures (or find out why there is one)

		if (bg.mOffset.x < -mScreenSize.x)
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}

		// @TODO: Scroll to the left
		/*if (bg.mOffset.x > mScreenSize.x)
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * -mScreenSize.x - 1;
		}*/

		// @TODO: Manage vertical (that means Up and Down in case you're dumb)
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& bg : mBGTextures)
	{
		SDL_FRect rect = {};

		rect.w = mScreenSize.x;
		rect.h = mScreenSize.y;

		rect.x = mOwner->GetPosition().x - rect.w / 2.0f + bg.mOffset.x;
		rect.y = mOwner->GetPosition().y - rect.h / 2.0f + bg.mOffset.y;

		SDL_RenderCopyExF(
			renderer,
			bg.mTexture,
			nullptr,
			&rect,
			0.0,
			nullptr,
			SDL_FLIP_NONE
		);
	}
}

void BGSpriteComponent::ProcessInput(const uint8_t* keyState)
{
	float scrollSpeed = 0.0f;

	if (keyState[mInputComponent->GetForwardKey()])
	{
		scrollSpeed -= 300.0f;
	}
	if (keyState[mInputComponent->GetBackKey()])
	{
		scrollSpeed += 150.0f;
	}
	SetScrollSpeed(scrollSpeed);
}

// @TODO : 9 textures total patchwork
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
