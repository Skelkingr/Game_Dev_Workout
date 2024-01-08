#pragma once

#include "Component.h"
#include "Math.h"

class CameraComponent : public Component
{
public:
	CameraComponent() = delete;
	CameraComponent(class Actor* owner, int updateOrder = 200);
	~CameraComponent() = default;
protected:
	void SetViewMatrix(const Matrix4& view);
};

