//////////////////////////////////////////////
// Name : ClearFlagInfo
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "ClearFlagInfo.h"
#include "Sprite.h"
#include "DirectXTK.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : CameraFlame
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
ClearFlagInfo::ClearFlagInfo()
{
}

//////////////////////////////////////////////
// Name : CameraFlame
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
ClearFlagInfo::~ClearFlagInfo()
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
void ClearFlagInfo::Initialize()
{
	sprite_.reset(new Sprite);
	sprite_->Initialize(L"Resources\\Images\\CharData.png", Vector2(WINDOW_W / 2.0f, WINDOW_H / 4.0f * 3.0f + 20.0f), RECT{ 0,0,448,64 }, true);

	alpha_ = 1.0f;
	count_ = 60;
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
bool ClearFlagInfo::Update()
{
	if (count_ > 0)
		count_--;
	else
		alpha_ -= 0.05f;

	sprite_->SetAlpha(alpha_);

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
void ClearFlagInfo::Render()
{
	sprite_->Draw();
}
