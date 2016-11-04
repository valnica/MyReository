#pragma once

#include <vector>
#include <SimpleMath.h>
#include "Object3D.h"

class Enemy
{
private:
	std::vector<DirectX::SimpleMath::Vector3> movePoint_;
	Object3D parts_;

public:
	Enemy();
	~Enemy();

	void Initialize();
	void Update();
	void Render();

	void SetMovePoint(std::vector<DirectX::SimpleMath::Vector3> movePoint);
};

