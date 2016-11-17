#include "Enemy.h"
#include "Debug.h"
#include "GameManager.h"
#include "Player.h"
#include "CollisionManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	movePoint_.DataAllDelete();
}

void Enemy::Initialize()
{
	//��̃I�u�W�F�N�g
	parts_[EMPTY].SetTrans(movePoint_.Top()->GetData());
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

	now_ = movePoint_.Top();
	moveCount_ =(int)((now_->next_->GetData() - now_->GetData()).Length() / moveSpeed_ * 60);
	waitTime_ = 60; 
	currentCount_ = 0;
	viewAngle_ = 45.0f;
	viewDistance_ = 30.0f;
}

void Enemy::Update()
{
	currentCount_++;

	//�K�����Ԃ��v�Z
	float time = (float)currentCount_ / moveCount_;
	if (time > 1.0f)
		time = 1.0f;

	//���`��Ԃňړ�
	Vector3 vec = now_->GetData() + time * (now_->next_->GetData() - now_->GetData());
	parts_[EMPTY].SetTrans(vec);

	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Calc();
	}
	//�L�����N�^�[�̉�]
	vec = now_->next_->GetData() - now_->GetData();
	float rad = atan2f(-vec.x, -vec.z);
	parts_[EMPTY].SetRotate(Vector3(0.0f, rad * 180.0f /3.14f , 0.0f));

	//���̖ڕW���W�X�V
	if (currentCount_ >= moveCount_ + waitTime_)
	{
		currentCount_ = 0;
		now_ = now_->next_;
		moveCount_ = (int)((now_->next_->GetData() - now_->GetData()).Length() / moveSpeed_ * 60);
	}

	CollisionManager::GetInstance()->Entry(this);
}

void Enemy::Render()
{
	for (int i = 0; i < NUM_PARTS; i++)
	{
		parts_[i].Draw();
	}

	//�v���C���[��������ɂ��邩�ǂ����̃f�o�b�O
	{
		//�f�o�b�O�@�����Ă��������`��
		Vector3 dir(0.0f, 0.0f, -viewDistance_);
		Matrix rot = Matrix::CreateRotationY(parts_[EMPTY].GetRotate().y * 3.14f / 180);
		Vector3 vec = Vector3::TransformNormal(dir, rot);
		Debug::GetInstance()->DrawLine(parts_[EMPTY].GetTrans(), parts_[EMPTY].GetTrans() + vec);

		//����̃f�o�b�O
		rot = Matrix::CreateRotationY((parts_[EMPTY].GetRotate().y + viewAngle_) * 3.14f / 180.0f);
		vec = Vector3::TransformNormal(dir, rot);
		Debug::GetInstance()->DrawLine(parts_[EMPTY].GetTrans(), parts_[EMPTY].GetTrans() + vec);

		rot = Matrix::CreateRotationY((parts_[EMPTY].GetRotate().y - viewAngle_) * 3.14f / 180.0f);
		vec = Vector3::TransformNormal(dir, rot);
		Debug::GetInstance()->DrawLine(parts_[EMPTY].GetTrans(),parts_[EMPTY].GetTrans() + vec);
	}

}

void Enemy::SetMovePoint(List<DirectX::SimpleMath::Vector3> movePoint)
{
	movePoint_ = movePoint;
}