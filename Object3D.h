//////////////////////////////////////////////
// Class Name : Object3D
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////

#pragma once

#include <Model.h>
#include <Effects.h>
#include "Camera.h"
#include <map>
#include <SimpleMath.h>

//////////////////////////////////////////////
// Class Name : Object3D
//
// Over View : 3Dオブジェクト関係のクラス
//////////////////////////////////////////////
class Object3D
{
private:
	//3Dオブジェクトに必要な変数
	static ID3D11Device* device_;
	static ID3D11DeviceContext* deviceContext_;
	static DirectX::CommonStates* state_;
	static std::shared_ptr<DirectX::DGSLEffectFactory> effect_;
	static std::map<std::wstring, std::unique_ptr<DirectX::Model>> modelArray_;

public:
	//3Dオブジェクトに必要な変数の設定
	static void SetDevice(ID3D11Device* device) { device_ = device; }
	static void SetContext(ID3D11DeviceContext* devicecontect) { deviceContext_ = devicecontect; }
	static void SetState(DirectX::CommonStates* state) { state_ = state; }
	static void SetEffect(std::shared_ptr<DirectX::DGSLEffectFactory> effect) { effect_ = effect; }

private:
	//モデル
	const DirectX::Model* model_;
	
	//座標
	DirectX::SimpleMath::Vector3 trans_;

	//回転角
	DirectX::SimpleMath::Vector3 rot_;
	
	//大きさ
	DirectX::SimpleMath::Vector3 scale_;
	
	//ローカルワールド行列
	DirectX::SimpleMath::Matrix localWorld_;
	
	//ワールド行列
	DirectX::SimpleMath::Matrix world_;
	
	//親オブジェクトのワールド行列
	const DirectX::SimpleMath::Matrix* parentMatrix_;
	
	//クォータニオン計算フラグ
	bool useQuaternion_;

	//回転角
	DirectX::SimpleMath::Quaternion quaternion_;

public:
	Object3D();
	~Object3D();

	//モデルの読み込み
	void LoadModelFromFile(const wchar_t* fileName = nullptr);
	
	void Calc();
	void Draw();

	//ライティング設定
	void DesableLighting();

	//座標の設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { trans_ = trans; }
	
	//回転角の設定
	void SetRotate(const DirectX::SimpleMath::Vector3& rot) { rot_ = rot; }
	
	//大きさの設定
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { scale_ = scale; }
	
	//ローカルワールドの設定
	void SetLocalWorld(const DirectX::SimpleMath::Matrix& world) { localWorld_ = world; }
	
	//親オブジェクトの設定
	void SetParentWorld(const DirectX::SimpleMath::Matrix* parentWorld) { parentMatrix_ = parentWorld; }
	
	//回転角の設定
	void SetQuaternion(const DirectX::SimpleMath::Quaternion quaternion) {quaternion_ = quaternion;}
	
	//クォータニオンフラグの切り替え
	void SetQuaternionFlag(bool flag) { useQuaternion_ = flag; }

	//座標の取得
	const DirectX::SimpleMath::Vector3& GetTrans() {return trans_;}
	
	//回転角の取得
	const DirectX::SimpleMath::Vector3& GetRotate() { return rot_; }
	
	//大きさの取得
	const DirectX::SimpleMath::Vector3& GetScale() { return scale_; }
	
	//ローカルワールドの取得
	DirectX::SimpleMath::Matrix& GetLocalWorld() { return localWorld_; }
	
	//ワールドの取得
	DirectX::SimpleMath::Matrix& GetWorld() { return world_; }
	
	//親オブジェクトの取得
	const DirectX::SimpleMath::Matrix* GetParentWorld() { return parentMatrix_; }
	
	//////////////////////////////////////////////
	// Name : HaveParent
	//
	// Over View : 親オブジェクトがあるかどうか
	//
	// Argument : 無し
	//
	// Return : true or false 
	//////////////////////////////////////////////
	bool HaveParent() 
	{
		if (parentMatrix_)
			return true;
		else
			return false;
	}
};

