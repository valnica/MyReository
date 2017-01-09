//////////////////////////////////////////////
// Name : TPSCamera
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "TPSCamera.h"
#include "FPSCamera.h"
#include "Utility.h"
#include "Player.h"
#include "GameManager.h"
#include "CollisionManager.h"

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : TPSCamera
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
TPSCamera::TPSCamera()
	:sensitivity_(0.01f)
{
}

//////////////////////////////////////////////
// Name : ~TPSCamera
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
TPSCamera::~TPSCamera()
{
}

//////////////////////////////////////////////
// Name : Input
//
// Over View : state切り替え
//
// Argument : カメラの参照
//
// Return : state
//////////////////////////////////////////////
State<Camera>* TPSCamera::Input(Camera & camera)
{
	if (g_mouseTracker->rightButton == g_mouseTracker->PRESSED)
	{
		return FPSCamera::GetInstance().get();
	}
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
void TPSCamera::Update(Camera & camera)
{
	std::weak_ptr<Player> player = camera.GetTarget();

	//カメラの設定に必要な変数の初期化
	Vector3 eye = Vector3(0.0f, 0.0f, distance_);
	Vector3 ref = player.lock()->GetEyePosition();
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	rotate_.x -= g_mouse.x * sensitivity_;
	rotate_.y -= g_mouse.y * sensitivity_;
	Clamp(-90.0f * 3.14f / 180.0f, 90.0f* 3.14f / 180.0f, rotate_.y);

	//視点を回すための計算
	Matrix rotX = Matrix::CreateRotationX(rotate_.y);
	Matrix rotY = Matrix::CreateRotationY(rotate_.x);
	Matrix rotZ = Matrix::CreateRotationZ(rotate_.z);
	Matrix rot = rotX * rotY * rotZ;

	//視点を計算
	eye = Vector3::Transform(eye, rot);
	eye += ref;

	//シームレスにするための処理
	Vector3 eyeAmount = eye - camera.GetEye();
	eyeAmount *= 0.1f;

	//upベクトルを回すための計算
	rot = rotX * rotY;
	up = Vector3::Transform(up, rot);

	//カメラの設定
	//camera.SetEye(camera.GetEye() + eyeAmount);
	camera.SetEye(eye);
	camera.SetRef(ref);
	camera.SetUp(up);

	//当たり判定に登録
	CollisionManager::GetInstance()->Entry(&camera);
}