#pragma once

#include <SimpleMath.h>
#include <vector>

class Player;
class Enemy;

///////////////////////////////////
// Name      : CollisionManager
//
// Over view : 当たり判定の管理クラス
///////////////////////////////////
class CollisionManager
{
private:
	std::vector<Player*> player_;
	std::vector<Enemy*> enemy_;

	void Reset();
public:
	CollisionManager();
	~CollisionManager();

	void Initialize();
	void Update();

	void Entry(Player* player);
	void Entry(Enemy* enemy);

	//シングルトンでアクセス
	static CollisionManager* GetInstance();
};

class Box
{
public:
	DirectX::SimpleMath::Vector3 point[8];

	Box& operator=(Box& rhs)
	{
		for (int i = 0; i < 8; i++)
		{
			point[i] = rhs.point[i];
		}
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

class Collision
{
private:

public:
	bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::SimpleMath::Vector3* inter = nullptr);
	bool CheckCapsule2Capsule(const Capsule& capsule1, const Capsule& capsule2, DirectX::SimpleMath::Vector3* inter = nullptr);
	bool CheckSphere2Capsule(const Sphere& sphere, const Capsule& capsule, DirectX::SimpleMath::Vector3* inter = nullptr);
	float VectorLengthSquare(DirectX::SimpleMath::Vector3& v);
	float Distance3DSquared(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& p2);
	float GetSqDistancePoint2Segment(const DirectX::SimpleMath::Vector3& _point, const Segment& _segment);
	float GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment1);
	void ComputeTriangle(const DirectX::SimpleMath::Vector3& _p0, const DirectX::SimpleMath::Vector3& _p1, const DirectX::SimpleMath::Vector3& _p2, Triangle* _triangle);
	void ClosestPtPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const Triangle& _triangle, DirectX::SimpleMath::Vector3* _closest);
	bool CheckPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const Triangle& _triangle);
	bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter);
	bool CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter);
};