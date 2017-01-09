//////////////////////////////////////////////
// Name : Marker
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include "Object3D.h"
#include "CollisionManager.h"

//////////////////////////////////////////////
// Class Name : Marker
//
// Over View : 写真を撮られるオブジェクト
//////////////////////////////////////////////
class Marker
{
private:
	//オブジェクト
	Object3D marker_;
	
	//当たり判定用のオブジェクト
	Box box_;

public:
	Marker();
	~Marker();

	void Initialize();
	void Update();
	void Render();

	//当たり判定用のオブジェクトの取得
	Box& GetBox() { return box_; }

	//座標の取得
	DirectX::SimpleMath::Vector3 GetPos() { return marker_.GetTrans(); }
	
	//座標の設定
	void SetPosition(DirectX::SimpleMath::Vector3 pos);
	
	//回転角の設定
	void SetRotate(DirectX::SimpleMath::Vector3 rot);

	//大きさの設定
	void SetScale(DirectX::SimpleMath::Vector3 scale);
};

