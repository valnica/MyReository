#include "Sprite.h"
#include "SpriteManager.h"
#include "DirectXTK.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Box2D::Box2D(float top, float left, float bottom, float right)
	:top_(top), left_(left)
	, bottom_(bottom), right_(right)
{

}

Sprite::Sprite()
{
	pos_ = Vector2::Zero;
	rect_ = RECT{ 0,0,0,0 };
	color_ = Colors::White.v;
	angle_ = 0.0f;
	scale_ = 0.0f;
	depth_ = 0.0f;
}


Sprite::~Sprite()
{
}

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

void Sprite::Draw()
{
	//起点の設定
	Vector2 origine(0.0f, 0.0f);
	//flagがtrueならば画像の中心を起点に描画
	if (origineFlag_)
		origine = Vector2((rect_.right - rect_.left) / 2.0f, (rect_.bottom - rect_.top) / 2.0f);
	g_spriteBatch->Draw(sprite_.lock()->m_pTexture, pos_, &rect_, color_, angle_, origine, scale_, SpriteEffects_None, depth_);
}

void Sprite::SetPos(DirectX::SimpleMath::Vector2 pos)
{
	pos_ = pos;
}

void Sprite::SetRect(RECT rect)
{
	rect_ = rect;
}

DirectX::SimpleMath::Vector2 Sprite::GetPos()
{
	return pos_;
}

void Sprite::SetOrigineFlag(bool flag)
{
	origineFlag_ = flag;
}

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

void Sprite::SetAlpha(float alpha)
{
	color_.A(alpha);
}


