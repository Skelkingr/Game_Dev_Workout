#include "PlaneActor.h"

#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"

PlaneActor::PlaneActor(Game* game)
	:
	Actor(game)
{
	SetScale(10.0f);
	
	MeshComponent* meshComp = new MeshComponent(this);
	meshComp->SetMesh(GetGame()->GetRenderer()->GetMesh("Meshes/Plane.gpmesh"));
}
