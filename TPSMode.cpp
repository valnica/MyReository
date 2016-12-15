#include "TPSMode.h"
#include "Player.h"
#include "PlayerMove.h"
#include <SimpleMath.h>
#include "Camera.h"
#include "GameManager.h"
#include <memory>

using namespace DirectX::SimpleMath;

TPSMode::TPSMode()
{
}

TPSMode::~TPSMode()
{
}

State<Player>* TPSMode::Input(Player & player)
{
	if (g_mouseTracker->rightButton == g_mouseTracker->PRESSED)
	{
		return new PlayerMove;
	}
	return nullptr;
}

void TPSMode::Update(Player & player)
{
	//移動ベクトル
	Vector3 vec = Vector3::Zero;

	if (g_key.W)
		vec += Vector3(0.0f, 0.0f, -1.0f);
	if (g_key.S)
		vec += Vector3(0.0f, 0.0f, 1.0f);
	if (g_key.A)
		vec += Vector3(-1.0f, 0.0f, 0.0f);
	if (g_key.D)
		vec += Vector3(1.0f, 0.0f, 0.0f);

	//入力がなければ以降の処理を行わない
	if (vec == Vector3::Zero) return;

	//カメラからplayerの向きを取得
	std::weak_ptr<Camera> camera = Camera::MainCamera();
	Vector3 eye = camera.lock()->GetEye();
	Vector3 dir = player.GetPosition() - eye;
	dir.y = 0.0f;

	//向きから角度を計算し、移動ベクトルを回転させる
	float rad = atan2f(-dir.x, -dir.z);
	Matrix rot = Matrix::CreateRotationY(rad);
	vec = Vector3::TransformNormal(vec, rot);
	vec.Normalize();

	//座標の更新と、向きの更新
	rad = atan2f(-vec.x, -vec.z);
	player.SetPosition(player.GetPosition() + vec * speed_);
	player.SetRotate(Vector3(0.0f, rad * 180 / 3.14f, 0.0f));
}