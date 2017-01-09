//////////////////////////////////////////////
// Name : GameOverState
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "GameOverState.h"
#include "Player.h"

const float headRollSpeed = 0.1f;
const float rollSpeed = 50.0f;

//////////////////////////////////////////////
// Name : GameOverState
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
GameOverState::GameOverState()
	:angle_(0.0f)
{
}

//////////////////////////////////////////////
// Name : ~GameOverState
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
GameOverState::~GameOverState()
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
State<Player>* GameOverState::Input(Player & player)
{
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
void GameOverState::Update(Player & player)
{
	//��̉�]���x�̍X�V
	angle_ += headRollSpeed;
	float rot = sinf(angle_) * rollSpeed;
	player.SetHeadRotate(DirectX::SimpleMath::Vector3(-20.0f, rot, 0.0f));
}
