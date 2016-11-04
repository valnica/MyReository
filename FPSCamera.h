#pragma once

#include "State.h"
class Camera;

class FPSCamera:public State<Camera>
{
private:

public:
	FPSCamera();
	~FPSCamera();

	State<Camera>* Input(Camera& camera);
	void Update(Camera& camera);
};

