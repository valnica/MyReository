//////////////////////////////////////////////
// Name : Sprite
//
// Author : �R�c ����
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include "Texture.h"
#include <SimpleMath.h>
#include <DirectXColors.h>
#include <memory>

//////////////////////////////////////////////
// Class Name : Box2D
//
// Over View : 2D�p�̃{�b�N�X�����蔻��
//////////////////////////////////////////////
class Box2D
{
public:
	Box2D(float top, float left, float bottom, float right);

	//�e���_
	float top_;
	float left_;
	float bottom_;
	float right_;
};

//////////////////////////////////////////////
// Class Name : Sprite
//
// Over View : �摜�N���X
//////////////////////////////////////////////
class Sprite
{
private:
	//�摜
	std::weak_ptr<Texture> sprite_;
	
	//���W
	DirectX::SimpleMath::Vector2 pos_;
	
	//�؂���͈�
	RECT rect_;
	
	//�F
	DirectX::SimpleMath::Color color_;
	
	//��]�p
	float angle_;
	
	//�傫��
	float scale_;
	
	//�k�x
	float depth_;
	
	//�A���J�[�𒆐S�ɂ��邩�̃t���O
	bool origineFlag_;

public:
	Sprite();
	~Sprite();

	void Initialize(wchar_t* texturePass, DirectX::SimpleMath::Vector2 pos, RECT rect, bool origineFlag = false, DirectX::SimpleMath::Color = DirectX::Colors::White.v, float angle = 0.0f, float scale = 1.0f, float depth = 0.0f);
	void Draw();

	//���W�̐ݒ�
	void SetPos(DirectX::SimpleMath::Vector2 pos);
	
	//�؂���͈͂̐ݒ�
	void SetRect(RECT rect);
	
	//���W�̎擾
	DirectX::SimpleMath::Vector2 GetPos();
	
	//�A���J�[�̃t���O�ݒ�
	void SetOrigineFlag(bool flag);
	
	//�����蔻��p�̃{�b�N�X�̎擾
	Box2D GetBox();
	
	//�����x�̐ݒ�
	void SetAlpha(float alpha);
};

