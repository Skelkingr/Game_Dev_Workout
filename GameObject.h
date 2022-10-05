#pragma once

#include <unordered_set>

#include "Component.h"

class GameObject
{
public:
	void AddComponent(Component*);
	void RemoveComponent(Component*);
private:
	std::unordered_set<Component*> mComponents;
};