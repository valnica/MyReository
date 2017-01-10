//////////////////////////////////////////////
// Class Name : Calling
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "Culling.h"
#include "Object3D.h"
#include "Camera.h"
#include "CollisionManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : Culling
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Culling::Culling()
{
}

//////////////////////////////////////////////
// Name : ~Culling
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Culling::~Culling()
{
}

//////////////////////////////////////////////
// Name : Inview
//
// Over View : 画面内に入ってるかの判定
//
// Argument : ボックス、カメラ、画面内に入ってる判定に必要な頂点の数、
//            画面の幅-1~1、画面の高さ-1~1
//
// Return :  無し
//////////////////////////////////////////////
bool Culling::InView(Box& box,std::weak_ptr<Camera> camera,int required,float sx, float sy)
{
	int num = 0;
	for (int i = 0; i < 8; i++)
	{
		//ビューポート行列を計算
		Matrix trans = Matrix::CreateTranslation(box.point[i]);
		Matrix world = Matrix::Identity;
		Matrix view = camera.lock()->GetView();
		Matrix proj = camera.lock()->GetProj();

		Matrix result = trans * world * view * proj;

		result._41 /= result._44;
		result._42 /= result._44;
		result._43 /= result._44;

		//指定されたビューポートないにあるかどうか
		if (result._41 > -sx && result._41 < sx
			&& result._42 > -sy && result._42 < sy
			&& result._43 >0 && result._43 < 1)
		{
			num++;
		}
	}

	//必要分頂点が入っていれば
	if (num >= required)
		return true;
	else
		return false;
}
