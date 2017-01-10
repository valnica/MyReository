//////////////////////////////////////////////
// Class Name : Calling
//
// Author : �R�c ����
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
// Over View : �r������
//////////////////////////////////////////////
class Culling
{
public:
	Culling();
	~Culling();

	//�J�������ɂ��邩�̔���
	static bool InView(Box& box, std::weak_ptr<Camera> camera, int required, float sx = 1.0f, float sy = 1.0f);
};