#include "Tile.h"

#include <string>

Tile::Tile(Game* game)
	:
	Actor(game),
	mAdjacent({}),
	mParent(nullptr),
	f(0.0f),
	g(0.0f),
	h(0.0f),
	mInOpenSet(false),
	mInClosedSet(false),
	mBlocked(false),
	mTileState(EDefault),
	mSelected()
{
	mSprite = new SpriteComponent(this);
	UpdateTexture();
}

Tile::~Tile()
{
	if (mSprite != nullptr)
	{
		delete mSprite;
		mSprite = nullptr;
	}
}

void Tile::SetTileState(TileState state)
{
	mTileState = state;
	UpdateTexture();
}

void Tile::ToggleSelect()
{
	mSelected = !mSelected;
	UpdateTexture();
}

void Tile::UpdateTexture()
{
	std::string texture;

	switch (mTileState)
	{
	case EStart:
		texture = "Assets\\TileTan.png";
		break;
	case EBase:
		texture = "Assets\\TileGreen.png";
		break;
	case EPath:
		if (mSelected)
			texture = "Assets\\TileGreySelected.png";
		else
			texture = "Assets\\TileGrey.png";
		break;
	case EDefault:
	default:
		if (mSelected)
			texture = "Assets\\TileBrownSelected.png";
		else
			texture = "Assets\\TileBrown.png";
		break;
	}

	mSprite->SetTexture(GetGame()->GetTexture(texture));
}
