#pragma once

#include "Object3D.h"
#include "CollisionManager.h"

class Marker
{
private:
	Object3D marker_;
	Box box_;

public:
	Marker();
	~Marker();

	void Initialize();
	void Update();
	void Render();

	Box& GetBox() { return box_; }
	DirectX::SimpleMath::Vector3 GetPos() { return marker_.GetTrans(); }
	void SetPosition(DirectX::SimpleMath::Vector3 pos);
	void SetRotate(DirectX::SimpleMath::Vector3 rot);
};

