#pragma once
#include "Object3D.h"
#include "State.h"
#include "CollisionNode.h"
#include "Character.h"

namespace Math = DirectX::SimpleMath;

class Stage;

class Player:public Character
{
private:
	State<Player>* state_;

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

	//ポジションのセッターとゲッター
	void SetPosition(Math::Vector3 pos);
	Math::Vector3 GetPosition();
	
	//回転角のセッターとゲッター
	void SetRotate(Math::Vector3 rot);
	Math::Vector3 GetRotate();

	void SetHeadRotate(Math::Vector3 rot);
	Math::Vector3 GetHeadRotate();

	Math::Vector3 GetEyePosition();
	Math::Matrix GetEyeMatrix();

	SphereNode& GetCollisionBody() { return collisionBody_; }
	void Found();
	void Calc();

	void SetState(State<Player>* state)
	{
		if (state_)
			delete state_;

		state_ = state;
	}
};

