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

Camera::Camera(float window_h, float window_w)
	:fovY_(XMConvertToRadians(45.0f)), aspect_(window_w / window_h)
	, near_(0.1f), far_(1000.0f)
{
	view_ = Matrix::Identity;
	proj_ = Matrix::Identity;
	eye_ = Vector3(0.0f, 2.0f, 3.0f);
	ref_ = Vector3(0.0f, 1.0f, 0.0f);
	up_ = Vector3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	view_ = Matrix::CreateLookAt(eye_, ref_, up_);
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
{
}

CameraController::~CameraController()
{
}

void CameraController::Initialize(std::shared_ptr<Camera> camera)
{
	camera_ = camera;
	state_ = TPSCamera::GetInstance().get();
}

void CameraController::Update()
{
	State<Camera>* state = state_->Input(*camera_.lock());
	
	if (state)
	{
		state_ = state;
	}

	state_->Update(*camera_.lock());

	//カメラのアップデート
	camera_.lock()->Update();
}

void CameraController::SetCamera(std::shared_ptr<Camera> camera)
{
	camera_ = camera;
}