//////////////////////////////////////////////
// Name : Camera
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include "DirectXTK.h"
#include <SimpleMath.h>
#include "State.h"
#include <memory>

namespace Math = DirectX::SimpleMath;

class Character;
class Player;

//////////////////////////////////////////////
// Class Name : Camera
//
// Over View : �J����
//////////////////////////////////////////////
class Camera
{
private:
	//���C���J����
	static std::weak_ptr<Camera> main_;

	//�J�����̈ʒu
	Math::Vector3 eye_;

	//�����_
	Math::Vector3 ref_;

	//�J�����̏�̕���
	Math::Vector3 up_;

	//�r���[�s��
	Math::Matrix view_;

	//�v���W�F�N�V�����s��
	Math::Matrix proj_;

	//����p
	float fovY_;

	//�A�X�y�N�g��
	float aspect_;

	//�`�悷��ŒZ�̋���
	float near_;

	//�`�悷��Œ��̋���
	float far_;

	//�^�[�Q�b�g�ƂȂ�L����
	std::weak_ptr<Player> target_;

public:
	Camera(float Window_h,float Window_w);
	virtual ~Camera();

	void Update();

	//�����_�ɂ���L�����N�^�[�̐ݒ�
	void SetTarget(std::shared_ptr<Player> target) { target_ = target; }
	//�����_�ɂ��Ă���L�����N�^�[�̎擾
	std::weak_ptr<Player> GetTarget() { return target_; }
	//���C���J�����̐ݒ�
	static void MainCamera(std::shared_ptr<Camera> camera) { main_ = camera; }
	//���C���J�����̎擾
	static std::weak_ptr<Camera> MainCamera() { return main_; }

	//�J�����̐ݒ�
	void SetFovY(float fov);
	void SetAspect(float w, float h);
	void SetNear(float nearPos);
	void SetFar(float farPos);
	void SetEye(const Math::Vector3 pos) { eye_ = pos; }
	void SetRef(const Math::Vector3 pos) { ref_ = pos; }
	void SetUp(const Math::Vector3 pos) { up_ = pos; }
	
	//�J�����̏��̎擾
	const Math::Vector3& GetEye() const { return eye_; }
	const Math::Vector3& GetRef() const { return ref_; }
	const Math::Vector3& GetUp() const { return up_; }
	const Math::Matrix& GetView() const { return view_; }
	const Math::Matrix& GetProj() const { return proj_; }
};

class CameraState;

//////////////////////////////////////////////
// Class Name : CameraController
//
// Over View : �J�����𑀍삷�邽�߂̃N���X
//////////////////////////////////////////////
class CameraController
{
private:
	//�J������state
	std::weak_ptr<State<Camera>> state_;

	//�J����
	std::weak_ptr<Camera> camera_;

public:
	CameraController();
	~CameraController();

	void Initialize(std::shared_ptr<Camera> camera);
	void Update();

	//�J�����̐ݒ�
	void SetCamera(std::shared_ptr<Camera> camera);
};