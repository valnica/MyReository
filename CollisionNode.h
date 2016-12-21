#pragma once

#include "Object3D.h"
#include "CollisionManager.h"

class SphereNode :public Sphere
{
protected:
	Object3D object_;
	float localRadius_;
	DirectX::SimpleMath::Vector3 trans_;

public:
	SphereNode();
	
	void Initialize();
	void Update();
	void Draw();

	void SetParentMatrix(const DirectX::SimpleMath::Matrix* parent);
	void SetLocalRadius(float radius) { localRadius_ = radius; }
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { trans_ = trans; }
	DirectX::SimpleMath::Vector3 GetTrans() { return object_.GetTrans(); }
};

class CapsuleNode :public Capsule
{
protected:
	Object3D object_;
	float localLenght_;
	float localRadius_;
	DirectX::SimpleMath::Vector3 trans_;

public:
	CapsuleNode();

	void Initialize();
	void Update();
	void Draw();

	void SetParentMatrix(const DirectX::SimpleMath::Matrix* parent);
	void SetRotate(DirectX::SimpleMath::Vector3& rotate);
	void SetLocalRadius(float radius) { localRadius_ = radius; }
	void SetLocalLenght(float lenght) { localLenght_ = lenght; }
	void SetTrans(DirectX::SimpleMath::Vector3& trans) { trans_ = trans; }
};

