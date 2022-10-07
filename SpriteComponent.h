#pragma once

#include "Actor.h"
#include "Component.h"
#include "Math.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(Actor* actor, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() { return this->mDrawOrder; }
	int GetTexWidth() { return this->mTexWidth; }
	int GetTexHeight() { return this->mTexHeight; }

	void SetTexture(SDL_Texture* texture);
private:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};
