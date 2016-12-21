#pragma once

#include <Model.h>
#include <Effects.h>
#include "Camera.h"
#include <map>
#include <SimpleMath.h>

class Object3D
{
private:
	static ID3D11Device* device_;
	static ID3D11DeviceContext* deviceContext_;
	static DirectX::CommonStates* state_;
	static std::weak_ptr<DirectX::EffectFactory> effect_;
	//static std::weak_ptr<Camera> camera_;
	static std::map<std::wstring, std::unique_ptr<DirectX::Model>> modelArray_;

public:
	static void SetDevice(ID3D11Device* device) { device_ = device; }
	static void SetContext(ID3D11DeviceContext* devicecontect) { deviceContext_ = devicecontect; }
	static void SetState(DirectX::CommonStates* state) { state_ = state; }
	static void SetEffect(std::shared_ptr<DirectX::EffectFactory> effect) { effect_ = effect; }
	//static void SetCamera(std::shared_ptr<Camera> camera) { camera_ = camera; }

private:
	const DirectX::Model* model_;
	DirectX::SimpleMath::Vector3 trans_;
	DirectX::SimpleMath::Vector3 rot_;
	DirectX::SimpleMath::Vector3 scale_;
	DirectX::SimpleMath::Matrix localWorld_;
	DirectX::SimpleMath::Matrix world_;
	const DirectX::SimpleMath::Matrix* parentMatrix_;
	bool useQuaternion_;
	DirectX::SimpleMath::Quaternion quaternion_;

public:
	Object3D();
	~Object3D();
	void LoadModelFromFile(const wchar_t* fileName = nullptr);
	void Calc();
	void Draw();
	void DesableLighting();

	void SetTrans(const DirectX::SimpleMath::Vector3& trans) { trans_ = trans; }
	void SetRotate(const DirectX::SimpleMath::Vector3& rot) { rot_ = rot; }
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { scale_ = scale; }
	void SetLocalWorld(const DirectX::SimpleMath::Matrix& world) { localWorld_ = world; }
	void SetParentWorld(const DirectX::SimpleMath::Matrix* parentWorld) { parentMatrix_ = parentWorld; }
	void SetQuaternion(const DirectX::SimpleMath::Quaternion quaternion) {quaternion_ = quaternion;}
	void SetQuaternionFlag(bool flag) { useQuaternion_ = flag; }

	const DirectX::SimpleMath::Vector3& GetTrans() {return trans_;}
	const DirectX::SimpleMath::Vector3& GetRotate() { return rot_; }
	const DirectX::SimpleMath::Vector3& GetScale() { return scale_; }
	DirectX::SimpleMath::Matrix& GetLocalWorld() { return localWorld_; }
	DirectX::SimpleMath::Matrix& GetWorld() { return world_; }
	const DirectX::SimpleMath::Matrix* GetParentWorld() { return parentMatrix_; }
	
	bool HaveParent() 
	{
		if (parentMatrix_)
			return true;
		else
			return false;
	}
};

