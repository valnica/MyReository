//////////////////////////////////////////////
// Name : FPSCamera
//
// Author : �R�c ����
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
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
FPSCamera::FPSCamera()
{
}

//////////////////////////////////////////////
// Name : ~FPSCamera
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
FPSCamera::~FPSCamera()
{
}

//////////////////////////////////////////////
// Name : Input
//
// Over View : State�؂�ւ�
//
// Argument : Camera�̎Q��
//
// Return :  ����
//////////////////////////////////////////////
std::shared_ptr<State<Camera>> FPSCamera::Input(Camera & camera)
{
	//�J�ڏ����ƑJ�ڐ�
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
// Over View : �X�V����
//
// Argument : �J�����̎Q��
//
// Return :  ����
//////////////////////////////////////////////
void FPSCamera::Update(Camera & camera)
{
	auto player = camera.GetTarget();

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
