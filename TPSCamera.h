#pragma once

#include "State.h"
#include "Camera.h"
#include <SimpleMath.h>

class TPSCamera:public State<Camera>
{
private:
	const float distance_ = 10;
	DirectX::SimpleMath::Vector3 rotate_;

public:
	TPSCamera();
	~TPSCamera();

	State<Camera>* Input(Camera& camera) override;
	void Update(Camera& camera) override;
};

