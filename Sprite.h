//////////////////////////////////////////////
// Name : Sprite
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include "Texture.h"
#include <SimpleMath.h>
#include <DirectXColors.h>
#include <memory>

//////////////////////////////////////////////
// Class Name : Box2D
//
// Over View : 2D用のボックス当たり判定
//////////////////////////////////////////////
class Box2D
{
public:
	Box2D(float top, float left, float bottom, float right);

	//各頂点
	float top_;
	float left_;
	float bottom_;
	float right_;
};

//////////////////////////////////////////////
// Class Name : Sprite
//
// Over View : 画像クラス
//////////////////////////////////////////////
class Sprite
{
private:
	//画像
	std::weak_ptr<Texture> sprite_;
	
	//座標
	DirectX::SimpleMath::Vector2 pos_;
	
	//切り取り範囲
	RECT rect_;
	
	//色
	DirectX::SimpleMath::Color color_;
	
	//回転角
	float angle_;
	
	//大きさ
	float scale_;
	
	//震度
	float depth_;
	
	//アンカーを中心にするかのフラグ
	bool origineFlag_;

public:
	Sprite();
	~Sprite();

	void Initialize(wchar_t* texturePass, DirectX::SimpleMath::Vector2 pos, RECT rect, bool origineFlag = false, DirectX::SimpleMath::Color = DirectX::Colors::White.v, float angle = 0.0f, float scale = 1.0f, float depth = 0.0f);
	void Draw();

	//座標の設定
	void SetPos(DirectX::SimpleMath::Vector2 pos);
	
	//切り取り範囲の設定
	void SetRect(RECT rect);
	
	//座標の取得
	DirectX::SimpleMath::Vector2 GetPos();
	
	//アンカーのフラグ設定
	void SetOrigineFlag(bool flag);
	
	//当たり判定用のボックスの取得
	Box2D GetBox();
	
	//透明度の設定
	void SetAlpha(float alpha);
};

