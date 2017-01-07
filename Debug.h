//////////////////////////////////////////////
// Name : Debug
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <SimpleMath.h>
#include <wrl.h>
#include "Singleton.h"

//////////////////////////////////////////////
// Class Name : Debug
//
// Over View : デバッグ 
//////////////////////////////////////////////
class Debug:public Singleton<Debug>
{
private:
	//デバッグに必要な変数
	std::unique_ptr<DirectX::BasicEffect> basicEffect_;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> primitiveBatch_;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayOut_;
	
	//デバッグのフラグ
	static bool debugFlag_;

	//線分描画用の変数
	DirectX::SimpleMath::Vector3 start_;
	DirectX::SimpleMath::Vector3 end_;

	friend class Singleton<Debug>;

	Debug();
public:
	~Debug();

	void Initialize();

	//線分描画
	void DrawLine(DirectX::SimpleMath::Vector3 v1, DirectX::SimpleMath::Vector3 v2);

	//フラグの切り替え
	static void SwitchFlag() { debugFlag_ = !debugFlag_; }
	
	//フラグの取得
	static bool GetFlag() { return debugFlag_; }

	//線分の設定
	void SetRay(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end)
	{
		start_ = start;
		end_ = end;
	}

	void Draw();
};