#pragma once

#include "Object3D.h"
#include "CollisionManager.h"

class ClearMarker
{
private:
	Object3D marker_;
	Box box_;

public:
	ClearMarker();
	~ClearMarker();

	void Initialize();
	void Update();
	void Render();

	Box& GetBox() { return box_; }
};

