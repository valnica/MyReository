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

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

void CollisionManager::Reset()
{
	player_.clear();
	enemy_.clear();
	landShape_.clear();
	marker_.clear();
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::Initialize()
{
	player_.clear();
	enemy_.clear();
	landShape_.clear();
	marker_.clear();
}

void CollisionManager::Update()
{
	Collision collision;

	////////////////////////�L�����ƒn�`//////////////////////////////////

	for (auto player = player_.begin(); player != player_.end(); player++)
	{
		for (auto landShape = landShape_.begin(); landShape != landShape_.end(); landShape++)
		{
			Grid grid;
			SphereNode sphere = (*player)->GetCollisionBody();
			Point3D point1 = grid.Calc3DPoint((*player)->GetPosition());
			Point3D point2 = grid.Calc3DPoint((*landShape)->GetTrans());
			
			/*if (!collision.NearPoint(point1, point2))
			{
				continue;
			}*/

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

				LandShape* land = collision.RayCast(origine, ref);

				//raycast�ŃI�u�W�F�N�g�ɓ������Ă��Ȃ������猩�����Ă���
				if (!land)
				{
					SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::GAMEOVER);
				}
			}

			//�Օ��������邩�Ȃ�������
			/*Camera camera(640, 480);
			camera.SetEye((*enemy)->GetPositon());
			Vector3 ref(0.0f, 0.0f, -(*enemy)->GetViewDistance());
			Matrix rot = Matrix::CreateRotationY((*enemy)->GetRotate().y * 3.14f / 180.0f);
			ref = Vector3::TransformNormal(ref, rot);
			camera.SetTarget((*enemy)->GetPositon() + ref);
			camera.Update();*/

			//if (Culling::InView((*landShape)->GetBox(), &camera, 1))

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
					if((*events))
						delete *events;
					events = event_.erase(events);
				}
				else
				{
					events++;
					continue;
				}
			}
			else
				events++;
		}
	}

	Reset();
}

void CollisionManager::Entry(Player * player)
{
	player_.push_back(player);
}

void CollisionManager::Entry(Enemy * enemy)
{
	enemy_.push_back(enemy);
}

void CollisionManager::Entry(LandShape * landShape)
{
	landShape_.push_back(landShape);
}

void CollisionManager::Entry(Marker * marker)
{
	marker_.push_back(marker);
}

void CollisionManager::Entry(Event * events)
{
	event_.push_back(events);
}

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager* instance_ = nullptr;

	if (!instance_)
		instance_ = new CollisionManager;

	return instance_;
}

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

void Box::Translation(DirectX::SimpleMath::Vector3 pos)
{
	for (int i = 0; i < 8; i++)
	{
		point[i] += pos;
	}
}

void Box::SetScale(DirectX::SimpleMath::Vector3 scale)
{
	for (int i = 0; i < 8; i++)
	{
		point[i] *= scale;
	}
}

void Box::Initialize()
{
}

void Box::Draw()
{
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
}
