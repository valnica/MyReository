#include "TPSCamera.h"
#include "FPSCamera.h"
#include "Utility.h"
#include "Player.h"
#include "GameManager.h"
#include "CollisionManager.h"

using namespace DirectX::SimpleMath;

TPSCamera::TPSCamera()
	:sensitivity_(0.01f)
{
}

TPSCamera::~TPSCamera()
{
}

State<Camera>* TPSCamera::Input(Camera & camera)
{
	if (g_mouseTracker->rightButton == g_mouseTracker->PRESSED)
	{
		//return new FPSCamera;
		return FPSCamera::GetInstance().get();
	}
	return nullptr;
}

void TPSCamera::Update(Camera & camera)
{
	std::weak_ptr<Player> player = camera.GetTarget();

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

	//�V�[�����X�ɂ��邽�߂̏���
	Vector3 eyeAmount = eye - camera.GetEye();
	eyeAmount *= 0.1f;

	//up�x�N�g�����񂷂��߂̌v�Z
	rot = rotX * rotY;
	up = Vector3::Transform(up, rot);

	//�J�����̐ݒ�
	//camera.SetEye(camera.GetEye() + eyeAmount);
	camera.SetEye(eye);
	camera.SetRef(ref);
	camera.SetUp(up);

	CollisionManager::GetInstance()->Entry(&camera);
}