//////////////////////////////////////////////
// Name : Sprite
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "Sprite.h"
#include "SpriteManager.h"
#include "DirectXTK.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//////////////////////////////////////////////
// Name : Box2D
//
// Over View : コンストラクタ
//
// Argument : ボックスの４頂点の座標
//////////////////////////////////////////////
Box2D::Box2D(float top, float left, float bottom, float right)
	:top_(top), left_(left)
	, bottom_(bottom), right_(right)
{

}

//////////////////////////////////////////////
// Name : Sprite
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Sprite::Sprite()
{
	pos_ = Vector2::Zero;
	rect_ = RECT{ 0,0,0,0 };
	color_ = Colors::White.v;
	angle_ = 0.0f;
	scale_ = 0.0f;
	depth_ = 0.0f;
}

//////////////////////////////////////////////
// Name : ~Sprite
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
Sprite::~Sprite()
{
}

//////////////////////////////////////////////
// Name : Initialize
//
// Over View : 初期化処理
//
// Argument : 画像のパス、座標、切り取り範囲、
//            アンカーを中心にするかのフラグ、色、
//            回転角、大きさ、震度
//
// Return :  無し
//////////////////////////////////////////////
void Sprite::Initialize(wchar_t * texturePass, DirectX::SimpleMath::Vector2 pos, RECT rect, bool origineFlag, Color color, float angle, float scale, float depth)
{
	sprite_ = SpriteManager::GetInstance()->LoadSprite(texturePass);
	pos_ = pos;
	rect_ = rect;
	origineFlag_ = origineFlag;
	color_ = color;
	angle_ = 3.14f / 180.0f * angle;
	scale_ = scale;
	depth_ = depth;
}

//////////////////////////////////////////////
// Name : Draw
//
// Over View : 描画処理
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
void Sprite::Draw()
{
	//起点の設定
	Vector2 origine(0.0f, 0.0f);

	//flagがtrueならば画像の中心を起点に描画
	if (origineFlag_)
		origine = Vector2((rect_.right - rect_.left) / 2.0f, (rect_.bottom - rect_.top) / 2.0f);
	g_spriteBatch->Draw(sprite_.lock()->m_pTexture, pos_, &rect_, color_, angle_, origine, scale_, SpriteEffects_None, depth_);
}

//////////////////////////////////////////////
// Name : SetPos
//
// Over View : 座標の設定
//
// Argument : 座標
//
// Return :  無し
//////////////////////////////////////////////
void Sprite::SetPos(DirectX::SimpleMath::Vector2 pos)
{
	pos_ = pos;
}

//////////////////////////////////////////////
// Name : SetRect
//
// Over View : 切り取り範囲の設定
//
// Argument : 切り取り範囲
//
// Return :  無し
//////////////////////////////////////////////
void Sprite::SetRect(RECT rect)
{
	rect_ = rect;
}

//////////////////////////////////////////////
// Name : GetPos
//
// Over View : 座標の設定
//
// Argument : 無し
//
// Return :  無し
//////////////////////////////////////////////
DirectX::SimpleMath::Vector2 Sprite::GetPos()
{
	return pos_;
}

//////////////////////////////////////////////
// Name : SetOrigineFlag
//
// Over View : アンカーを中心にするフラグの設定
//
// Argument : アンカーを中心にするフラグ
//
// Return :  無し
//////////////////////////////////////////////
void Sprite::SetOrigineFlag(bool flag)
{
	origineFlag_ = flag;
}

//////////////////////////////////////////////
// Name : GetBox
//
// Over View : 当たり判定用のボックスの取得
//
// Argument : 無し
//
// Return :  ボックス
//////////////////////////////////////////////
Box2D Sprite::GetBox()
{
	if (origineFlag_)
	{
		float offsetX = (rect_.right - rect_.left) / 2.0f;
		float offsetY = (rect_.bottom + rect_.top) / 2.0f;
		return Box2D(pos_.y - offsetY, pos_.x - offsetX, pos_.y + offsetY, pos_.x + offsetX);
	}
	return Box2D(pos_.y, pos_.x, pos_.y + (rect_.bottom + rect_.top), pos_.x + (rect_.right - rect_.left));
}

//////////////////////////////////////////////
// Name : SetAlpha
//
// Over View : 透明度の設定
//
// Argument : 透明度
//
// Return :  無し
//////////////////////////////////////////////
void Sprite::SetAlpha(float alpha)
{
	color_.A(alpha);
}


