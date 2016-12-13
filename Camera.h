#pragma once

#include "DirectXTK.h"
#include <SimpleMath.h>
//#include "Character.h"
#include "State.h"

class Player;

class Camera
{
private:
	//�J�����̈ʒu
	DirectX::SimpleMath::Vector3 eye_;

	//�����_
	DirectX::SimpleMath::Vector3 target_;

	//�J�����̏�̕���
	DirectX::SimpleMath::Vector3 up_;

	//�r���[�s��
	DirectX::SimpleMath::Matrix view_;

	//�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix proj_;

	//����p
	float fovY_;

	//�A�X�y�N�g��
	float aspect_;

	//�`�悷��ŒZ�̋���
	float near_;

	//�`�悷��Œ��̋���
	float far_;

public:
	Camera(float Window_h,float Window_w);

	virtual ~Camera();

	void Update();

	void SetFovY(float fov);
	void SetAspect(float w, float h);
	void SetNear(float nearPos);
	void SetFar(float farPos);
	void SetEye(const DirectX::SimpleMath::Vector3 pos) { eye_ = pos; }
	void SetTarget(const DirectX::SimpleMath::Vector3 pos) { target_ = pos; }
	void SetUp(const DirectX::SimpleMath::Vector3 pos) { up_ = pos; }
	const DirectX::SimpleMath::Vector3& GetEye() const { return eye_; }
	const DirectX::SimpleMath::Vector3& GetTarget() const { return target_; }
	const DirectX::SimpleMath::Vector3& GetUp() const { return up_; }
	const DirectX::SimpleMath::Matrix& GetView() const { return view_; }
	const DirectX::SimpleMath::Matrix& GetProj() const { return proj_; }
};

class CameraState;

class CameraController
{
private:
	State<Camera>* state_;
	Camera* camera_;

public:

	CameraController();
	~CameraController();

	void Initialize(Camera* camera);
	void Update();

	void SetCamera(Camera* camera);

	Camera* GetCamera() { return camera_; }
};