//////////////////////////////////////////////
// Name : Debug
//
// Author : �R�c ����
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
// Over View : �f�o�b�O 
//////////////////////////////////////////////
class Debug:public Singleton<Debug>
{
private:
	//�f�o�b�O�ɕK�v�ȕϐ�
	std::unique_ptr<DirectX::BasicEffect> basicEffect_;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> primitiveBatch_;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayOut_;
	
	//�f�o�b�O�̃t���O
	static bool debugFlag_;

	//�����`��p�̕ϐ�
	DirectX::SimpleMath::Vector3 start_;
	DirectX::SimpleMath::Vector3 end_;

	friend class Singleton<Debug>;

	Debug();
public:
	~Debug();

	void Initialize();

	//�����`��
	void DrawLine(DirectX::SimpleMath::Vector3 v1, DirectX::SimpleMath::Vector3 v2);

	//�t���O�̐؂�ւ�
	static void SwitchFlag() { debugFlag_ = !debugFlag_; }
	
	//�t���O�̎擾
	static bool GetFlag() { return debugFlag_; }

	//�����̐ݒ�
	void SetRay(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 end)
	{
		start_ = start;
		end_ = end;
	}

	void Draw();
};