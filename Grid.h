#pragma once

#include "Actor.h"
#include "Game.h"
#include "Tile.h"

class Grid : public Actor
{
public:
	Grid() = delete;
	Grid(Game* game);

	void ProcessClick(int x, int y);

	bool FindPath(Tile* start, Tile* goal);

	void BuildTower();

	Tile* GetStartTile();
	Tile* GetEndTile();

	void UpdateActor(float deltaTime) override;
private:
	void SelectTile(size_t row, size_t col);

	void UpdatePathTiles(Tile* start);
private:
	Tile* mSelectedTile;

	std::vector<std::vector<Tile*>> mTiles;

	float mNextEnemy;

	const size_t mNumRows = 7;
	const size_t mNumCols = 16;

	const float mStartY = 192.0f;
	const float mTileSize = 64.0f;

	const float mEnemyTime = 1.5f;
};

