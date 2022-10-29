#include "BGSpriteComponent.h"

BGSpriteComponent::BGSpriteComponent(class Actor* owner, int drawOrder)
	:
	SpriteComponent(owner, drawOrder),
	mScrollSpeed(0.0f),
	mInputComponent(nullptr),
	mShip(owner->GetGame()->GetShip())
{
	mShipPosition = Vector2(mShip->GetCenterShipX(), mShip->GetCenterShipY());
}

void BGSpriteComponent::Update(float deltaTime)
{
	
	SpriteComponent::Update(deltaTime);

	float forwardX = mShip->GetForward().x;
	float forwardY = mShip->GetForward().y;

	for (auto& bg : mBGTextures)
	{

		bg.mOffset.x += mScrollSpeed * forwardX * deltaTime;
		bg.mOffset.y += mScrollSpeed * forwardY * deltaTime;


		// @TODO : Reset background offset
		ResetBacKGroundOffSetX(&bg, forwardX);
	}
}

// @TODO : Prevent black gaps
void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	float forwardX = mShip->GetForward().x;
	float forwardY = mShip->GetForward().y;

	for (auto& bg : mBGTextures)
	{
		SDL_FRect rect = {};

		rect.w = mScreenSize.x;
		rect.h = mScreenSize.y;

		rect.x = mOwner->GetPosition().x - rect.w / 2.0f + bg.mOffset.x;
		rect.y = mOwner->GetPosition().y - rect.h / 2.0f + bg.mOffset.y;

		SDL_RenderCopyF(renderer,
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
		scrollSpeed -= 400.0f;
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
		i++;
	}
}

void BGSpriteComponent::ResetBacKGroundOffSetX(BGTexture* texture)
{
	if (texture->mOffset.x < -mScreenSize.x)
	{
		texture->mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
	}
}
