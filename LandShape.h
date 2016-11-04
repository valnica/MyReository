#pragma once

#include "LandShapeData.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <CommonStates.h>

#include "Camera.h"
#include "Object3D.h"
#include "CollisionManager.h"

class LandShapeCommonDef
{
public:
	ID3D11Device* device_;
	ID3D11DeviceContext* deviceContext_;
	Camera* camera_;
};

class LandShapeCommon
{
	friend class LandShape;
public:
	LandShapeCommon(LandShapeCommonDef* def);
	~LandShapeCommon();
protected:
	Camera* camera_;
	std::unique_ptr<DirectX::CommonStates> state_;
	std::unique_ptr<DirectX::EffectFactory> effectFactory_;
	std::unique_ptr<DirectX::BasicEffect> effect_;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionNormal>> primitiveBatch_;
	ID3D11InputLayout* inputLayout_;
	ID3D11DeviceContext* deviceContext_;
};

class LandShape
{
protected:
	static std::unique_ptr<LandShapeCommon> common_;
	static std::map<std::wstring, std::unique_ptr<LandShapeData>> dataArray_;

	Object3D object_;
	const LandShapeData* data_;
	DirectX::SimpleMath::Matrix world_;

public:
	static void InitializeCommon(LandShapeCommonDef* def);

	LandShape();
	void Initialize(const wchar_t* fileNameMDL, const wchar_t* fileNameCMO = nullptr);
	void Calc();
	void Draw();

	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { object_.SetTrans(trans); }
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate) { object_.SetRotate(rotate); }
	void SetScale(DirectX::SimpleMath::Vector3 scale) { object_.SetScale(DirectX::SimpleMath::Vector3(scale)); }
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { object_.SetLocalWorld(world); }

	const DirectX::SimpleMath::Vector3& GetTrans() { return object_.GetTrans(); }
	const DirectX::SimpleMath::Vector3& GetRotate() { return object_.GetRotate(); }
	const float GetScale() { return object_.GetScale().x; }
	const DirectX::SimpleMath::Matrix& GetLocalWorld() { return object_.GetWorld(); }

	bool IntersectSphere(const Sphere& sphere, DirectX::SimpleMath::Vector3* reject);
	bool LandShape::IntersectSegment(const Segment& segment, DirectX::SimpleMath::Vector3* inter);
};