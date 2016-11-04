#pragma once
#include "Object3D.h"
#include "State.h"

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

	Object3D parts_[NUM_PARTS];
	void Calc();
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

	DirectX::SimpleMath::Vector3 GetEye();
	DirectX::SimpleMath::Matrix GetEyeMatrix();
};

