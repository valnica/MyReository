//////////////////////////////////////////////
// Name : GameManager
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include "Singleton.h"
#include "Direct3D.h"
#include "DirectXTK.h"

class Player;
class Camera;
class Marker;
class LandShapeCommonDef;

//////////////////////////////////////////////
// Class Name : GameManager
//
// Over View : �Q�[���Ɏg���N���X�̏�����
//////////////////////////////////////////////
class GameManager:public Singleton<GameManager>
{
private:

	friend class Singleton<GameManager>;

	GameManager();
public:
	~GameManager();

	void Initialize();
};

