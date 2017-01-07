//////////////////////////////////////////////
// Name : CollitionNode
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include "Object3D.h"
#include "CollisionManager.h"

//////////////////////////////////////////////
// Class Name : SphereNode
//
// Over View : 当たり判定用の球オブジェクト
//////////////////////////////////////////////
class SphereNode :public Sphere
{
protected:
	//オブジェクト
	Object3D object_;

	//半径
	float localRadius_;

	//座標
	DirectX::SimpleMath::Vector3 trans_;

public:
	SphereNode();
	
	void Initialize();
	void Update();
	void Draw();

	//親オブジェクトの設定
	void SetParentMatrix(const DirectX::SimpleMath::Matrix* parent);
	
	//半径の設定
	void SetLocalRadius(float radius) { localRadius_ = radius; }
	
	//座標の設定
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { trans_ = trans; }
	
	//座標の取得
	DirectX::SimpleMath::Vector3 GetTrans() { return object_.GetTrans(); }
};

//////////////////////////////////////////////
// Class Name : CapsuleNode
//
// Over View : 当たり判定用のカプセルオブジェクト
//////////////////////////////////////////////
class CapsuleNode :public Capsule
{
protected:
	//オブジェクト
	Object3D object_;

	//カプセルの長さ
	float localLenght_;

	//半径
	float localRadius_;

	//座標
	DirectX::SimpleMath::Vector3 trans_;

public:
	CapsuleNode();

	void Initialize();
	void Update();
	void Draw();

	//親オブジェクトの設定
	void SetParentMatrix(const DirectX::SimpleMath::Matrix* parent);
	
	//回転角の設定
	void SetRotate(DirectX::SimpleMath::Vector3& rotate);
	
	//半径の設定
	void SetLocalRadius(float radius) { localRadius_ = radius; }
	
	//長さの設定
	void SetLocalLenght(float lenght) { localLenght_ = lenght; }
	
	//座標の設定
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { trans_ = trans; }
};

