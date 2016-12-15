#pragma once
#include "CollisionManager.h"

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

class Grid
{
private:

public:
	const float gridX_ = 10.0f;
	const float gridY_ = 10.0f;
	const float gridZ_ = 10.0f;

	Point3D Calc3DPoint(DirectX::SimpleMath::Vector3 pos)
	{
		int x = (int)(pos.x / gridX_);
		int y = (int)(pos.y / gridY_);
		int z = (int)(pos.z / gridZ_);

		return Point3D(x, y, z);
	}
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
	LandShape* RayCast(DirectX::SimpleMath::Vector3 origine, DirectX::SimpleMath::Vector3 ref);
	bool InFrontView(const ViewInfo& viewInfo);
	bool MarkerInView();
	bool Box2Point(BoundingBox box, DirectX::SimpleMath::Vector3 point);
	bool Box2Box(BoundingBox box1, BoundingBox box2);
	bool NearArea(Point3D point1, Point3D point2);
};