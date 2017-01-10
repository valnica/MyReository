//////////////////////////////////////////////
// Class Name : LandShape
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "LandShapeData.h"
#include "Camera.h"
#include "Object3D.h"
#include "CollisionManager.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <CommonStates.h>


//////////////////////////////////////////////
// Class Name : LandShapeCommonDef
//
// Over View : 地形のデフォルト設定用クラス
//////////////////////////////////////////////
class LandShapeCommonDef
{
public:
	//地形に必要な変数
	ID3D11Device* device_;
	ID3D11DeviceContext* deviceContext_;
};

//////////////////////////////////////////////
// Class Name : LandShapeCommon
//
// Over View : 地形の共通設定クラス
//////////////////////////////////////////////
class LandShapeCommon
{
	friend class LandShape;
public:
	LandShapeCommon(std::shared_ptr<LandShapeCommonDef> def);
	~LandShapeCommon();
protected:
	//地形に必要な変数
	std::unique_ptr<DirectX::CommonStates> state_;
	std::unique_ptr<DirectX::EffectFactory> effectFactory_;
	std::unique_ptr<DirectX::BasicEffect> effect_;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> primitiveBatch_;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout_;
	ID3D11DeviceContext* deviceContext_;
};

//////////////////////////////////////////////
// Class Name : LandShape
//
// Over View : 地形
//////////////////////////////////////////////
class LandShape
{
protected:
	//地形の設定
	static std::unique_ptr<LandShapeCommon> common_;
	
	//地形のプール
	static std::map<std::wstring, std::unique_ptr<LandShapeData>> dataArray_;

	//地形に必要な変数
	Object3D object_;
	const LandShapeData* data_;
	DirectX::SimpleMath::Matrix world_;
	Box box_;

public:
	static void InitializeCommon(std::shared_ptr<LandShapeCommonDef>);

	LandShape();
	void Initialize(const wchar_t* fileNameMDL, const wchar_t* fileNameCMO = nullptr);
	void Update();
	void Calc();
	void Draw();

	//座標の設定
	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { object_.SetTrans(trans); }
	
	//回転角の設定
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate) { object_.SetRotate(rotate); }
	
	//大きさの設定
	void SetScale(DirectX::SimpleMath::Vector3 scale) { object_.SetScale(DirectX::SimpleMath::Vector3(scale)); }
	
	//ワールドの設定
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { object_.SetLocalWorld(world); }

	//当たり判定用のボックスの設定
	void SetBox(Box box) 
	{
		box_ = box; 
		box_.SetScale(object_.GetScale());
		box_.Translation(object_.GetTrans() + DirectX::SimpleMath::Vector3(0.0f, object_.GetScale().y / 2.0f, 0.0f));
	}
	//当たり判定用のボックスの取得
	Box GetBox() { return box_; }

	//座標の取得
	const DirectX::SimpleMath::Vector3& GetTrans() { return object_.GetTrans(); }
	
	//回転角の取得
	const DirectX::SimpleMath::Vector3& GetRotate() { return object_.GetRotate(); }
	
	//大きさの設定
	const float GetScale() { return object_.GetScale().x; }
	
	//ワールドの取得
	const DirectX::SimpleMath::Matrix& GetLocalWorld() { return object_.GetWorld(); }

	//球との当たり判定
	bool IntersectSphere(const Sphere& sphere, DirectX::SimpleMath::Vector3* reject);
	
	//線分との当たり判定
	bool IntersectSegment(const Segment& segment, DirectX::SimpleMath::Vector3* inter, float angleofFloor = 30);
};