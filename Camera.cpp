#include "GameManager.h"
#include "Camera.h"
#include "Player.h"
#include "FPSCamera.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX;
using namespace DirectX::SimpleMath;

Camera::Camera(float window_h, float window_w)
	:fovY_(XMConvertToRadians(45.0f)), aspect_(window_w / window_h)
	, near_(0.1f), far_(1000.0f)
{
	view_ = Matrix::Identity;
	proj_ = Matrix::Identity;
	eye_ = Vector3(0.0f, 2.0f, 3.0f);
	target_ = Vector3(0.0f, 1.0f, 0.0f);
	up_ = Vector3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	view_ = Matrix::CreateLookAt(eye_, target_, up_);
	proj_ = Matrix::CreatePerspectiveFieldOfView(fovY_, aspect_, near_, far_);
}

void Camera::SetFovY(float fov)
{
	fovY_ = fov;
}

void Camera::SetAspect(float w, float h)
{
	aspect_ = w / h;
}

void Camera::SetNear(float nearPos)
{
	near_ = nearPos;
}

void Camera::SetFar(float farPos)
{
	far_ = farPos;
}

CameraController::CameraController()
	:camera_(nullptr)
{
	state_ = new FPSCamera;
}

CameraController::~CameraController()
{
	if (state_)
		delete state_;
}

void CameraController::Initialize(Camera* camera)
{
	camera_ = camera;
}

void CameraController::Update()
{
	State<Camera>* state = state_->Input(*camera_);
	
	if (state)
	{
		delete state_;
		state_ = state;
	}

	state_->Update(*camera_);

	//カメラのアップデート
	camera_->Update();
}

void CameraController::SetCamera(Camera * camera)
{
	camera_ = camera;
}
