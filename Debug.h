#pragma once

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <SimpleMath.h>
#include "Singleton.h"

class Debug:public Singleton<Debug>
{
private:
	std::unique_ptr<DirectX::BasicEffect> basicEffect_;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> primitiveBatch_;
	ID3D11InputLayout* inputLayOut_;
	static bool debugFlag_;
	DirectX::SimpleMath::Vector3 start_;
	DirectX::SimpleMath::Vector3 end_;

	friend class Singleton<Debug>;

	Debug();
public:
	~Debug();

	void Initialize();
	void DrawLine(DirectX::SimpleMath::Vector3 v1, DirectX::SimpleMath::Vector3 v2);

	static void SwitchFlag() { debugFlag_ = !debugFlag_; }
	static bool GetFlag() { return debugFlag_; }

	void SetRay(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end)
	{
		start_ = start;
		end_ = end;
	}

	void Draw();
};