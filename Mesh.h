#pragma once

#include <string>
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh() = default;

	bool Load(const std::string& fileName, class Renderer* renderer);
	void Unload();

	class Texture* GetTexture(size_t index);
	
	class VertexArray* GetVertexArray() const { return mVertexArray; }

	const std::string& GetShaderName() const { return mShaderName; }

	float GetRadius() const { return mRadius; }
	float GetSpecPower() const { return mSpecPower; }
private:
	std::vector<class Texture*> mTextures;

	class VertexArray* mVertexArray;

	std::string mShaderName;

	float mRadius;

	float mSpecPower;
};

