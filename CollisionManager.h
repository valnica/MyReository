//////////////////////////////////////////////
// Name : COllitionManager
//
// Author : 山田 聖弥
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
// Over view : 当たり判定の管理クラス
///////////////////////////////////
class CollisionManager:public Singleton<CollisionManager>
{
private:
	//当たり判定をするオブジェクトの登録用変数
	std::vector<Player*> player_;
	std::vector<Enemy*> enemy_;
	std::vector<LandShape*> landShape_;
	std::vector<Marker*> marker_;
	std::vector<Event*> event_;
	Camera* camera_;
	
	friend Collision;
	friend class Singleton<CollisionManager>;

	//登録情報のリセット
	void Reset();
public:
	CollisionManager();
	~CollisionManager();

	void Initialize();
	void Update();

	//登録用の関数
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
// Over View : ボックスの当たり判定用のクラス
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
// Over View : ボックス
//////////////////////////////////////////////
class Box
{
private:
	//ボックスの各頂点
	DirectX::SimpleMath::Vector3 point[8];

	friend Culling;
public:
	Box();

	//ボックスの設定
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
	// Over View : 当たり判定用のボックスの取得
	//
	// Argument : 無し
	//
	// Return : 当たり判定用のボックス
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
// Over View : 当たり判定用の球
//////////////////////////////////////////////
class Sphere
{
public:
	//中心点
	DirectX::SimpleMath::Vector3 center_;
	
	//半径
	float radius_;

	Sphere()
	{
		radius_ = 1.0f;
	}
};

//////////////////////////////////////////////
// Class Name : Segment
//
// Over View : 線分
//////////////////////////////////////////////
class Segment
{
public:
	//始点
	DirectX::SimpleMath::Vector3 start_;
	
	//終点
	DirectX::SimpleMath::Vector3 end_;
};

//////////////////////////////////////////////
// Class Name : Capsule
//
// Over View : 当たり判定用のカプセル
//////////////////////////////////////////////
class Capsule
{
public:
	//線分
	Segment segment_;
	
	//半径
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
// Over View : 当たり判定用の三角形
//////////////////////////////////////////////
class Triangle
{
public:
	//各頂点の座標
	DirectX::SimpleMath::Vector3	P0;
	DirectX::SimpleMath::Vector3	P1;
	DirectX::SimpleMath::Vector3	P2;
	//法線
	DirectX::SimpleMath::Vector3	Normal;	// 法線ベクトル
};

//////////////////////////////////////////////
// Class Name : ViewInfo
//
// Over View : 視野内にいるか判定の引数用のクラス
//////////////////////////////////////////////
class ViewInfo
{
private:
public:
	//視点
	DirectX::SimpleMath::Vector3 eye_;
	
	//注視点
	DirectX::SimpleMath::Vector3 ref_;
	
	//視野角
	float viewAngle_;
	
	//向いている方向
	float eyeAngle_;

	//視野距離
	float viewDistance_;

	ViewInfo(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 ref, float viewAngle,float eyeAngle,float viewDistance)
		:eye_(eye),ref_(ref),viewAngle_(viewAngle),eyeAngle_(eyeAngle),viewDistance_(viewDistance)
	{
	}
};