#include "CollisionNode.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

bool CollisionNode::debugVisible_ = false;

SphereNode::SphereNode()
{
	localRadius_ = 1.0f;
}

void SphereNode::Initialize()
{
	object_.LoadModelFromFile(L"Resources\\cModels\\HitSphere.cmo");
}

void SphereNode::Update()
{
	object_.SetTrans(trans_);
	Vector3 localScale;

	localScale = Vector3(1, 1, 1);

	localScale.x = localRadius_;
	localScale.y = localRadius_;
	localScale.z = localRadius_;
	object_.SetScale(localScale);

	object_.Calc();

	Matrix world = object_.GetWorld();
	Vector3 center(0.0f, 0.0f, 0.0f);
	Vector3 right(1.0f, 0.0f, 0.0f);

	center = Vector3::Transform(center, world);
	right = Vector3::Transform(right, world);

	center_ = center;
	radius_ = Vector3::Distance(center, right);
}

void SphereNode::Draw()
{
	if (CollisionNode::GetDebugVisible())
		object_.Draw();
}

void SphereNode::SetParentMatrix(const DirectX::SimpleMath::Matrix * parent)
{
	object_.SetParentWorld(parent);
}

CapsuleNode::CapsuleNode()
{
	localLenght_ = 1.0f;
	localRadius_ = 1.0f;
}

void CapsuleNode::Initialize()
{
	object_.LoadModelFromFile(L"Resources\\cModels\\HitCapsule.cmo");
}

void CapsuleNode::Update()
{
	object_.SetTrans(trans_);
	Vector3 localScale;
	localScale.x = localRadius_;
	localScale.z = localRadius_;
	localScale.y = localLenght_;
	object_.SetScale(localScale);
	object_.Calc();

	Matrix world = object_.GetWorld();
	Vector3 center(0.0f, 0.0f, 0.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);
	Vector3 right(1.0f, 0.0f, 0.0f);

	center = Vector3::Transform(center, world);
	up = Vector3::Transform(up, world);
	right = Vector3::Transform(right, world);

	segment_.start_ = center;
	segment_.end_ = up;
	radius_ = Vector3::Distance(center, right);
}

void CapsuleNode::Draw()
{
	if (CollisionNode::GetDebugVisible())
		object_.Draw();
}

void CapsuleNode::SetParentMatrix(const DirectX::SimpleMath::Matrix * parent)
{
	object_.SetParentWorld(parent);
}

void CapsuleNode::SetRotate(DirectX::SimpleMath::Vector3 & rotate)
{
	object_.SetRotate(rotate);
}


