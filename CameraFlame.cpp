//////////////////////////////////////////////
// Name : CameraFlame
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "CameraFlame.h"
#include "Sprite.h"
#include "DirectXTK.h"

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : CameraFlame
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
CameraFlame::CameraFlame()
{
}


//////////////////////////////////////////////
// Name : ~CameraFlame
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
CameraFlame::~CameraFlame()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ����������
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void CameraFlame::Initialize()
{
	sprite_.reset(new Sprite);
	sprite_->Initialize(L"Resources\\Images\\Flame.png", Vector2(WINDOW_W / 2.0f, WINDOW_H / 2.0f), { 0,0,64,48 }, true);
	sprite_->SetScale(5.0f);

	count_ = 1;
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : ����
//
// Return :  �������I��������̔���
//////////////////////////////////////////////
bool CameraFlame::Update()
{
	count_--;

	if (count_ < 0)
		return false;

	return true;
}

//////////////////////////////////////////////
// Name : Render
//
// Over View : �`�揈��
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void CameraFlame::Render()
{
	sprite_->Draw();
}
