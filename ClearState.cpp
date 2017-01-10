//////////////////////////////////////////////
// Name : ClearState
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "ClearState.h"
#include "Player.h"

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : ClearState
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
ClearState::ClearState()
	:angle_(0.0f)
{
}

//////////////////////////////////////////////
// Name : ~ClearState
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
ClearState::~ClearState()
{
}

//////////////////////////////////////////////
// Name : Input
//
// Over View : State�̐؂�ւ�����
//
// Argument : player�ւ̎Q��
//
// Return : State�̃|�C���^
//////////////////////////////////////////////
std::shared_ptr<State<Player>> ClearState::Input(Player & player)
{
	//�J�ڏ����ƑJ�ڐ�̃|�C���^��ݒ肷��


	return nullptr;
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : ����
//
// Return : ���� 
//////////////////////////////////////////////
void ClearState::Update(Player & player)
{
	//�v���C���[�̓��̉�]
	angle_ += 0.1f;
	float rad = sinf(angle_) * 30;

	player.SetHeadRotate(Vector3(rad, 0.0f, 0.0f));
}