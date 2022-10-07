#include "AnimSpriteComponent.h"

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		mCurrFrame += mAnimFPS + deltaTime;

		while (mCurrFrame >= mAnimTextures.size())
		{
			mCurrFrame -= mAnimTextures.size();
		}

		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}
