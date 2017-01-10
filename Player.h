//////////////////////////////////////////////
// Name : Player
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once
#include "Object3D.h"
#include "State.h"
#include "CollisionNode.h"
#include "Character.h"

#include "Debug.h"

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
	std::weak_ptr<State<Player>> state_;

	//���f���p�[�c�̒�`
	enum PARTS
	{
		EMPTY,
		BODY,
		HEAD,
		EYE,

		NUM_PARTS
	};

#ifdef DEBUG
	//�f�o�b�O�t���O
	bool debugFlag_;
#endif

	//�����蔻��I�u�W�F�N�g
	SphereNode collisionBody_;

	//���f��
	Object3D parts_[NUM_PARTS];
public:
	Player();
	~Player();

	void Initialize();
	void Initialize(std::shared_ptr<State<Player>> state);
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

	//���[���h�v�Z
	void Calc();
};

