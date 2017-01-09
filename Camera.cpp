//////////////////////////////////////////////
// Name : Camera
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "GameManager.h"
#include "Camera.h"
#include "Player.h"
#include "FPSCamera.h"
#include "TPSCamera.h"
#include "Character.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX;
using namespace DirectX::SimpleMath;

std::weak_ptr<Camera> Camera::main_;

//////////////////////////////////////////////
// Name : Camera
//
// Over View : �R���X�g���N�^
//
// Argument : ��ʂ̕��A����
//////////////////////////////////////////////
Camera::Camera(float window_h, float window_w)
	:fovY_(XMConvertToRadians(45.0f)), aspect_(window_w / window_h)
	, near_(0.1f), far_(1000.0f)
{
	//�`��ɕK�v�Ȑݒ�
	view_ = Matrix::Identity;
	proj_ = Matrix::Identity;
	eye_ = Vector3(0.0f, 2.0f, 3.0f);
	ref_ = Vector3(0.0f, 1.0f, 0.0f);
	up_ = Vector3(0.0f, 1.0f, 0.0f);
}

//////////////////////////////////////////////
// Name : ~Camera
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Camera::~Camera()
{
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : ����
//
// Return : ���� 
//////////////////////////////////////////////
void Camera::Update()
{
	//View�s��̍쐬
	view_ = Matrix::CreateLookAt(eye_, ref_, up_);
	
	//projection�s��̍쐬
	proj_ = Matrix::CreatePerspectiveFieldOfView(fovY_, aspect_, near_, far_);
}

//////////////////////////////////////////////
// Name : SetFovY
//
// Over View : ����p�̐ݒ�
//
// Argument : ����p
//
// Return : ���� 
//////////////////////////////////////////////
void Camera::SetFovY(float fov)
{
	fovY_ = fov;
}

//////////////////////////////////////////////
// Name : SetAspect
//
// Over View : �A�X�y�N�g��̐ݒ�
//
// Argument : ��ʂ̕��A����
//
// Return : ���� 
//////////////////////////////////////////////
void Camera::SetAspect(float w, float h)
{
	aspect_ = w / h;
}

//////////////////////////////////////////////
// Name : SetNear
//
// Over View : Near�N���b�v�̐ݒ�
//
// Argument : �`�悷��ŒZ����
//
// Return : ���� 
//////////////////////////////////////////////
void Camera::SetNear(float nearPos)
{
	near_ = nearPos;
}

//////////////////////////////////////////////
// Name : SetFar
//
// Over View : Far�N���b�v�̐ݒ�
//
// Argument : �`�悷��Œ�����
//
// Return : ���� 
//////////////////////////////////////////////
void Camera::SetFar(float farPos)
{
	far_ = farPos;
}

//////////////////////////////////////////////
// Name : CameraController
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
CameraController::CameraController()
{
}

//////////////////////////////////////////////
// Name : ~CameraController
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
CameraController::~CameraController()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ����������
//
// Argument : �J�����̃|�C���^
//
// Return : ���� 
//////////////////////////////////////////////
void CameraController::Initialize(std::shared_ptr<Camera> camera)
{
	camera_ = camera;
	state_ = TPSCamera::GetInstance().get();
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : ����
//
// Return : ���� 
//////////////////////////////////////////////
void CameraController::Update()
{
	//State�̐؂�ւ�����
	State<Camera>* state = state_->Input(*camera_.lock());
	if (state)
	{
		state_ = state;
	}

	//State�̍X�V����
	state_->Update(*camera_.lock());

	//�J�����̃A�b�v�f�[�g
	camera_.lock()->Update();
}

//////////////////////////////////////////////
// Name : SetCamera
//
// Over View : ��������J�����̐ݒ�
//
// Argument : �J�����̃|�C���^
//
// Return : ���� 
//////////////////////////////////////////////
void CameraController::SetCamera(std::shared_ptr<Camera> camera)
{
	camera_ = camera;
}