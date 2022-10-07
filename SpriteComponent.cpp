#include "SpriteComponent.h"

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect rect;
		
		rect.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		rect.h = static_cast<int>(mTexHeight * mOwner->GetScale());

		rect.x = static_cast<int>(mOwner->GetPosition().x - rect.w / 2);
		rect.y = static_cast<int>(mOwner->GetPosition().y - rect.h / 2);

		SDL_RenderCopyEx(
			renderer,
			mTexture,
			nullptr,
			&rect,
			- Math::ToDegrees(mOwner->GetRotation()),
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
