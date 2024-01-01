#include "MeshComponent.h"

#include "Game.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

MeshComponent::MeshComponent(Actor* owner)
	:
	Component(owner),
	mMesh(nullptr),
	mTextureIndex(0)
{
	mOwner->GetGame()->GetRenderer()->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveMeshComponent(this);
}

void MeshComponent::Draw(Shader* shader)
{
	if (mMesh)
	{
		shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
		shader->SetFloatUniform("uSpecPower", mMesh->GetSpecPower());

		Texture* texture = mMesh->GetTexture(mTextureIndex);
		if (texture)
		{
			texture->SetActive();
		}

		VertexArray* vertexArray = mMesh->GetVertexArray();
		vertexArray->SetActive();

		glDrawElements(GL_TRIANGLES, vertexArray->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
}
