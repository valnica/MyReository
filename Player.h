#pragma once
#include "Object3D.h"
#include "State.h"
#include "CollisionNode.h"

class Stage;

class Player
{
private:
	State<Player>* state_;
	Stage* stage_;
	
	enum PARTS
	{
		EMPTY,
		BODY,
		HEAD,
		EYE,

		NUM_PARTS
	};

	bool flag_;
	SphereNode collisionBody_;

	Object3D parts_[NUM_PARTS];
public:
	Player();
	~Player();

	void Initialize();
	void Update();
	void Render();

	void SetStage(Stage* stage);
	Stage* GetStage() { return stage_; }

	//ポジションのセッターとゲッター
	void SetPosition(DirectX::SimpleMath::Vector3 pos);
	DirectX::SimpleMath::Vector3 GetPosition();
	
	//回転角のセッターとゲッター
	void SetRotate(DirectX::SimpleMath::Vector3 rot);
	DirectX::SimpleMath::Vector3 GetRotate();

	void SetHeadRotate(DirectX::SimpleMath::Vector3 rot);
	DirectX::SimpleMath::Vector3 GetHeadRotate();

	DirectX::SimpleMath::Vector3 GetEyePosition();
	DirectX::SimpleMath::Matrix GetEyeMatrix();

	SphereNode& GetCollisionBody() { return collisionBody_; }
	void Found();
	void Calc();
};

