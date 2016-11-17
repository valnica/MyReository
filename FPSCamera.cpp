#include <SimpleMath.h>
#include "FPSCamera.h"
#include "Camera.h"
#include "Player.h"
#include "GameManager.h"
#include "DirectXTK.h"
#include "DebugCamera.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;


FPSCamera::FPSCamera()
{
}


FPSCamera::~FPSCamera()
{
}

State<Camera>* FPSCamera::Input(Camera & camera)
{
	if (g_keyTracker->IsKeyPressed(DirectX::Keyboard::O))
	{
		return new DebugCamera;
	}

	return nullptr;
}

void FPSCamera::Update(Camera & camera)
{
	Player* player = GameManager::GetInstance()->GetPlayer();

	//playerの行列をtrans rotate scaleに分解
	Vector3 pos;
	Quaternion qua;
	Vector3 scale;
	player->GetEyeMatrix().Decompose(scale, qua, pos);

	Vector3 angle = player->GetRotate() + player->GetHeadRotate();

	//カメラの設定に必要な変数の初期化
	Vector3 eye = pos;
	Vector3 ref = Vector3(0.0f, 0.0f, -20.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	//注視点を回すための計算
	Matrix rotX = Matrix::CreateRotationX(angle.x * 3.14f / 180);
	Matrix rotY = Matrix::CreateRotationY(angle.y* 3.14f / 180);
	Matrix rotZ = Matrix::CreateRotationZ(angle.z* 3.14f / 180);
	Matrix rot = rotX * rotY * rotZ;

	//注視点を計算
	ref = Vector3::TransformNormal(ref, rot);
	ref = eye + ref;

	//upベクトルを回すための計算
	rot = rotX * rotY;
	up = Vector3::TransformNormal(up, rot);

	//カメラの設定
	camera.SetEye(eye);
	camera.SetTarget(ref);
	camera.SetUp(up);
}
