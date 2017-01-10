//////////////////////////////////////////////
// Name : Scene
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////
// Class Name : Scene
//
// Over View : �V�[���̊��N���X
//////////////////////////////////////////////
class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};

	virtual void Initialize() = 0;
	virtual bool Update() = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;
};

