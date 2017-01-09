//////////////////////////////////////////////
// Name : Stage
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once
#include <vector>
#include <SimpleMath.h>
#include "CollisionManager.h"

class LandShape;
class Marker;
class ClearEvent;

//////////////////////////////////////////////
// Class Name : Stage
//
// Over View : ゲームステージ
//////////////////////////////////////////////
class Stage
{
protected:
	//ステージに必要なオブジェクト
	std::vector<std::shared_ptr<LandShape>> landshapeList_;
	std::shared_ptr<Marker> marker_;
	std::shared_ptr<ClearEvent> clearEvent_;
	
	//プレイヤーのスタート座標
	DirectX::SimpleMath::Vector3 startPos_;
	
	//クリアフラグ
	static bool clearFlag_;

public:
	Stage();
	virtual ~Stage();

	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Finalize();

	//クリアフラグの設定
	static void SetClearFlag() { clearFlag_ = true; }
	
	//スタート座標の取得
	DirectX::SimpleMath::Vector3 GetStartPos() { return startPos_; }
	
	//クリアフラグの取得
	static bool GetClearFlag() { return clearFlag_; }
};

