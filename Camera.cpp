//////////////////////////////////////////////
// Name : Camera
//
// Author : 山田 聖弥
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
// Over View : コンストラクタ
//
// Argument : 画面の幅、高さ
//////////////////////////////////////////////
Camera::Camera(float window_h, float window_w)
	:fovY_(XMConvertToRadians(45.0f)), aspect_(window_w / window_h)
	, near_(0.1f), far_(1000.0f)
{
	//描画に必要な設定
	view_ = Matrix::Identity;
	proj_ = Matrix::Identity;
	eye_ = Vector3(0.0f, 2.0f, 3.0f);
	ref_ = Vector3(0.0f, 1.0f, 0.0f);
	up_ = Vector3(0.0f, 1.0f, 0.0f);
}

//////////////////////////////////////////////
// Name : ~Camera
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Camera::~Camera()
{
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return : 無し 
//////////////////////////////////////////////
void Camera::Update()
{
	//View行列の作成
	view_ = Matrix::CreateLookAt(eye_, ref_, up_);
	
	//projection行列の作成
	proj_ = Matrix::CreatePerspectiveFieldOfView(fovY_, aspect_, near_, far_);
}

//////////////////////////////////////////////
// Name : SetFovY
//
// Over View : 視野角の設定
//
// Argument : 視野角
//
// Return : 無し 
//////////////////////////////////////////////
void Camera::SetFovY(float fov)
{
	fovY_ = fov;
}

//////////////////////////////////////////////
// Name : SetAspect
//
// Over View : アスペクト比の設定
//
// Argument : 画面の幅、高さ
//
// Return : 無し 
//////////////////////////////////////////////
void Camera::SetAspect(float w, float h)
{
	aspect_ = w / h;
}

//////////////////////////////////////////////
// Name : SetNear
//
// Over View : Nearクリップの設定
//
// Argument : 描画する最短距離
//
// Return : 無し 
//////////////////////////////////////////////
void Camera::SetNear(float nearPos)
{
	near_ = nearPos;
}

//////////////////////////////////////////////
// Name : SetFar
//
// Over View : Farクリップの設定
//
// Argument : 描画する最長距離
//
// Return : 無し 
//////////////////////////////////////////////
void Camera::SetFar(float farPos)
{
	far_ = farPos;
}

//////////////////////////////////////////////
// Name : CameraController
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
CameraController::CameraController()
{
}

//////////////////////////////////////////////
// Name : ~CameraController
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
CameraController::~CameraController()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : カメラのポインタ
//
// Return : 無し 
//////////////////////////////////////////////
void CameraController::Initialize(std::shared_ptr<Camera> camera)
{
	camera_ = camera;
	state_ = TPSCamera::GetInstance().get();
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return : 無し 
//////////////////////////////////////////////
void CameraController::Update()
{
	//Stateの切り替え処理
	State<Camera>* state = state_->Input(*camera_.lock());
	if (state)
	{
		state_ = state;
	}

	//Stateの更新処理
	state_->Update(*camera_.lock());

	//カメラのアップデート
	camera_.lock()->Update();
}

//////////////////////////////////////////////
// Name : SetCamera
//
// Over View : 処理するカメラの設定
//
// Argument : カメラのポインタ
//
// Return : 無し 
//////////////////////////////////////////////
void CameraController::SetCamera(std::shared_ptr<Camera> camera)
{
	camera_ = camera;
}