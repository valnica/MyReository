//////////////////////////////////////////////
// Name : CollitionNode
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "CollisionNode.h"
#include "Debug.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX;
using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : ShereNode
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
SphereNode::SphereNode()
{
	//�����ݒ�
	localRadius_ = 1.0f;
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
void SphereNode::Initialize()
{
	//�����蔻��p�̃��f���̓ǂݍ���
	object_.LoadModelFromFile(L"Resources\\cModels\\HitSphere.cmo");
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
void SphereNode::Update()
{
	//���W�̐ݒ�
	object_.SetTrans(trans_);
	Vector3 localScale;

	//�傫���̐ݒ�
	localScale = Vector3(1, 1, 1);

	//�傫���̕ύX
	localScale.x = localRadius_;
	localScale.y = localRadius_;
	localScale.z = localRadius_;
	object_.SetScale(localScale);

	object_.Calc();

	//���̌v�Z
	Matrix world = object_.GetWorld();
	Vector3 center(0.0f, 0.0f, 0.0f);
	Vector3 right(1.0f, 0.0f, 0.0f);

	center = Vector3::Transform(center, world);
	right = Vector3::Transform(right, world);

	center_ = center;
	radius_ = Vector3::Distance(center, right);
}

//////////////////////////////////////////////
// Name : Draw
//
// Over View : ���̃f�o�b�O�\��
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void SphereNode::Draw()
{
#ifdef DEBUG
	if (Debug::GetFlag())
		object_.Draw();
#endif
}

//////////////////////////////////////////////
// Name : SetParentMatrix
//
// Over View : �e�I�u�W�F�N�g�̐ݒ�
//
// Argument : �e�I�u�W�F�N�g�̍s��
//
// Return :  ����
//////////////////////////////////////////////
void SphereNode::SetParentMatrix(const DirectX::SimpleMath::Matrix * parent)
{
	object_.SetParentWorld(parent);
}

//////////////////////////////////////////////
// Name : CapsuleNode
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
CapsuleNode::CapsuleNode()
{
	//�����ݒ�
	localLenght_ = 1.0f;
	localRadius_ = 1.0f;
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
void CapsuleNode::Initialize()
{
	//�����蔻��p�̃��f���̓ǂݍ���
	object_.LoadModelFromFile(L"Resources\\cModels\\HitCapsule.cmo");
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
void CapsuleNode::Update()
{
	//���W�̐ݒ�
	object_.SetTrans(trans_);
	
	//�傫���̐ݒ�
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
	
	//World�v�Z
	center = Vector3::Transform(center, world);
	up = Vector3::Transform(up, world);
	right = Vector3::Transform(right, world);

	//�傫���̍X�V
	segment_.start_ = center;
	segment_.end_ = up;
	radius_ = Vector3::Distance(center, right);
}

//////////////////////////////////////////////
// Name : Draw
//
// Over View : �J�v�Z���̃f�o�b�O�`��
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void CapsuleNode::Draw()
{
#ifdef DEBUG
	if (Debug::GetFlag())
		object_.Draw();
#endif
}

//////////////////////////////////////////////
// Name : SetParentMatrix
//
// Over View : �e�I�u�W�F�N�g�̐ݒ�
//
// Argument : �e�I�u�W�F�N�g�̍s��
//
// Return :  ����
//////////////////////////////////////////////
void CapsuleNode::SetParentMatrix(const DirectX::SimpleMath::Matrix * parent)
{
	object_.SetParentWorld(parent);
}

//////////////////////////////////////////////
// Name : SetRotate
//
// Over View : �J�v�Z������]������
//
// Argument : ��]�p
//
// Return :  ����
//////////////////////////////////////////////
void CapsuleNode::SetRotate(DirectX::SimpleMath::Vector3 & rotate)
{
	object_.SetRotate(rotate);
}