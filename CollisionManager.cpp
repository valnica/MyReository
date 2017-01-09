//////////////////////////////////////////////
// Name : COllitionManager
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "CollisionManager.h"
#include "DirectXTK.h"
#include "Debug.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "Culling.h"
#include "LandShape.h"
#include "Collision.h"
#include "Event.h"
#include "Stage.h"
#include "SceneManager.h"
#include "TPSCamera.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : Reset
//
// Over View : �o�^����Ă�I�u�W�F�N�g�̃��Z�b�g
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void CollisionManager::Reset()
{
	//�o�^����Ă�I�u�W�F�N�g�̃��Z�b�g
	player_.clear();
	enemy_.clear();
	landShape_.clear();
	marker_.clear();
	camera_ = nullptr;
}

//////////////////////////////////////////////
// Name : CollitionManager
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
CollisionManager::CollisionManager()
{
}

//////////////////////////////////////////////
// Name : ~CollitionManager
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
CollisionManager::~CollisionManager()
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
void CollisionManager::Initialize()
{
	player_.clear();
	enemy_.clear();
	landShape_.clear();
	marker_.clear();
	event_.clear();
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : �X�V����
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void CollisionManager::Update()
{
	Collision collision;

	////////////////////////�L�����ƒn�`//////////////////////////////////

	for (auto player = player_.begin(); player != player_.end(); player++)
	{
		for (auto landShape = landShape_.begin(); landShape != landShape_.end(); landShape++)
		{
			//��ԕ����p�̕ϐ�
			Grid grid;
			SphereNode sphere = (*player)->GetCollisionBody();
			Point3D point1 = grid.Calc3DPoint((*player)->GetPosition());
			Point3D point2 = grid.Calc3DPoint((*landShape)->GetTrans());

			//����������Ԃ��אڋ�Ԃł��邩�ǂ���
			if (!collision.NearArea(point1, point2))
			{
				continue;
			}

			//�v���C���[�ƒn�`�̓����蔻��
			Vector3 inter;
			Vector3 vec = (*player)->GetPosition() - sphere.center_;
			if ((*landShape)->IntersectSphere(sphere, &inter))
			{
				sphere.center_ += inter;
				(*player)->SetPosition(sphere.center_ + vec);
				(*player)->Calc();
			}
		}
	}

	////////////////////////�G���玩���ւ̎�������/////////////////////////
	for (auto player = player_.begin(); player != player_.end(); player++)
	{
		for (auto enemy = enemy_.begin(); enemy != enemy_.end(); enemy++)
		{
			//��������ǂ����̔��肷�邽�߂̕ϐ��\�z
			Vector3 eye = (*enemy)->GetPosition();
			Vector3 ref = (*player)->GetEyePosition();
			float eyeAngle = (*enemy)->GetRotate().y;
			float viewAngle = (*enemy)->GetViewAngle();
			float viewDistance = (*enemy)->GetViewDistance();
			ViewInfo viewInfo(eye, ref, viewAngle, eyeAngle, viewDistance);

			//��������ǂ���
			if (collision.InFrontView(viewInfo))
			{
				//raycast�p�̕ϐ��\�z
				Vector3 origine = (*enemy)->GetPosition() + Vector3(0.0f, 1.0f, 0.0f);
				Vector3 ref = (*player)->GetEyePosition();

				//Ray�����������I�u�W�F�N�g������
				LandShape* land = collision.RayCast(origine, ref);

				//raycast�ŃI�u�W�F�N�g�ɓ������Ă��Ȃ������猩�����Ă���
				if (!land)
				{
					SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::GAMEOVER);
				}
			}
		}
	}

	////////////////////////�����ƃC�x���g�Ƃ̓����蔻��/////////////////////////

	for (auto player = player_.begin(); player != player_.end(); player++)
	{
		for (auto events = event_.begin(); events != event_.end();)
		{
			//�����蔻��
			BoundingBox boundingBox = (*events)->GetBox().GetBoundingBox();
			Vector3 pos = (*player)->GetEyePosition();
			if (collision.Box2Point(boundingBox, pos))
			{
				if ((*events)->Run())
				{
					events = event_.erase(events);
					continue;
				}
			}
			events++;
		}
	}

	////////////////////////////�J�����ƃI�u�W�F�N�g//////////////////////////
	if (camera_)
	{
		Vector3 inter{};
		float distance = (float)10e10;
		for (auto it = landShape_.begin(); it != landShape_.end(); it++)
		{
			Segment segment;
			segment.start_ = Camera::MainCamera().lock()->GetRef();
			segment.end_ = Camera::MainCamera().lock()->GetEye();

			if ((*it)->IntersectSegment(segment, &inter, 90))
			{
				if (distance > inter.Length())
				{
					distance = inter.Length();
					Vector3 offset = segment.start_ - inter;
					offset.Normalize();
					Camera::MainCamera().lock()->SetEye(inter + offset);
					Camera::MainCamera().lock()->Update();
				}
			}
		}
	}


	Reset();
}

