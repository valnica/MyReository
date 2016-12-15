#pragma once

#include <SimpleMath.h>
#include <memory>

class Box;
class Camera;

class Culling
{
public:
	Culling();
	~Culling();

	static bool InView(Box& box, std::weak_ptr<Camera> camera, int required, float sx = 1.0f, float sy = 1.0f);
};