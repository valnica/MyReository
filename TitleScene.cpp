//////////////////////////////////////////////
// Name : TitleScene
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "TitleScene.h"
#include "SceneManager.h"
#include "Sprite.h"
#include "Stage.h"
#include "Camera.h"
#include "GameManager.h"
#include "Object3D.h"

#include "Debug.h"

#include "Used\DirectXTK.h"

#include <SimpleMath.h>

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : TitleScene
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
TitleScene::TitleScene()
	:alpha_(0)
{
}

//////////////////////////////////////////////
// Name : ~TitleScene
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
TitleScene::~TitleScene()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : ����������
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void TitleScene::Initialize()
{
	//�摜�̓ǂݍ���
	sprite_[0].reset(new Sprite);
	sprite_[0]->Initialize(L"Resources\\Images\\TitleData.png", Vector2(320.0f, 120.0f), RECT{ 0,0,320,96 }, true);
	sprite_[1].reset(new Sprite);
	sprite_[1]->Initialize(L"Resources\\Images\\TitleData.png", Vector2(320.0f, 320.0f), RECT{ 0,96,192,160 }, true);
	
	//�X�e�[�W�̃��Z�b�g
	stage_.reset(new Stage);
	stage_->Initialize();

	//�J�����̏�����
	camera_.reset(new Camera((float)WINDOW_H,(float)WINDOW_W));
	camera_->SetRef(Vector3(0.0f, 0.0f, 0.0f));
	camera_->SetUp(Vector3(0.0f, 1.0f, 0.0f));

	//���C���J�����̐ݒ�
	Camera::MainCamera(camera_);
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : ����
//
// Return :  �������I��������̔���
//////////////////////////////////////////////
bool TitleScene::Update()
{
	//�摜�̓_��
	alpha_++;
	float alpha = sinf(alpha_ * 0.05f);
	sprite_[1]->SetAlpha(alpha);

	//�X�V
	stage_->Update();
	camera_->Update();

	Vector3 vec(0.0f, 0.0f, 40.0f);
	static float angle{};
	angle += 0.5f;
	if (angle > 360.0f)
		angle -= 360;
	Matrix rotY = Matrix::CreateRotationY(angle * 3.14f / 180.0f);
	vec = Vector3::Transform(vec, rotY);
	vec.y = 25.0f;

	//���_�̐ݒ�
	camera_->SetEye(vec);

	//�V�[���J��
	if (g_mouseTracker->leftButton == g_mouseTracker->PRESSED)
	{
		SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::PLAY);
	}

	return true;
}

//////////////////////////////////////////////
// Name : Render
//
// Over View : �`�揈��
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void TitleScene::Render()
{
	sprite_[0]->Draw();
	sprite_[1]->Draw();

	stage_->Render();

#ifdef DEBUG
	wchar_t flag[6];
	swprintf_s(flag, 6, L"Title");
	g_spriteFont->DrawString(g_spriteBatch.get(), flag, Vector2(300, 0));
#endif
}

//////////////////////////////////////////////
// Name : Finalize
//
// Over View : �I������
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void TitleScene::Finalize()
{
}