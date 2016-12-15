#include <SimpleMath.h>
#include "FPSCamera.h"
#include "Camera.h"
#include "Player.h"
#include "GameManager.h"
#include "DirectXTK.h"
#include "DebugCamera.h"
#include "TPSCamera.h"

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
	if (g_mouseTracker->rightButton == g_mouseTracker->RELEASED)
	{
		//return new TPSCamera;
		return TPSCamera::GetInstance().get();
	}

	if (g_keyTracker->IsKeyPressed(DirectX::Keyboard::O))
	{
		return new DebugCamera;
	}

	return nullptr;
}

void FPSCamera::Update(Camera & camera)
{
	std::weak_ptr<Player> player = camera.GetTarget();

	//player�̍s���trans rotate scale�ɕ���
	Vector3 pos;
	Quaternion qua;
	Vector3 scale;
	player.lock()->GetEyeMatrix().Decompose(scale, qua, pos);

	Vector3 angle = player.lock()->GetRotate() + player.lock()->GetHeadRotate();

	//�J�����̐ݒ�ɕK�v�ȕϐ��̏�����
	Vector3 eye = pos;
	Vector3 ref = Vector3(0.0f, 0.0f, -20.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	//�����_���񂷂��߂̌v�Z
	Matrix rotX = Matrix::CreateRotationX(angle.x * 3.14f / 180);
	Matrix rotY = Matrix::CreateRotationY(angle.y* 3.14f / 180);
	Matrix rotZ = Matrix::CreateRotationZ(angle.z* 3.14f / 180);
	Matrix rot = rotX * rotY * rotZ;

	//�����_���v�Z
	ref = Vector3::TransformNormal(ref, rot);
	ref = eye + ref;

	//up�x�N�g�����񂷂��߂̌v�Z
	rot = rotX * rotY;
	up = Vector3::TransformNormal(up, rot);

	//�J�����̐ݒ�
	camera.SetEye(eye);
	camera.SetRef(ref);
	camera.SetUp(up);
}
