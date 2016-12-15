#pragma once

#include "State.h"

class Camera;

class FPSCamera :public State<Camera>, public Singleton<FPSCamera>
{
private:

	friend class Singleton<FPSCamera>;

	FPSCamera();
public:
	~FPSCamera();

	State<Camera>* Input(Camera& camera);
	void Update(Camera& camera);
};

