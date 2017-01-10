//////////////////////////////////////////////
// Name : GameManager
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "Singleton.h"
#include "Used\Direct3D.h"
#include "Used\DirectXTK.h"

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

