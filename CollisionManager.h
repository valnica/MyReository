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
// Over view : 当たり判定の管理クラス
///////////////////////////////////
class CollisionManager:public Singleton<CollisionManager>
{
private:
	std::vector<Player*> player_;
	std::vector<Enemy*> enemy_;
	std::vector<LandShape*> landShape_;
	std::vector<Marker*> marker_;
	std::vector<Event*> event_;
	Camera* camera;

	friend Collision;
	friend class Singleton<CollisionManager>;

	void Reset();
public:
	CollisionManager();
	~CollisionManager();

	void Initialize();
	void Update();

	void Entry(Player* player);
	void Entry(Enemy* enemy);
	void Entry(LandShape* landShape);
	void Entry(Marker* marker);
	void Entry(Event* events);
	void Entry(Camera* mainCamera);
};

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


class Box
{
private:
	DirectX::SimpleMath::Vector3 point[8];

	friend Culling;
public:
	Box();

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

class Sphere
{
public:
	DirectX::SimpleMath::Vector3 center_;
	float radius_;
	Sphere()
	{
		radius_ = 1.0f;
	}
};

class Segment
{
public:
	DirectX::SimpleMath::Vector3 start_;
	DirectX::SimpleMath::Vector3 end_;
};

class Capsule
{
public:
	Segment segment_;
	float radius_;
	Capsule()
	{
		segment_.start_ = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
		segment_.end_ = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);
		radius_ = 1.0f;
	}
};

// 法線付き三角形（反時計回りが表面）
class Triangle
{
public:
	DirectX::SimpleMath::Vector3	P0;
	DirectX::SimpleMath::Vector3	P1;
	DirectX::SimpleMath::Vector3	P2;
	DirectX::SimpleMath::Vector3	Normal;	// 法線ベクトル
};

//視野内にいるかどうかの判定用のクラス
class ViewInfo
{
private:
public:
	DirectX::SimpleMath::Vector3 eye_;
	DirectX::SimpleMath::Vector3 ref_;
	float viewAngle_;
	float eyeAngle_;
	float viewDistance_;

	ViewInfo(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 ref, float viewAngle,float eyeAngle,float viewDistance)
		:eye_(eye),ref_(ref),viewAngle_(viewAngle),eyeAngle_(eyeAngle),viewDistance_(viewDistance)
	{
	}
};