//////////////////////////////////////////////
// Name : Entry
//
// Over View : �����蔻��ɓo�^
//
// Argument : Player�̃|�C���^
//
// Return :  ����
//////////////////////////////////////////////
void CollisionManager::Entry(Player * player)
{
	player_.push_back(player);
}

//////////////////////////////////////////////
// Name : Entry
//
// Over View : �����蔻��ɓo�^
//
// Argument : Enemy�̃|�C���^
//
// Return :  ����
//////////////////////////////////////////////
void CollisionManager::Entry(Enemy * enemy)
{
	enemy_.push_back(enemy);
}

//////////////////////////////////////////////
// Name : Entry
//
// Over View : �����蔻��ɓo�^
//
// Argument : LandShape�̃|�C���^
//
// Return :  ����
//////////////////////////////////////////////
void CollisionManager::Entry(LandShape * landShape)
{
	landShape_.push_back(landShape);
}

//////////////////////////////////////////////
// Name : Entry
//
// Over View : �����蔻��ɓo�^
//
// Argument : Marker�̃|�C���^
//
// Return :  ����
//////////////////////////////////////////////
void CollisionManager::Entry(Marker * marker)
{
	marker_.push_back(marker);
}

//////////////////////////////////////////////
// Name : Entry
//
// Over View : �����蔻��ɓo�^
//
// Argument : Event�̃|�C���^
//
// Return :  ����
//////////////////////////////////////////////
void CollisionManager::Entry(Event * events)
{
	event_.push_back(events);
}

//////////////////////////////////////////////
// Name : Entry
//
// Over View : �����蔻��ɓo�^
//
// Argument : Camera�̃|�C���^
//
// Return :  ����
//////////////////////////////////////////////
void CollisionManager::Entry(Camera* camera)
{
	camera_ = camera;
}

//////////////////////////////////////////////
// Name : Box
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
Box::Box()
{
	point[0] = Vector3(-0.5f, 0.5f, 0.5f);
	point[1] = Vector3(-0.5f, 0.5f, -0.5f);
	point[2] = Vector3(0.5f, 0.5f, -0.5f);
	point[3] = Vector3(0.5f, 0.5f, 0.5f);
	point[4] = Vector3(-0.5f, -0.5f, 0.5f);
	point[5] = Vector3(-0.5f, -0.5f, -0.5f);
	point[6] = Vector3(0.5f, -0.5f, -0.5f);
	point[7] = Vector3(0.5f, -0.5f, 0.5f);
}

//////////////////////////////////////////////
// Name : Translation
//
// Over View : ���W�̐ݒ�
//
// Argument : ���W
//
// Return :  ����
//////////////////////////////////////////////
void Box::Translation(DirectX::SimpleMath::Vector3 pos)
{
	for (int i = 0; i < 8; i++)
	{
		point[i] += pos;
	}
}

//////////////////////////////////////////////
// Name : SetScale
//
// Over View : �傫���̐ݒ�
//
// Argument : �傫��
//
// Return :  ����
//////////////////////////////////////////////
void Box::SetScale(DirectX::SimpleMath::Vector3 scale)
{
	for (int i = 0; i < 8; i++)
	{
		point[i] *= scale;
	}
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
void Box::Initialize()
{
}

//////////////////////////////////////////////
// Name : Draw
//
// Over View : �{�b�N�X�̃f�o�b�O�\��
//
// Argument : ����
//
// Return :  ����
//////////////////////////////////////////////
void Box::Draw()
{
#ifdef DEBUG
	Debug::GetInstance()->DrawLine(point[0], point[1]);
	Debug::GetInstance()->DrawLine(point[1], point[2]);
	Debug::GetInstance()->DrawLine(point[2], point[3]);
	Debug::GetInstance()->DrawLine(point[3], point[0]);
	Debug::GetInstance()->DrawLine(point[4], point[5]);
	Debug::GetInstance()->DrawLine(point[5], point[6]);
	Debug::GetInstance()->DrawLine(point[6], point[7]);
	Debug::GetInstance()->DrawLine(point[7], point[4]);
	Debug::GetInstance()->DrawLine(point[0], point[4]);
	Debug::GetInstance()->DrawLine(point[1], point[5]);
	Debug::GetInstance()->DrawLine(point[2], point[6]);
	Debug::GetInstance()->DrawLine(point[3], point[7]);

#endif //DEBUG
}
