#include "Enemy.h"

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
	parts_.SetTrans(Vector3(0.0f, 0.0f, 0.0f));
	parts_.SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	parts_.SetScale(Vector3(1.0f, 1.0f, 1.0f));
}

void Enemy::Update()
{
	parts_.Calc();
}

void Enemy::Render()
{
	parts_.Draw();
}

void Enemy::SetMovePoint(std::vector<DirectX::SimpleMath::Vector3> movePoint)
{
	movePoint_ = movePoint;
}
