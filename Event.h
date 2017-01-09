//////////////////////////////////////////////
// Class Name : Event
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include "CollisionManager.h"
#include <SimpleMath.h>

class Stage;

//////////////////////////////////////////////
// Class Name : Event
//
// Over View : ゲームイベント用の基底クラス
//////////////////////////////////////////////
class Event
{
protected:
	//当たり判定オブジェクト
	Box box_;

public:
	Event() {};
	virtual ~Event() {};

	virtual void Initialize() {};
	virtual bool Run() = 0 ;
	virtual void Render() {};
	
	//当たり判定オブジェクトの取得
	Box GetBox() { return box_; }
};

//////////////////////////////////////////////
// Class Name : ClearEvent
//
// Over View : クリアイベント
//////////////////////////////////////////////
class ClearEvent :public Event
{
private:
	//座標
	DirectX::SimpleMath::Vector3 pos_;

	//当たり判定オブジェクトの大きさ
	DirectX::SimpleMath::Vector3 scale_;

public:
	ClearEvent() {};
	~ClearEvent() {};

	void Initialize();
	bool Run() override;
	void Render()
	{
		box_.Draw();
	}

	//座標の設定
	void SetPosition(DirectX::SimpleMath::Vector3 pos)
	{
		pos_ = pos;
	}

	//当たり判定オブジェクトの大きさの設定
	void SetScale(DirectX::SimpleMath::Vector3 scale)
	{
		scale_ = scale;
	}

	//当たり判定オブジェクトの設定
	void SetBox(Box box)
	{
		box_ = box;
		box_.SetScale(scale_);
		box_.Translation(pos_ + DirectX::SimpleMath::Vector3(0.0f, scale_.y / 2.0f, 0.0f));
	}
};