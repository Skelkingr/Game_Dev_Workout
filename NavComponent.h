#pragma once

#include "Actor.h"
#include "Math.h"
#include "MoveComponent.h"
#include "Tile.h"

class NavComponent : public MoveComponent
{
public:
	NavComponent() = delete;
	NavComponent(Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	void StartPath(const Tile* start);
	void TurnTo(const Vector2& pos);
private:
	const Tile* mNextNode;
};

