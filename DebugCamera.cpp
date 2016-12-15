#include "DebugCamera.h"
#include "Camera.h"
#include "DirectXTK.h"
#include "FPSCamera.h"
#include "Utility.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

DebugCamera::DebugCamera()
	:distance_(10.0f),rotate_(Vector3::Zero)
{
}

DebugCamera::~DebugCamera()
{
}

State<Camera>* DebugCamera::Input(Camera & camera)
{
	if (g_keyTracker->IsKeyPressed(DirectX::Keyboard::O))
	{
		//return new FPSCamera;
		return FPSCamera::GetInstance().get();
	}

	return nullptr;
}

void DebugCamera::Update(Camera & camera)
{
	//カメラの設定に必要な変数の初期化
	Vector3 eye = Vector3(0.0f, 0.0f, distance_);
	Vector3 ref = Vector3::Zero;
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	//距離と回転角の計算
	if (g_mouse.leftButton)
	{
		distance_ += g_mouse.y * 0.05f;
		if (distance_ < 1.0f)
			distance_ = 1.0f;
	}
	else
	{
		rotate_.x += g_mouse.x * 0.05f;
		rotate_.y += g_mouse.y * 0.05f;
		Clamp(-90.0f * 3.14f / 180.0f, 90.0f* 3.14f / 180.0f, rotate_.y);
	}

	//視点を回すための計算
	Matrix rotX = Matrix::CreateRotationX(rotate_.y);
	Matrix rotY = Matrix::CreateRotationY(rotate_.x);
	Matrix rotZ = Matrix::CreateRotationZ(rotate_.z);
	Matrix rot = rotX * rotY * rotZ;

	//視点を計算
	eye = Vector3::Transform(eye, rot);

	//upベクトルを回すための計算
	rot = rotX * rotY;
	up = Vector3::Transform(up, rot);

	//カメラの設定
	camera.SetEye(eye);
	camera.SetRef(ref);
	camera.SetUp(up);
}
