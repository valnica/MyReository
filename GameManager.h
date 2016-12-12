#pragma once

#include "Singleton.h"
#include "Direct3D.h"
#include "DirectXTK.h"

class Player;
class Camera;
class Marker;
class LandShapeCommonDef;

class GameManager:public Singleton<GameManager>
{
private:
	Player* player_;
	Camera* camera_;
	DirectX::EffectFactory* factory_;
	LandShapeCommonDef* landshapeCommondef_;

	friend class Singleton<GameManager>;

	GameManager();
public:
	~GameManager();

	void Initialize();

	Player* GetPlayer();
	Camera* GetCamera();
	
	//static GameManager* GetInstance()
	//{
	//	static GameManager* instance_ = nullptr;

	//	if (!instance_)
	//	{
	//		instance_ = new GameManager;
	//	}

	//	return instance_;
	//}
};

