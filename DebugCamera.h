#pragma once
#include "State.h"
#include <SimpleMath.h>

class Camera;

class DebugCamera :
	public State<Camera>
{
private:
	float distance_;
	DirectX::SimpleMath::Vector3 rotate_;

public:
	DebugCamera();
	~DebugCamera();

	State<Camera>* Input(Camera& camera);
	void Update(Camera& camera);
};

