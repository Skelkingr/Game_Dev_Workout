#pragma once

#include "Actor.h"
#include "Game.h"
#include "SpriteComponent.h"

#include <vector>

class Tile : public Actor
{
public:
	friend class Grid;

	enum TileState
	{
		EDefault,
		EPath,
		EStart,
		EBase
	};

	Tile() = delete;
	Tile(Game* game);
	~Tile() override;

	void SetTileState(TileState state);
	
	TileState GetTileState() const { return mTileState; }
	const Tile* GetParent() const { return mParent; }

	void ToggleSelect();
private:
	std::vector<Tile*> mAdjacent;
	Tile* mParent;

	float f;
	float g;
	float h;

	bool mInOpenSet;
	bool mInClosedSet;
	bool mBlocked;

	void UpdateTexture();

	SpriteComponent* mSprite;

	TileState mTileState;

	bool mSelected;
};

