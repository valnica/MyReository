//////////////////////////////////////////////
// Name : Flash
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "Flash.h"
#include "Sprite.h"
#include <SimpleMath.h>
#include <DirectXColors.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float transparentSpeed = 0.05f;

//////////////////////////////////////////////
// Name : Flash
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Flash::Flash()
	:alpha_(1.0f)
{
}

//////////////////////////////////////////////
// Name : ~Flash
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Flash::~Flash()
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
void Flash::Initialize()
{
	//�摜�̏�������
	sprite_.reset(new Sprite);
	sprite_->Initialize(L"Resources\\Images\\Flash.png", Vector2(320, 240), RECT{ 0,0,2,2 }, true, Colors::White.v, 0.0f, 320.0f);
	sprite_->SetAlpha(1.0f);
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : ����
//
// Return : �d�����I��������̔���
//////////////////////////////////////////////
bool Flash::Update()
{
	//�����x�̕ύX
	alpha_ -= transparentSpeed;

	//�A���t�@��0�ɂȂ�΂��̃N���X�̎d���I��
	if (alpha_ < 0)
		return false;

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
// Return : ����
//////////////////////////////////////////////
void Flash::Render()
{
	sprite_->Draw();
}
