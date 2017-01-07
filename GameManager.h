//////////////////////////////////////////////
// Name : GameManager
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
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
// Over View : ゲームに使うクラスの初期化
//////////////////////////////////////////////
class GameManager:public Singleton<GameManager>
{
private:
	std::shared_ptr<DirectX::DGSLEffectFactory> factory_;
	LandShapeCommonDef* landshapeCommondef_;

	friend class Singleton<GameManager>;

	GameManager();
public:
	~GameManager();

	void Initialize();
};

