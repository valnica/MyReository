//////////////////////////////////////////////
// Name : Player
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "Player.h"
#include "State.h"
#include "Utility.h"
#include "Stage.h"
#include "CollisionManager.h"
#include "TPSMode.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : Calc
//
// Over View : ���[���h�v�Z
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void Player::Calc()
{
	int a = 0;
	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Calc();
	}
}

//////////////////////////////////////////////
// Name : Player
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Player::Player()
{
}

//////////////////////////////////////////////
// Name : ~Player
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Player::~Player()
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
void Player::Initialize()
{
	//��̃I�u�W�F�N�g
	parts_[EMPTY].SetTrans(Vector3(0.0f, 0.0f, 0.0f));
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
	parts_[EYE].SetTrans(Vector3(0.0f, 0.1f, -0.3f));
	parts_[EYE].SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_[EYE].SetScale(Vector3(0.3f, 0.3f, 0.3f));
	parts_[EYE].SetParentWorld(&parts_[HEAD].GetWorld());

	//�����蔻��p�̃��f���̏�����
	collisionBody_.Initialize();
	collisionBody_.SetTrans(Vector3(0.0f, 0.85f, 0.3f));
	collisionBody_.SetLocalRadius(1.0f);
	collisionBody_.SetParentMatrix(&parts_[EMPTY].GetLocalWorld());
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ����������
//
// Argument : state
//
// Return :  ����
//////////////////////////////////////////////
void Player::Initialize(std::shared_ptr<State<Player>> state)
{
	state_ = state;
	Initialize();
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
void Player::Update()
{
	//State�p�^�[��
	std::weak_ptr<State<Player>> state = state_.lock()->Input(*this);
	if (state.lock())
	{
		state_ = state;
	}
	state_.lock()->Update(*this);

	//���f���̍s��v�Z
	Calc();

	collisionBody_.Update();

	//�����蔻��ɓo�^
	CollisionManager::GetInstance()->Entry(this);

#ifdef DEBUG
	//�f�o�b�O�t���O�̏�����
	debugFlag_ = false;
#endif
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
void Player::Render()
{
	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Draw();
	}

	collisionBody_.Draw();

#ifdef DEBUG
	wchar_t flag[20];
	if (debugFlag_)
		swprintf_s(flag, 20, L"PlayerFront = true");
	else
		swprintf_s(flag, 20, L"PlayerFront = false");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(0, 100));
#endif //�f�o�b�O
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
void Player::SetPosition(Vector3 pos)
{
	parts_[EMPTY].SetTrans(pos);
}

//////////////////////////////////////////////
// Name : GetPosition
//
// Over View : ���W�̎擾
//
// Argument : ����
//
// Return :  ���W
//////////////////////////////////////////////
DirectX::SimpleMath::Vector3 Player::GetPosition()
{
	return parts_[EMPTY].GetTrans();
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
void Player::SetRotate(DirectX::SimpleMath::Vector3 rot)
{
	parts_[EMPTY].SetRotate(rot);
}

//////////////////////////////////////////////
// Name : GetRotate
//
// Over View : ��]�p�̎擾
//
// Argument : ����
//
// Return :  ��]�p
//////////////////////////////////////////////
DirectX::SimpleMath::Vector3 Player::GetRotate()
{
	return parts_[EMPTY].GetRotate();
}

//////////////////////////////////////////////
// Name : SetHeadRotate
//
// Over View : ���̉�]�p�̐ݒ�
//
// Argument : ��]�p
//
// Return :  ����
//////////////////////////////////////////////
void Player::SetHeadRotate(Vector3 rot)
{
	//��̉���ɕ␳
	Clamp(-90.0f, 90.0f, rot.y);
	Clamp(-20.0f, 80.0f, rot.x);

	parts_[HEAD].SetRotate(rot);
}

//////////////////////////////////////////////
// Name : GetHeadRotate
//
// Over View : ��]�p�̎擾
//
// Argument : ����
//
// Return :  ��]�p
//////////////////////////////////////////////
Vector3 Player::GetHeadRotate()
{
	return parts_[HEAD].GetRotate();
}

//////////////////////////////////////////////
// Name : GetEyePosition
//
// Over View : �ڂ̍��W�擾
//
// Argument : ����
//
// Return : �ڂ̍��W
//////////////////////////////////////////////
Vector3 Player::GetEyePosition()
{
	Vector3 pos;
	Quaternion qua;
	Vector3 scale;
	parts_[EYE].GetWorld().Decompose(scale, qua, pos);
	return pos;
}

//////////////////////////////////////////////
// Name : GetEyeMatrix
//
// Over View : �ڂ̍s����擾
//
// Argument : ����
//
// Return : �ڂ̃��[���h
//////////////////////////////////////////////
Matrix Player::GetEyeMatrix()
{
	return parts_[EYE].GetWorld();
}

//////////////////////////////////////////////
// Name : Found
//
// Over View : ���������ʒm
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void Player::Found()
{
#ifdef DEBUG
	debugFlag_ = true;
#endif
}
