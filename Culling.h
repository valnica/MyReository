#pragma once

#include <SimpleMath.h>

class Box;
class Camera;

class Culling
{
public:
	Culling();
	~Culling();

	static bool InView(Box& box, Camera* camera, int required, float sx = 1.0f, float sy = 1.0f);
};

