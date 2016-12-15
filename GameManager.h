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
	std::shared_ptr<DirectX::EffectFactory> factory_;
	LandShapeCommonDef* landshapeCommondef_;

	friend class Singleton<GameManager>;

	GameManager();
public:
	~GameManager();

	void Initialize();
};

