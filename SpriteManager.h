//////////////////////////////////////////////
// Name : SpriteManager
//
// Author : �R�c ����
//
// Date : 2017/1/10
//////////////////////////////////////////////
#pragma once

#include "Singleton.h"

#include "Used\Texture.h"

#include <map>

//////////////////////////////////////////////
// Class Name : SpriteManager
//
// Over View : �摜�̊Ǘ��N���X
//////////////////////////////////////////////
class SpriteManager:public Singleton<SpriteManager>
{
private:
	//�摜�ۑ��v�[��
	std::map<std::wstring, std::shared_ptr<Texture>> spritePool_;

	friend class Singleton<SpriteManager>;

protected:
	SpriteManager();

public:
	~SpriteManager();

	//�摜�ǂݍ���
	std::shared_ptr<Texture> LoadSprite(wchar_t* fileName = nullptr);
};

