//////////////////////////////////////////////
// Name : FPSMode
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "FPSMode.h"
#include "Player.h"
#include "Stage.h"
#include "Marker.h"
#include "Culling.h"
#include "GameManager.h"
#include "Collision.h"
#include "TPSMode.h"
#include "TaskManager.h"
#include "Flash.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : FPSMode
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
FPSMode::FPSMode()
{
}

//////////////////////////////////////////////
// Name : ~FPSMode
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
FPSMode::~FPSMode()
{
}

//////////////////////////////////////////////
// Name : Input
//
// Over View : State�؂�ւ�
//
// Argument : �v���C���[�̎Q��
//
// Return :  ����
//////////////////////////////////////////////
State<Player> * FPSMode::Input(Player& player)
{
	//�J�ڏ����ƑJ�ڐ�
	if (g_mouseTracker->rightButton == g_mouseTracker->RELEASED)
	{
		return new TPSMode;
	}
	return nullptr;
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : �v���C���[�̎Q��
//
// Return :  ����
//////////////////////////////////////////////
void FPSMode::Update(Player & player)
{
	//���N���b�N�Ŏʐ^���B��
	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		TaskManager::GetInstance()->Add<Flash>()->Initialize();
		Collision collision;

		if (collision.MarkerInView())
		{
			Stage::SetClearFlag();
		}
	}

	//�J�����̈ړ��ʎ擾
	Vector2 amountOfMoment = Vector2((float)g_mouse.x, (float)g_mouse.y);

	float angle = 0;

	angle -= amountOfMoment.x;

	//��]�p�̕ύX
	Vector3 rot = player.GetRotate();
	Matrix rotY = Matrix::CreateRotationY(rot.y * 3.14f / 180.0f);

	player.SetRotate(player.GetRotate() + Vector3(0.0f, angle, 0.0f));
	player.SetHeadRotate(player.GetHeadRotate() + Vector3(-amountOfMoment.y, 0.0f, 0.0f));
}