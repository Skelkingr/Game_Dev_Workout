#pragma once

#include "Math.h"

#include <SDL/SDL.h>

#include <string>
#include <unordered_map>
#include <vector>

struct DirectionalLight
{
	Vector3 mDirection;
	Vector3 mDiffuseColor;
	Vector3 mSpecColor;
};

class Renderer
{
public:
	Renderer() = delete;
	Renderer(class Game* game);
	~Renderer() = default;

	bool Initialize(float screenWidth, float screenHeight);
	void Shutdown();

	void UnloadData();

	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMeshComponent(class MeshComponent* mesh);
	void RemoveMeshComponent(class MeshComponent* mesh);

	class Mesh* GetMesh(const std::string& fileName);
	class Texture* GetTexture(const std::string& fileName);

	void SetViewMatrix(const Matrix4& view) { mView = view; }

	void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }
private:
	bool LoadShaders();
	void CreateSpriteVerts();
	void SetLightUniforms(class Shader* shader) const;
private:
	std::unordered_map<std::string, class Mesh*> mMeshes;
	std::unordered_map<std::string, class Texture*> mTextures;

	std::vector<class MeshComponent*> mMeshComps;
	std::vector<class SpriteComponent*> mSprites;

	class Game* mGame;

	class Shader* mMeshShader;
	class Shader* mSpriteShader;

	class VertexArray* mSpriteVerts;

	Matrix4 mView;
	Matrix4 mProjection;

	float mScreenWidth;
	float mScreenHeight;

	Vector3 mAmbientLight;
	DirectionalLight mDirLight;

	SDL_Window* mWindow;
	SDL_GLContext mContext;
};

