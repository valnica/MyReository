//////////////////////////////////////////////
// Name : Debug Camera
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "DebugCamera.h"
#include "Camera.h"
#include "DirectXTK.h"
#include "FPSCamera.h"
#include "Utility.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : DebugCamera
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
DebugCamera::DebugCamera()
	:distance_(10.0f),rotate_(Vector3::Zero)
{
}

//////////////////////////////////////////////
// Name : ~DebugCamera
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
DebugCamera::~DebugCamera()
{
}

//////////////////////////////////////////////
// Name : Input
//
// Over View : State�̐؂�ւ�
//
// Argument : �J�����̎Q��
//
// Return :  ����
//////////////////////////////////////////////
std::shared_ptr<State<Camera>> DebugCamera::Input(Camera & camera)
{
	//�J�ڏ����ƑJ�ڐ�
	if (g_keyTracker->IsKeyPressed(DirectX::Keyboard::O))
	{
		return FPSCamera::GetInstance();
	}
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
void DebugCamera::Update(Camera & camera)
{
	//�J�����̐ݒ�ɕK�v�ȕϐ��̏�����
	Vector3 eye = Vector3(0.0f, 0.0f, distance_);
	Vector3 ref = Vector3::Zero;
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	//�����Ɖ�]�p�̌v�Z
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

	//���_���񂷂��߂̌v�Z
	Matrix rotX = Matrix::CreateRotationX(rotate_.y);
	Matrix rotY = Matrix::CreateRotationY(rotate_.x);
	Matrix rotZ = Matrix::CreateRotationZ(rotate_.z);
	Matrix rot = rotX * rotY * rotZ;

	//���_���v�Z
	eye = Vector3::Transform(eye, rot);

	//up�x�N�g�����񂷂��߂̌v�Z
	rot = rotX * rotY;
	up = Vector3::Transform(up, rot);

	//�J�����̐ݒ�
	camera.SetEye(eye);
	camera.SetRef(ref);
	camera.SetUp(up);
}
