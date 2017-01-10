//////////////////////////////////////////////
// Name : GameManager
//
// Author : �R�c ����
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
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
GameManager::GameManager()
{
}

//////////////////////////////////////////////
// Name : ~GameManager
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
GameManager::~GameManager()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ��������
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void GameManager::Initialize()
{

	std::shared_ptr<DirectX::DGSLEffectFactory> factory;
	factory.reset(new DGSLEffectFactory(g_pd3dDevice.Get()));
	factory->SetDirectory(L"Resources\\cModels");

	//3D�I�u�W�F�N�g�̏�����
	Object3D::SetDevice(g_pd3dDevice.Get());
	Object3D::SetContext(g_pImmediateContext.Get());
	Object3D::SetState(g_state.get());
	Object3D::SetEffect(factory);

	//�n�`�̏����ݒ�
	std::shared_ptr<LandShapeCommonDef> landshapeCommondef;
	landshapeCommondef.reset(new LandShapeCommonDef);
	landshapeCommondef->device_ = g_pd3dDevice.Get();
	landshapeCommondef->deviceContext_ = g_pImmediateContext.Get();
	LandShape::InitializeCommon(landshapeCommondef);
}