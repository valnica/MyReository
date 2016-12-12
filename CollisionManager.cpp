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

void CollisionManager::Reset()
{
	//登録されてるオブジェクトのリセット
	player_.clear();
	enemy_.clear();
	landShape_.clear();
	marker_.clear();
	camera = nullptr;
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
	event_.clear();
}

void CollisionManager::Update()
{
	Collision collision;

	////////////////////////キャラと地形//////////////////////////////////

	for (auto player = player_.begin(); player != player_.end(); player++)
	{
		for (auto landShape = landShape_.begin(); landShape != landShape_.end(); landShape++)
		{
			//空間分割用の変数
			Grid grid;
			SphereNode sphere = (*player)->GetCollisionBody();
			Point3D point1 = grid.Calc3DPoint((*player)->GetPosition());
			Point3D point2 = grid.Calc3DPoint((*landShape)->GetTrans());

			//分割した空間が隣接空間であるかどうか
			if (!collision.NearPoint(point1, point2))
			{
				continue;
			}

			//プレイヤーと地形の当たり判定
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

	////////////////////////敵から自分への視線判定/////////////////////////
	for (auto player = player_.begin(); player != player_.end(); player++)
	{
		for (auto enemy = enemy_.begin(); enemy != enemy_.end(); enemy++)
		{
			//視野内かどうかの判定するための変数構築
			Vector3 eye = (*enemy)->GetPosition();
			Vector3 ref = (*player)->GetEyePosition();
			float eyeAngle = (*enemy)->GetRotate().y;
			float viewAngle = (*enemy)->GetViewAngle();
			float viewDistance = (*enemy)->GetViewDistance();
			ViewInfo viewInfo(eye, ref, viewAngle, eyeAngle, viewDistance);

			//視野内かどうか
			if (collision.InFrontView(viewInfo))
			{
				//raycast用の変数構築
				Vector3 origine = (*enemy)->GetPosition() + Vector3(0.0f, 1.0f, 0.0f);
				Vector3 ref = (*player)->GetEyePosition();

				//Rayが交差したオブジェクトを検索
				LandShape* land = collision.RayCast(origine, ref);

				//raycastでオブジェクトに当たっていなかったら見つかっている
				if (!land)
				{
					SceneManager::GetInstance()->ChageScene(SceneManager::SCENEID::GAMEOVER);
				}
			}

			//遮蔽物があるかないか判定
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

	////////////////////////自分とイベントとの当たり判定/////////////////////////

	for (auto player = player_.begin(); player != player_.end(); player++)
	{
		for (auto events = event_.begin(); events != event_.end();)
		{
			//当たり判定
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

	////////////////////////////カメラとオブジェクト//////////////////////////
	if (camera)
	{
		Vector3 inter{};
		float distance = 10e10;
		for (auto it = landShape_.begin(); it != landShape_.end(); it++)
		{
			Segment segment;
			segment.start_ = camera->GetTarget();
			segment.end_ = camera->GetEye();

			if ((*it)->IntersectSegment(segment, &inter, 90))
			{
				if (distance > inter.Length())
				{
					distance = inter.Length();
					Vector3 offset = segment.start_ - inter;
					offset.Normalize();
					camera->SetEye(inter + offset);
					camera->Update();
				}
			}
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

void CollisionManager::Entry(Camera * mainCamera)
{
	camera = mainCamera;
}

//CollisionManager* CollisionManager::GetInstance()
//{
//	static CollisionManager* instance_ = nullptr;
//
//	if (!instance_)
//		instance_ = new CollisionManager;
//
//	return instance_;
//}

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
