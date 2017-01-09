//////////////////////////////////////////////
// Name : Flash
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once
#include "Effect.h"
#include <memory>

class Sprite;

//////////////////////////////////////////////
// Class Name : Flash
//
// Over View : �t���b�V���G�t�F�N�g
//////////////////////////////////////////////
class Flash:public Effect
{
private:
	//�t���b�V���p�̉摜
	std::unique_ptr<Sprite> sprite_;
	
	//�����x
	float alpha_;

public:
	Flash();
	~Flash();

	void Initialize() override;
	bool Update() override;
	void Render() override;
};

