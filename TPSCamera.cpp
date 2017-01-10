//////////////////////////////////////////////
// Name : TPSCamera
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "TPSCamera.h"
#include "FPSCamera.h"
#include "Utility.h"
#include "Player.h"
#include "GameManager.h"
#include "CollisionManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : TPSCamera
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
TPSCamera::TPSCamera()
	:sensitivity_(0.01f)
{
}

//////////////////////////////////////////////
// Name : ~TPSCamera
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
TPSCamera::~TPSCamera()
{
}

//////////////////////////////////////////////
// Name : Input
//
// Over View : state�؂�ւ�
//
// Argument : �J�����̎Q��
//
// Return : state
//////////////////////////////////////////////
std::shared_ptr<State<Camera>> TPSCamera::Input(Camera & camera)
{
	if (g_mouseTracker->rightButton == g_mouseTracker->PRESSED)
	{
		return FPSCamera::GetInstance();
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
void TPSCamera::Update(Camera & camera)
{
	auto player = camera.GetTarget();

	//�J�����̐ݒ�ɕK�v�ȕϐ��̏�����
	Vector3 eye = Vector3(0.0f, 0.0f, distance_);
	Vector3 ref = player.lock()->GetEyePosition();
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);

	rotate_.x -= g_mouse.x * sensitivity_;
	rotate_.y -= g_mouse.y * sensitivity_;
	Clamp(-90.0f * 3.14f / 180.0f, 90.0f* 3.14f / 180.0f, rotate_.y);

	//���_���񂷂��߂̌v�Z
	Matrix rotX = Matrix::CreateRotationX(rotate_.y);
	Matrix rotY = Matrix::CreateRotationY(rotate_.x);
	Matrix rotZ = Matrix::CreateRotationZ(rotate_.z);
	Matrix rot = rotX * rotY * rotZ;

	//���_���v�Z
	eye = Vector3::Transform(eye, rot);
	eye += ref;

	//up�x�N�g�����񂷂��߂̌v�Z
	rot = rotX * rotY;
	up = Vector3::Transform(up, rot);

	//�J�����̐ݒ�
	camera.SetEye(eye);
	camera.SetRef(ref);
	camera.SetUp(up);

	//�����蔻��ɓo�^
	CollisionManager::GetInstance()->Entry(&camera);
}