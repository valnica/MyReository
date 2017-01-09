//////////////////////////////////////////////
// Name : Sprite
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "Sprite.h"
#include "SpriteManager.h"
#include "DirectXTK.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : Box2D
//
// Over View : �R���X�g���N�^
//
// Argument : �{�b�N�X�̂S���_�̍��W
//////////////////////////////////////////////
Box2D::Box2D(float top, float left, float bottom, float right)
	:top_(top), left_(left)
	, bottom_(bottom), right_(right)
{

}

//////////////////////////////////////////////
// Name : Sprite
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Sprite::Sprite()
{
	pos_ = Vector2::Zero;
	rect_ = RECT{ 0,0,0,0 };
	color_ = Colors::White.v;
	angle_ = 0.0f;
	scale_ = 0.0f;
	depth_ = 0.0f;
}

//////////////////////////////////////////////
// Name : ~Sprite
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Sprite::~Sprite()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ����������
//
// Argument : �摜�̃p�X�A���W�A�؂���͈́A
//            �A���J�[�𒆐S�ɂ��邩�̃t���O�A�F�A
//            ��]�p�A�傫���A�k�x
//
// Return :  ����
//////////////////////////////////////////////
void Sprite::Initialize(wchar_t * texturePass, DirectX::SimpleMath::Vector2 pos, RECT rect, bool origineFlag, Color color, float angle, float scale, float depth)
{
	sprite_ = SpriteManager::GetInstance()->LoadSprite(texturePass);
	pos_ = pos;
	rect_ = rect;
	origineFlag_ = origineFlag;
	color_ = color;
	angle_ = 3.14f / 180.0f * angle;
	scale_ = scale;
	depth_ = depth;
}

//////////////////////////////////////////////
// Name : Draw
//
// Over View : �`�揈��
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void Sprite::Draw()
{
	//�N�_�̐ݒ�
	Vector2 origine(0.0f, 0.0f);

	//flag��true�Ȃ�Ή摜�̒��S���N�_�ɕ`��
	if (origineFlag_)
		origine = Vector2((rect_.right - rect_.left) / 2.0f, (rect_.bottom - rect_.top) / 2.0f);
	g_spriteBatch->Draw(sprite_.lock()->m_pTexture, pos_, &rect_, color_, angle_, origine, scale_, SpriteEffects_None, depth_);
}

//////////////////////////////////////////////
// Name : SetPos
//
// Over View : ���W�̐ݒ�
//
// Argument : ���W
//
// Return :  ����
//////////////////////////////////////////////
void Sprite::SetPos(DirectX::SimpleMath::Vector2 pos)
{
	pos_ = pos;
}

//////////////////////////////////////////////
// Name : SetRect
//
// Over View : �؂���͈͂̐ݒ�
//
// Argument : �؂���͈�
//
// Return :  ����
//////////////////////////////////////////////
void Sprite::SetRect(RECT rect)
{
	rect_ = rect;
}

//////////////////////////////////////////////
// Name : GetPos
//
// Over View : ���W�̐ݒ�
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
DirectX::SimpleMath::Vector2 Sprite::GetPos()
{
	return pos_;
}

//////////////////////////////////////////////
// Name : SetOrigineFlag
//
// Over View : �A���J�[�𒆐S�ɂ���t���O�̐ݒ�
//
// Argument : �A���J�[�𒆐S�ɂ���t���O
//
// Return :  ����
//////////////////////////////////////////////
void Sprite::SetOrigineFlag(bool flag)
{
	origineFlag_ = flag;
}

//////////////////////////////////////////////
// Name : GetBox
//
// Over View : �����蔻��p�̃{�b�N�X�̎擾
//
// Argument : ����
//
// Return :  �{�b�N�X
//////////////////////////////////////////////
Box2D Sprite::GetBox()
{
	if (origineFlag_)
	{
		float offsetX = (rect_.right - rect_.left) / 2.0f;
		float offsetY = (rect_.bottom + rect_.top) / 2.0f;
		return Box2D(pos_.y - offsetY, pos_.x - offsetX, pos_.y + offsetY, pos_.x + offsetX);
	}
	return Box2D(pos_.y, pos_.x, pos_.y + (rect_.bottom + rect_.top), pos_.x + (rect_.right - rect_.left));
}

//////////////////////////////////////////////
// Name : SetAlpha
//
// Over View : �����x�̐ݒ�
//
// Argument : �����x
//
// Return :  ����
//////////////////////////////////////////////
void Sprite::SetAlpha(float alpha)
{
	color_.A(alpha);
}


