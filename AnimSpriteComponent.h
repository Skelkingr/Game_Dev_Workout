#pragma once

#include "SDL.h"
#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	
	void Update(float deltaTime) override;
	
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float animFPS) { mAnimFPS = animFPS; }
	std::vector<SDL_Texture*> GetAnimTextures() const { return mAnimTextures; }
	
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
private:
	std::vector<SDL_Texture*> mAnimTextures;
	float mAnimFPS;
	float mCurrFrame;
};