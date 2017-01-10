//////////////////////////////////////////////
// Name : Collition
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "CollisionManager.h"

/////////////////////////////////////////
// Class Name : Point3D
//
// Over View  : 空間分割の戻り値用のクラス
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
// Over View  : 空間分割用のクラス
/////////////////////////////////////////
class Grid
{
private:

public:
	//分割の大きさ
	const float gridX_ = 10.0f;
	const float gridY_ = 10.0f;
	const float gridZ_ = 10.0f;

	//////////////////////////////////////////////
	// Name : Calc3DPoint
	//
	// Over View : 空間分割時の分割ポイントの計算
	//
	// Argument : 座標
	//
	// Return :  空間分割時のポイント
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
// Over View  : 当たり判定用のクラス
/////////////////////////////////////////
class Collision
{
private:

public:
	//球と球の当たり判定
	bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, DirectX::SimpleMath::Vector3* inter = nullptr);
	
	//カプセルとカプセル
	bool CheckCapsule2Capsule(const Capsule& capsule1, const Capsule& capsule2, DirectX::SimpleMath::Vector3* inter = nullptr);
	
	//球とカプセル
	bool CheckSphere2Capsule(const Sphere& sphere, const Capsule& capsule, DirectX::SimpleMath::Vector3* inter = nullptr);
	
	//長さの２乗を求める
	float VectorLengthSquare(DirectX::SimpleMath::Vector3& v);
	
	//2つの座標から距離の２乗を求める
	float Distance3DSquared(const DirectX::SimpleMath::Vector3& p1, const DirectX::SimpleMath::Vector3& p2);
	
	//点と線分の当たり判定
	float GetSqDistancePoint2Segment(const DirectX::SimpleMath::Vector3& _point, const Segment& _segment);
	
	//線分と線分の一番近いポジションを計算
	float GetSqDistanceSegment2Segment(const Segment& _segment0, const Segment& _segment1);
	
	//３点から3角形を計算
	void ComputeTriangle(const DirectX::SimpleMath::Vector3& _p0, const DirectX::SimpleMath::Vector3& _p1, const DirectX::SimpleMath::Vector3& _p2, Triangle* _triangle);
	
	//点と三角形の最近接点を計算
	void ClosestPtPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const Triangle& _triangle, DirectX::SimpleMath::Vector3* _closest);
	
	//点と三角形の当たり判定
	bool CheckPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const Triangle& _triangle);
	
	//球と三角形の当たり判定
	bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter);
	
	//線分と三角形の当たり判定
	bool CheckSegment2Triangle(const Segment& _segment, const Triangle& _triangle, DirectX::SimpleMath::Vector3 *_inter);
	
	//線分と地形の当たり判定
	LandShape* RayCast(DirectX::SimpleMath::Vector3 origine, DirectX::SimpleMath::Vector3 ref);
	
	//視界内にいるかどうかの判定
	bool InFrontView(const ViewInfo& viewInfo);
	
	//写真を撮れるオブジェクトとの判定
	bool MarkerInView();

	//ボックスと点の当たり判定
	bool Box2Point(BoundingBox box, DirectX::SimpleMath::Vector3 point);
	
	//ボックスとボックスの当たり判定
	bool Box2Box(BoundingBox box1, BoundingBox box2);
	
	//空間分割での周囲のマスにいるか判定
	bool NearArea(Point3D point1, Point3D point2);
};