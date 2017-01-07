//////////////////////////////////////////////
// Name : COllitionManager
//
// Author : �R�c ����
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include <SimpleMath.h>
#include <vector>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include "Singleton.h"

class Marker;
class Player;
class Enemy;
class LandShape;
class Collision;
class Culling;
class Event;
class Camera;

///////////////////////////////////
// Name      : CollisionManager
//
// Over view : �����蔻��̊Ǘ��N���X
///////////////////////////////////
class CollisionManager:public Singleton<CollisionManager>
{
private:
	//�����蔻�������I�u�W�F�N�g�̓o�^�p�ϐ�
	std::vector<Player*> player_;
	std::vector<Enemy*> enemy_;
	std::vector<LandShape*> landShape_;
	std::vector<Marker*> marker_;
	std::vector<Event*> event_;
	Camera* camera_;
	
	friend Collision;
	friend class Singleton<CollisionManager>;

	//�o�^���̃��Z�b�g
	void Reset();
public:
	CollisionManager();
	~CollisionManager();

	void Initialize();
	void Update();

	//�o�^�p�̊֐�
	void Entry(Player* player);
	void Entry(Enemy* enemy);
	void Entry(LandShape* landShape);
	void Entry(Marker* marker);
	void Entry(Event* events);
	void Entry(Camera* camera);
};

//////////////////////////////////////////////
// Class Name : BoundingBox
//
// Over View : �{�b�N�X�̓����蔻��p�̃N���X
//////////////////////////////////////////////
class BoundingBox
{
private:
public:
	float maxX_;
	float minX_;
	float maxY_;
	float minY_;
	float maxZ_;
	float minZ_;
};

//////////////////////////////////////////////
// Class Name : Box
//
// Over View : �{�b�N�X
//////////////////////////////////////////////
class Box
{
private:
	//�{�b�N�X�̊e���_
	DirectX::SimpleMath::Vector3 point[8];

	friend Culling;
public:
	Box();

	//�{�b�N�X�̐ݒ�
	void Translation(DirectX::SimpleMath::Vector3 pos);
	void SetScale(DirectX::SimpleMath::Vector3 scale);

	void Initialize();
	void Draw();

	Box& operator=(Box& rhs)
	{
		for (int i = 0; i < 8; i++)
		{
			point[i] = rhs.point[i];
		}

		return *this;
	}

	//////////////////////////////////////////////
	// Name : GetBoundingBox
	//
	// Over View : �����蔻��p�̃{�b�N�X�̎擾
	//
	// Argument : ����
	//
	// Return : �����蔻��p�̃{�b�N�X
	//////////////////////////////////////////////
	BoundingBox GetBoundingBox()
	{
		BoundingBox box;
		box.maxX_ = point[2].x;
		box.minX_ = point[0].x;
		box.maxY_ = point[0].y;
		box.minY_ = point[4].y;
		box.maxZ_ = point[0].z;
		box.minZ_ = point[2].z;

		return box;
	}
};

//////////////////////////////////////////////
// Class Name : Sphere
//
// Over View : �����蔻��p�̋�
//////////////////////////////////////////////
class Sphere
{
public:
	//���S�_
	DirectX::SimpleMath::Vector3 center_;
	
	//���a
	float radius_;

	Sphere()
	{
		radius_ = 1.0f;
	}
};

//////////////////////////////////////////////
// Class Name : Segment
//
// Over View : ����
//////////////////////////////////////////////
class Segment
{
public:
	//�n�_
	DirectX::SimpleMath::Vector3 start_;
	
	//�I�_
	DirectX::SimpleMath::Vector3 end_;
};

//////////////////////////////////////////////
// Class Name : Capsule
//
// Over View : �����蔻��p�̃J�v�Z��
//////////////////////////////////////////////
class Capsule
{
public:
	//����
	Segment segment_;
	
	//���a
	float radius_;


	Capsule()
	{
		segment_.start_ = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		segment_.end_ = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
		radius_ = 1.0f;
	}
};

//////////////////////////////////////////////
// Class Name : Triangle
//
// Over View : �����蔻��p�̎O�p�`
//////////////////////////////////////////////
class Triangle
{
public:
	//�e���_�̍��W
	DirectX::SimpleMath::Vector3	P0;
	DirectX::SimpleMath::Vector3	P1;
	DirectX::SimpleMath::Vector3	P2;
	//�@��
	DirectX::SimpleMath::Vector3	Normal;	// �@���x�N�g��
};

//////////////////////////////////////////////
// Class Name : ViewInfo
//
// Over View : ������ɂ��邩����̈����p�̃N���X
//////////////////////////////////////////////
class ViewInfo
{
private:
public:
	//���_
	DirectX::SimpleMath::Vector3 eye_;
	
	//�����_
	DirectX::SimpleMath::Vector3 ref_;
	
	//����p
	float viewAngle_;
	
	//�����Ă������
	float eyeAngle_;

	//���싗��
	float viewDistance_;

	ViewInfo(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 ref, float viewAngle,float eyeAngle,float viewDistance)
		:eye_(eye),ref_(ref),viewAngle_(viewAngle),eyeAngle_(eyeAngle),viewDistance_(viewDistance)
	{
	}
};