//////////////////////////////////////////////
// Class Name : Calling
//
// Author : 山田 聖弥
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
// Over View : 排他処理
//////////////////////////////////////////////
class Culling
{
public:
	Culling();
	~Culling();

	//カメラ内にいるかの判定
	static bool InView(Box& box, std::weak_ptr<Camera> camera, int required, float sx = 1.0f, float sy = 1.0f);
};