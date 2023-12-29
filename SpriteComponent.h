#pragma once

#include "Component.h"
#include "Shader.h"

#include <SDL.h>

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* actor, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(Shader* shader);
	virtual void SetTexture(Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexWidth() const { return mTexWidth; }
	int GetTexHeight() const { return mTexHeight; }

	void SetDrawOrder(int drawOrder) { mDrawOrder = drawOrder; }
private:
	Texture* mTexture;

	int mDrawOrder;

	int mTexWidth;
	int mTexHeight;
};
