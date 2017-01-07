//////////////////////////////////////////////
// Name : Player
//
// Author : �R�c ����
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once
#include "Object3D.h"
#include "State.h"
#include "CollisionNode.h"
#include "Character.h"

namespace Math = DirectX::SimpleMath;

class Stage;

//////////////////////////////////////////////
// Class Name : Player
//
// Over View : �v���C���[
//////////////////////////////////////////////
class Player:public Character
{
private:
	//State
	State<Player>* state_;

	//���f���p�[�c�̒�`
	enum PARTS
	{
		EMPTY,
		BODY,
		HEAD,
		EYE,

		NUM_PARTS
	};

	bool flag_;

	//�����蔻��I�u�W�F�N�g
	SphereNode collisionBody_;

	//���f��
	Object3D parts_[NUM_PARTS];
public:
	Player();
	~Player();

	void Initialize();
	void Initialize(State<Player>* state);
	void Update();
	void Render();

	//�|�W�V�����̃Z�b�^�[�ƃQ�b�^�[
	void SetPosition(Math::Vector3 pos);
	Math::Vector3 GetPosition();
	
	//��]�p�̃Z�b�^�[�ƃQ�b�^�[
	void SetRotate(Math::Vector3 rot);
	Math::Vector3 GetRotate();

	//���̉�]�p�̃Z�b�^�[�ƃQ�b�^�[
	void SetHeadRotate(Math::Vector3 rot);
	Math::Vector3 GetHeadRotate();

	//�ڂ̃Q�b�^�[�ƃZ�b�^�[
	Math::Vector3 GetEyePosition();
	Math::Matrix GetEyeMatrix();

	//�����蔻��I�u�W�F�N�g�̎擾
	SphereNode& GetCollisionBody() { return collisionBody_; }
	
	//���������ʒm
	void Found();


	void Calc();
};

