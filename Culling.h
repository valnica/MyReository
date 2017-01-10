//////////////////////////////////////////////
// Class Name : Calling
//
// Author : R“c ¹–í
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include <SimpleMath.h>
#include <memory>

class Box;
class Camera;

//////////////////////////////////////////////
// Class Name : Calling
//
// Over View : ”r‘¼ˆ—
//////////////////////////////////////////////
class Culling
{
public:
	Culling();
	~Culling();

	//ƒJƒƒ‰“à‚É‚¢‚é‚©‚Ì”»’è
	static bool InView(Box& box, std::weak_ptr<Camera> camera, int required, float sx = 1.0f, float sy = 1.0f);
};