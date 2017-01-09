//////////////////////////////////////////////
// Name : Marker
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "Marker.h"
#include <SimpleMath.h>
#include "GameManager.h"
#include "Culling.h"

#include "Debug.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : Marker
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Marker::Marker()
{
}

//////////////////////////////////////////////
// Name : ~Marker
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Marker::~Marker()
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
void Marker::Initialize()
{
	marker_.LoadModelFromFile(L"Resources\\cModels\\Display.cmo");
	marker_.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	marker_.SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	marker_.SetScale(Vector3(2.0f, 1.5f, 1.0f));
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
void Marker::Update()
{
	marker_.Calc();

	//�����蔻��ɓo�^
	CollisionManager::GetInstance()->Entry(this);
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
void Marker::Render()
{
	marker_.Draw();

#ifdef DEBUG
	box_.Draw();
	wchar_t flag[20];
	if (Culling::InView(box_, Camera::MainCamera(), 6, 0.5f, 0.5f))
	{
		swprintf_s(flag, 20, L"In Camera = true");
	}
	else
		swprintf_s(flag, 20, L"In Camera = false");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(0, 80));
#endif
}

//////////////////////////////////////////////
// Name : SetPosition
//
// Over View : ���W�̐ݒ�
//
// Argument : ���W
//
// Return :  ����
//////////////////////////////////////////////
void Marker::SetPosition(DirectX::SimpleMath::Vector3 pos)
{
	marker_.SetTrans(pos);
	box_.Translation(pos);
}

//////////////////////////////////////////////
// Name : SetRotate
//
// Over View : ��]�p�̐ݒ�
//
// Argument : ��]�p
//
// Return :  ����
//////////////////////////////////////////////
void Marker::SetRotate(DirectX::SimpleMath::Vector3 rot)
{
	marker_.SetRotate(rot);
}

//////////////////////////////////////////////
// Name : SetScale
//
// Over View : �傫���̐ݒ�
//
// Argument : �傫��
//
// Return :  ����
//////////////////////////////////////////////
void Marker::SetScale(DirectX::SimpleMath::Vector3 scale)
{
	marker_.SetScale(scale);
}
