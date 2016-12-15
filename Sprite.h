#pragma once

#include "Texture.h"
#include <SimpleMath.h>
#include <DirectXColors.h>
#include <memory>

class Box2D
{
public:
	Box2D(float top, float left, float bottom, float right);
	float top_;
	float left_;
	float bottom_;
	float right_;
};

class Sprite
{
private:
	std::weak_ptr<Texture> sprite_;
	DirectX::SimpleMath::Vector2 pos_;
	RECT rect_;
	DirectX::SimpleMath::Color color_;
	float angle_;
	float scale_;
	float depth_;
	bool origineFlag_;

public:
	Sprite();
	~Sprite();

	void Initialize(wchar_t* texturePass, DirectX::SimpleMath::Vector2 pos, RECT rect, bool origineFlag = false, DirectX::SimpleMath::Color = DirectX::Colors::White.v, float angle = 0.0f, float scale = 1.0f, float depth = 0.0f);
	void Draw();

	void SetPos(DirectX::SimpleMath::Vector2 pos);
	void SetRect(RECT rect);
	DirectX::SimpleMath::Vector2 GetPos();
	void SetOrigineFlag(bool flag);
	Box2D GetBox();
	void SetAlpha(float alpha);
};

