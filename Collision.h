//////////////////////////////////////////////
// Name : Collition
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "CollisionManager.h"

/////////////////////////////////////////
// Class Name : Point3D
//
// Over View  : ��ԕ����̖߂�l�p�̃N���X
/////////////////////////////////////////
class Point3D
{
private:

public:
	Point3D(int x, int y, int z)
		:x_(x), y_(y), z_(z)
	{
	}

	int x_;
	int y_;
	int z_;
};

/////////////////////////////////////////
// Class Name : Grid
//
// Over View  : ��ԕ����p�̃N���X
/////////////////////////////////////////
class Grid
{
private:

public:
	//�����̑傫��
	const float gridX_ = 10.0f;
	const float gridY_ = 10.0f;
	const float gridZ_ = 10.0f;

	//////////////////////////////////////////////
	// Name : Calc3DPoint
	//
	// Over View : ��ԕ������̕����|�C���g�̌v�Z
	//
	// Argument : ���W
	//
	// Return :  ��ԕ������̃|�C���g
	//////////////////////////////////////////////
	Point3D Calc3DPoint(DirectX::SimpleMath::Vector3 pos)
	{
		int x = (int)(pos.x / gridX_);
		int y = (int)(pos.y / gridY_);
		int z = (int)(pos.z / gridZ_);

		return Point3D(x, y, z);
	}
};

/////////////////////////////////////////
// Class Name : Collision
//
// Over View  : �����蔻��p�̃N���X
/////////////////////////////////////////
class Collision
{
private:

public:
	//���Ƌ��̓����蔻��
	bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::SimpleMath::Vector3* inter = nullptr);
	
	//�J�v�Z���ƃJ�v�Z��
	bool CheckCapsule2Capsule(const Capsule& capsule1, const Capsule& capsule2, DirectX::SimpleMath::Vector3* inter = nullptr);
	
	//���ƃJ�v�Z��
	bool CheckSphere2Capsule(const Sphere& sphere, const Capsule& capsule, DirectX::SimpleMath::Vector3* inter = nullptr);
	
	//�����̂Q������߂�
	float VectorLengthSquare(DirectX::SimpleMath::Vector3& v);
	
	//2�̍��W���狗���̂Q������߂�
	float Distance3DSquared(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& p2);
	
	//�_�Ɛ����̓����蔻��
	float GetSqDistancePoint2Segment(const DirectX::SimpleMath::Vector3& _point, const Segment& _segment);
	
	//�����Ɛ����̈�ԋ߂��|�W�V�������v�Z
	float GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment1);
	
	//�R�_����3�p�`���v�Z
	void ComputeTriangle(const DirectX::SimpleMath::Vector3& _p0, const DirectX::SimpleMath::Vector3& _p1, const DirectX::SimpleMath::Vector3& _p2, Triangle* _triangle);
	
	//�_�ƎO�p�`�̍ŋߐړ_���v�Z
	void ClosestPtPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const Triangle& _triangle, DirectX::SimpleMath::Vector3* _closest);
	
	//�_�ƎO�p�`�̓����蔻��
	bool CheckPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const Triangle& _triangle);
	
	//���ƎO�p�`�̓����蔻��
	bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter);
	
	//�����ƎO�p�`�̓����蔻��
	bool CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter);
	
	//�����ƒn�`�̓����蔻��
	LandShape* RayCast(DirectX::SimpleMath::Vector3 origine, DirectX::SimpleMath::Vector3 ref);
	
	//���E���ɂ��邩�ǂ����̔���
	bool InFrontView(const ViewInfo& viewInfo);
	
	//�ʐ^���B���I�u�W�F�N�g�Ƃ̔���
	bool MarkerInView();

	//�{�b�N�X�Ɠ_�̓����蔻��
	bool Box2Point(BoundingBox box, DirectX::SimpleMath::Vector3 point);
	
	//�{�b�N�X�ƃ{�b�N�X�̓����蔻��
	bool Box2Box(BoundingBox box1, BoundingBox box2);
	
	//��ԕ����ł̎��͂̃}�X�ɂ��邩����
	bool NearArea(Point3D point1, Point3D point2);
};