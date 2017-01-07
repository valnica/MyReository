#include "GameManager.h"
#include "Object3D.h"
#include "Player.h"
#include "Camera.h"
#include "LandShape.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX;

GameManager::GameManager()
{
	landshapeCommondef_ = new LandShapeCommonDef;
}

GameManager::~GameManager()
{
	if (landshapeCommondef_)
		delete landshapeCommondef_;
}

void GameManager::Initialize()
{
	factory_.reset(new DGSLEffectFactory(g_pd3dDevice.Get()));
	factory_->SetDirectory(L"Resources\\cModels");

	//3Dオブジェクトの初期化
	Object3D::SetDevice(g_pd3dDevice.Get());
	Object3D::SetContext(g_pImmediateContext.Get());
	Object3D::SetState(g_state.get());
	Object3D::SetEffect(factory_);
	//Object3D::SetCamera(camera_);

	//地形の初期設定
	//landshapeCommondef_->camera_ = camera_;
	landshapeCommondef_->device_ = g_pd3dDevice.Get();
	landshapeCommondef_->deviceContext_ = g_pImmediateContext.Get();
	LandShape::InitializeCommon(landshapeCommondef_);
}