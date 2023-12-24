#include "Enemy.h"
#include "Grid.h"
#include "Tower.h"

#include <algorithm>

Grid::Grid(Game* game)
	:
	Actor(game),
	mSelectedTile(nullptr)
{
	mTiles.resize(mNumRows);
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].resize(mNumCols);
	}

	for (size_t i = 0; i < mNumRows; i++)
	{
		for (size_t j = 0; j < mNumCols; j++)
		{
			mTiles[i][j] = new Tile(GetGame());
			mTiles[i][j]->SetPosition(Vector2(mTileSize / 2.0f + j * mTileSize, mStartY + i * mTileSize));
		}
	}

	GetStartTile()->SetTileState(Tile::EStart);
	GetEndTile()->SetTileState(Tile::EBase);

	for (size_t i = 0; i < mNumRows; i++)
	{
		for (size_t j = 0; j < mNumCols; j++)
		{
			if (i > 0)
				mTiles[i][j]->mAdjacent.push_back(mTiles[i - 1][j]);
			if (i < mNumRows - 1)
				mTiles[i][j]->mAdjacent.push_back(mTiles[i + 1][j]);
			if (j > 0)
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j - 1]);
			if (j < mNumCols - 1)
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j + 1]);
		}
	}

	FindPath(GetEndTile(), GetStartTile());
	UpdatePathTiles(GetStartTile());

	mNextEnemy = mEnemyTime;
}

void Grid::ProcessClick(int x, int y)
{
	y -= static_cast<int>(mStartY - mTileSize / 2);
	if (y >= 0)
	{
		x /= static_cast<int>(mTileSize);
		y /= static_cast<int>(mTileSize);

		if (x >= 0 && x < static_cast<int>(mNumCols) && y >= 0 && y < static_cast<int>(mNumRows))
		{
			SelectTile(y, x);
		}
	}
}

bool Grid::FindPath(Tile* start, Tile* goal)
{
	for (size_t i = 0; i < mNumRows; i++)
	{
		for (size_t j = 0; j < mNumCols; j++)
		{
			mTiles[i][j]->g = 0.0f;
			mTiles[i][j]->mInOpenSet = false;
			mTiles[i][j]->mInClosedSet = false;
		}
	}

	std::vector<Tile*> openSet;

	Tile* current = start;
	current->mInClosedSet = true;

	do
	{
		for (Tile* neighbor : current->mAdjacent)
		{
			if (neighbor->mBlocked)
			{
				continue;
			}

			if (!neighbor->mInClosedSet)
			{
				if (!neighbor->mInOpenSet)
				{
					neighbor->mParent = current;

					neighbor->h = (neighbor->GetPosition() - goal->GetPosition()).Length();
					neighbor->g = current->g + mTileSize;
					neighbor->f = neighbor->g + neighbor->h;

					openSet.emplace_back(neighbor);
					neighbor->mInOpenSet = true;
				}
				else
				{
					float newG = current->g + mTileSize;
					if (newG < neighbor->g)
					{
						neighbor->mParent = current;

						neighbor->g = newG;
						neighbor->f = neighbor->g + neighbor->h;
					}
				}
			}
		}

		if (openSet.empty())
		{
			break;
		}

		auto iter = std::min_element(
			openSet.begin(),
			openSet.end(),
			[](Tile* a, Tile* b) {
				return a->f < b->f;
			}
		);

		current = *iter;
		openSet.erase(iter);
		current->mInOpenSet = false;
		current->mInClosedSet = true;

	} while (current != goal);

	return (current == goal) ? true : false;
}

void Grid::BuildTower()
{
	if (mSelectedTile && !mSelectedTile->mBlocked)
	{
		mSelectedTile->mBlocked = true;
		if (FindPath(GetEndTile(), GetStartTile()))
		{
			Tower* t = new Tower(GetGame());
			t->SetPosition(mSelectedTile->GetPosition());
		}
		else
		{
			mSelectedTile->mBlocked = false;
			FindPath(GetEndTile(), GetStartTile());
		}

		UpdatePathTiles(GetStartTile());
	}
}

Tile* Grid::GetStartTile()
{
	return mTiles[3][0];
}

Tile* Grid::GetEndTile()
{
	return mTiles[3][15];
}

void Grid::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	mNextEnemy -= deltaTime;
	if (mNextEnemy <= 0.0f)
	{
		new Enemy(GetGame());
		mNextEnemy += mEnemyTime;
	}
}

void Grid::SelectTile(size_t row, size_t col)
{
	Tile::TileState tState = mTiles[row][col]->GetTileState();
	if (tState != Tile::EStart && tState != Tile::EBase)
	{
		if (mSelectedTile)
		{
			mSelectedTile->ToggleSelect();
		}
		mSelectedTile = mTiles[row][col];
		mSelectedTile->ToggleSelect();
	}
}

void Grid::UpdatePathTiles(Tile* start)
{
	for (size_t i = 0; i < mNumRows; i++)
	{
		for (size_t j = 0; j < mNumCols; j++)
		{
			if (!(i == 3 && j == 0) && !(i == 3 && j == 15))
			{
				mTiles[i][j]->SetTileState(Tile::EDefault);
			}
		}
	}

	Tile* t = start->mParent;
	while (t != GetEndTile())
	{
		t->SetTileState(Tile::EPath);
		t = t->mParent;
	}
}
