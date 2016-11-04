#include "GameManager.h"
#include "Object3D.h"
#include "Player.h"
#include "Camera.h"
#include "LandShape.h"

using namespace DirectX;

GameManager::GameManager()
{
	player_ = new Player;
	camera_ = new Camera(480, 640);
	factory_ = new EffectFactory(g_pd3dDevice.Get());
	landshapeCommondef_ = new LandShapeCommonDef;
}

GameManager::~GameManager()
{
	if (camera_)
		delete camera_;

	if (factory_)
		delete factory_;

	if (landshapeCommondef_)
		delete landshapeCommondef_;
}

void GameManager::Initialize()
{
	factory_->SetDirectory(L"Resources\\cModels");

	//3Dオブジェクトの初期化
	Object3D::SetDevice(g_pd3dDevice.Get());
	Object3D::SetContext(g_pImmediateContext.Get());
	Object3D::SetState(g_state.get());
	Object3D::SetEffect(factory_);
	Object3D::SetCamera(camera_);

	//地形の初期設定
	landshapeCommondef_->camera_ = camera_;
	landshapeCommondef_->device_ = g_pd3dDevice.Get();
	landshapeCommondef_->deviceContext_ = g_pImmediateContext.Get();
	LandShape::InitializeCommon(landshapeCommondef_);
}

Player * GameManager::GetPlayer()
{
	return player_;
}

Camera* GameManager::GetCamera()
{
	return camera_;
}
