#pragma once

#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(Actor* owner, int drawOrder = 100);
	
	void Update(float deltaTime) override;
	
	float GetAnimFPS() const { return this->mAnimFPS; }
	float GetCurrFrame() const { return this->mCurrFrame; }
	std::vector<SDL_Texture*> GetAnimTextures() const { return this->mAnimTextures; }
	
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
private:
	std::vector<SDL_Texture*> mAnimTextures;
	float mAnimFPS;
	float mCurrFrame;
};