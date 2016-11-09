#include "Enemy.h"
#include "Debug.h"
#include "GameManager.h"
#include "Player.h"
#include "CollisionManager.h"

using namespace DirectX::SimpleMath;

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	parts_.LoadModelFromFile(L"Resources\\cModels\\Enemy.cmo");
	parts_.SetTrans(movePoint_.Top()->GetData());
	parts_.SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_.SetScale(Vector3(1.0f, 1.0f, 1.0f));

	now_ = movePoint_.Top();
	moveCount_ = (now_->next_->GetData() - now_->GetData()).Length() / moveSpeed_ * 60;
	waitTime_ = 60; 
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
	parts_.SetTrans(vec);

	parts_.Calc();

	//�L�����N�^�[�̉�]
	vec = now_->next_->GetData() - now_->GetData();
	float rad = atan2f(-vec.x, -vec.z);
	parts_.SetRotate(Vector3(0.0f, rad * 180.0f /3.14f , 0.0f));

	//���̖ڕW���W�X�V
	if (currentCount_ >= moveCount_ + waitTime_)
	{
		currentCount_ = 0;
		now_ = now_->next_;
		moveCount_ = (now_->next_->GetData() - now_->GetData()).Length() / moveSpeed_ * 60;
	}

	CollisionManager::GetInstance()->Entry(this);
}

void Enemy::Render()
{
	parts_.Draw();


	//�v���C���[��������ɂ��邩�ǂ����̃f�o�b�O
	{
		//�f�o�b�O�@�����Ă��������`��
		Vector3 dir(0.0f, 0.0f, -viewDistance_);
		Matrix rot = Matrix::CreateRotationY(parts_.GetRotate().y * 3.14f / 180);
		Vector3 vec = Vector3::TransformNormal(dir, rot);
		Debug::GetInstance()->DrawLine(parts_.GetTrans(), parts_.GetTrans() + vec);

		//����̃f�o�b�O
		rot = Matrix::CreateRotationY((parts_.GetRotate().y + viewAngle_) * 3.14f / 180.0f);
		vec = Vector3::TransformNormal(dir, rot);
		Debug::GetInstance()->DrawLine(parts_.GetTrans(), parts_.GetTrans() + vec);

		rot = Matrix::CreateRotationY((parts_.GetRotate().y - viewAngle_) * 3.14f / 180.0f);
		vec = Vector3::TransformNormal(dir, rot);
		Debug::GetInstance()->DrawLine(parts_.GetTrans(),parts_.GetTrans() + vec);
	}

}

void Enemy::SetMovePoint(List<DirectX::SimpleMath::Vector3> movePoint)
{
	movePoint_ = movePoint;
}