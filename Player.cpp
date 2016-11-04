#include "Player.h"
#include "State.h"
#include "PlayerMove.h"
#include "Utility.h"
#include "Stage.h"

using namespace DirectX::SimpleMath;

//���f���̍s��v�Z
void Player::Calc()
{
	int a = 0;
	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Calc();
	}
}

//�R���X�g���N�^
Player::Player()
{
	state_ = new PlayerMove;
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
	//��̃I�u�W�F�N�g
	parts_[EMPTY].SetTrans(stage_->GetStartPos());
	parts_[EMPTY].SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_[EMPTY].SetScale(Vector3(1.0f, 1.0f, 1.0f));

	parts_[BODY].LoadModelFromFile(L"Resources\\cModels\\PlayerBody.cmo");
	parts_[BODY].SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	parts_[BODY].SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_[BODY].SetScale(Vector3(1.0f, 1.0f, 1.0f));
	parts_[BODY].SetParentWorld(&parts_[EMPTY].GetWorld());

	parts_[HEAD].LoadModelFromFile(L"Resources\\cModels\\PlayerHead.cmo");
	parts_[HEAD].SetTrans(Vector3(0.0f, 1.3f, 0.3f));
	parts_[HEAD].SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_[HEAD].SetScale(Vector3(1.0f, 1.0f, 1.0f));
	parts_[HEAD].SetParentWorld(&parts_[BODY].GetWorld());

	//���_�̈ʒu
	//parts_[EYE].LoadModelFromFile(L"Resources\\cModels\\PlayerHead.cmo");
	parts_[EYE].SetTrans(Vector3(0.0f, 0.1f, -0.3f));
	parts_[EYE].SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_[EYE].SetScale(Vector3(0.3f, 0.3f, 0.3f));
	parts_[EYE].SetParentWorld(&parts_[HEAD].GetWorld());
}

//�X�V����
void Player::Update()
{
	//State�p�^�[��
	State<Player>* state = state_->Input(*this);
	if (state)
	{
		delete state_;
		state_ = state;
	}
	state_->Update(*this);

	//���f���̍s��v�Z
	Calc();
}

//�`��
void Player::Render()
{
	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Draw();
	}
}

void Player::SetStage(Stage * stage)
{
	stage_ = stage;
}

//���W�̐ݒ�
void Player::SetPosition(Vector3 pos)
{
	parts_[EMPTY].SetTrans(pos);
}

//���W�̎擾
DirectX::SimpleMath::Vector3 Player::GetPosition()
{
	return parts_[EMPTY].GetTrans();
}

//��]�p�̐ݒ�
void Player::SetRotate(DirectX::SimpleMath::Vector3 rot)
{
	parts_[EMPTY].SetRotate(rot);
}

//��]�p�̎擾
DirectX::SimpleMath::Vector3 Player::GetRotate()
{
	return parts_[EMPTY].GetRotate();
}

//���p�[�c�̉�]�p�̐ݒ�
void Player::SetHeadRotate(Vector3 rot)
{
	//��̉���ɕ␳
	Clamp(-90.0f, 90.0f, rot.y);
	Clamp(-70.0f, 80.0f, rot.x);

	parts_[HEAD].SetRotate(rot);
}

//���p�[�c�̉�]�p�̎擾
Vector3 Player::GetHeadRotate()
{
	return parts_[HEAD].GetRotate();
}

//�����̍��W���擾
Vector3 Player::GetEye()
{
	return parts_[EYE].GetTrans();
}

//�����̍s����擾
Matrix Player::GetEyeMatrix()
{
	return parts_[EYE].GetWorld();
}
