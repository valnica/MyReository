//////////////////////////////////////////////
// Name : CollitionNode
//
// Author : 山田 聖弥
//
// Date : 2017/1/10
//////////////////////////////////////////////
#include "CollisionNode.h"
#include "Debug.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace DirectX;
using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : ShereNode
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
SphereNode::SphereNode()
{
	//初期設定
	localRadius_ = 1.0f;
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void SphereNode::Initialize()
{
	//当たり判定用のモデルの読み込み
	object_.LoadModelFromFile(L"Resources\\cModels\\HitSphere.cmo");
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void SphereNode::Update()
{
	//座標の設定
	object_.SetTrans(trans_);
	Vector3 localScale;

	//大きさの設定
	localScale = Vector3(1, 1, 1);

	//大きさの変更
	localScale.x = localRadius_;
	localScale.y = localRadius_;
	localScale.z = localRadius_;
	object_.SetScale(localScale);

	object_.Calc();

	//球の計算
	Matrix world = object_.GetWorld();
	Vector3 center(0.0f, 0.0f, 0.0f);
	Vector3 right(1.0f, 0.0f, 0.0f);

	center = Vector3::Transform(center, world);
	right = Vector3::Transform(right, world);

	center_ = center;
	radius_ = Vector3::Distance(center, right);
}

//////////////////////////////////////////////
// Name : Draw
//
// Over View : 球のデバッグ表示
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void SphereNode::Draw()
{
#ifdef DEBUG
	if (Debug::GetFlag())
		object_.Draw();
#endif
}

//////////////////////////////////////////////
// Name : SetParentMatrix
//
// Over View : 親オブジェクトの設定
//
// Argument : 親オブジェクトの行列
//
// Return :  無し
//////////////////////////////////////////////
void SphereNode::SetParentMatrix(const DirectX::SimpleMath::Matrix * parent)
{
	object_.SetParentWorld(parent);
}

//////////////////////////////////////////////
// Name : CapsuleNode
//
// Over View : コンストラクタ
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
CapsuleNode::CapsuleNode()
{
	//初期設定
	localLenght_ = 1.0f;
	localRadius_ = 1.0f;
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void CapsuleNode::Initialize()
{
	//当たり判定用のモデルの読み込み
	object_.LoadModelFromFile(L"Resources\\cModels\\HitCapsule.cmo");
}

//////////////////////////////////////////////
// Name : Update
//
// Over View : 更新処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void CapsuleNode::Update()
{
	//座標の設定
	object_.SetTrans(trans_);
	
	//大きさの設定
	Vector3 localScale;
	localScale.x = localRadius_;
	localScale.z = localRadius_;
	localScale.y = localLenght_;
	object_.SetScale(localScale);
	object_.Calc();

	Matrix world = object_.GetWorld();
	Vector3 center(0.0f, 0.0f, 0.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);
	Vector3 right(1.0f, 0.0f, 0.0f);
	
	//World計算
	center = Vector3::Transform(center, world);
	up = Vector3::Transform(up, world);
	right = Vector3::Transform(right, world);

	//大きさの更新
	segment_.start_ = center;
	segment_.end_ = up;
	radius_ = Vector3::Distance(center, right);
}

//////////////////////////////////////////////
// Name : Draw
//
// Over View : カプセルのデバッグ描画
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void CapsuleNode::Draw()
{
#ifdef DEBUG
	if (Debug::GetFlag())
		object_.Draw();
#endif
}

//////////////////////////////////////////////
// Name : SetParentMatrix
//
// Over View : 親オブジェクトの設定
//
// Argument : 親オブジェクトの行列
//
// Return :  無し
//////////////////////////////////////////////
void CapsuleNode::SetParentMatrix(const DirectX::SimpleMath::Matrix * parent)
{
	object_.SetParentWorld(parent);
}

//////////////////////////////////////////////
// Name : SetRotate
//
// Over View : カプセルを回転させる
//
// Argument : 回転角
//
// Return :  無し
//////////////////////////////////////////////
void CapsuleNode::SetRotate(DirectX::SimpleMath::Vector3 & rotate)
{
	object_.SetRotate(rotate);
}