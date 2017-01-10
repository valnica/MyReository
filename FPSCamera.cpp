//////////////////////////////////////////////
// Name : FPSCamera
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "FPSCamera.h"
#include "Camera.h"
#include "Player.h"
#include "GameManager.h"
#include "DebugCamera.h"
#include "TPSCamera.h"

#include "Used\DirectXTK.h"

#include "Debug.h"

#include <SimpleMath.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : FPSCamera
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
FPSCamera::FPSCamera()
{
}

//////////////////////////////////////////////
// Name : ~FPSCamera
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
FPSCamera::~FPSCamera()
{
}

//////////////////////////////////////////////
// Name : Input
//
// Over View : State切り替え
//
// Argument : Cameraの参照
//
// Return :  無し
//////////////////////////////////////////////
std::shared_ptr<State<Camera>> FPSCamera::Input(Camera & camera)
{
	//遷移条件と遷移先
	if (g_mouseTracker->rightButton == g_mouseTracker->RELEASED)
	{
		return TPSCamera::GetInstance();
	}

#ifdef DEBUG
	if (g_keyTracker->IsKeyPressed(DirectX::Keyboard::O))
	{
		return DebugCamera::GetInstance();
	}
#endif

	return nullptr;
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : カメラの参照
//
// Return :  無し
//////////////////////////////////////////////
void FPSCamera::Update(Camera & camera)
{
	auto player = camera.GetTarget();

	//playerの行列をtrans rotate scaleに分解
	Vector3 pos;
	Quaternion qua;
	Vector3 scale;
	player.lock()->GetEyeMatrix().Decompose(scale, qua, pos);

	Vector3 angle = player.lock()->GetRotate() + player.lock()->GetHeadRotate();

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
	camera.SetRef(ref);
	camera.SetUp(up);
}
