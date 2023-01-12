#include "Game.h"
#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:
	Component(owner),
	mTexture(nullptr),
	mDrawOrder(drawOrder),
	mTexWidth(0),
	mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_FRect rect = {};
		
		rect.w = mTexWidth * mOwner->GetScale();
		rect.h = mTexHeight * mOwner->GetScale();

		rect.x = mOwner->GetPosition().x - rect.w / 2.0f;
		rect.y = mOwner->GetPosition().y - rect.h / 2.0f;

		SDL_RenderCopyExF(
			renderer,
			mTexture,
			nullptr,
			&rect,
			-Math::ToDegrees(mOwner->GetRotation()),
			nullptr,
			SDL_FLIP_NONE
		);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}
