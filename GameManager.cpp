//////////////////////////////////////////////
// Name : GameManager
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "GameManager.h"
#include "Object3D.h"
#include "Player.h"
#include "Camera.h"
#include "LandShape.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX;

//////////////////////////////////////////////
// Name : GameManager
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
GameManager::GameManager()
{
}

//////////////////////////////////////////////
// Name : ~GameManager
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
GameManager::~GameManager()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void GameManager::Initialize()
{

	std::shared_ptr<DirectX::DGSLEffectFactory> factory;
	factory.reset(new DGSLEffectFactory(g_pd3dDevice.Get()));
	factory->SetDirectory(L"Resources\\cModels");

	//3Dオブジェクトの初期化
	Object3D::SetDevice(g_pd3dDevice.Get());
	Object3D::SetContext(g_pImmediateContext.Get());
	Object3D::SetState(g_state.get());
	Object3D::SetEffect(factory);

	//地形の初期設定
	std::shared_ptr<LandShapeCommonDef> landshapeCommondef;
	landshapeCommondef.reset(new LandShapeCommonDef);
	landshapeCommondef->device_ = g_pd3dDevice.Get();
	landshapeCommondef->deviceContext_ = g_pImmediateContext.Get();
	LandShape::InitializeCommon(landshapeCommondef);
}