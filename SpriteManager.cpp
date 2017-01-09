//////////////////////////////////////////////
// Name : SpriteManager
//
// Author : �R�c ����
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "SpriteManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

//////////////////////////////////////////////
// Name : SpriteManager
//
// Over View : �R���X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
SpriteManager::SpriteManager()
{
}

//////////////////////////////////////////////
// Name : ~SpriteManager
//
// Over View : �f�X�g���N�^
//
// Argument : ����
//////////////////////////////////////////////
SpriteManager::~SpriteManager()
{
}

//////////////////////////////////////////////
// Name : LoadSprite
//
// Over View : �摜�̓ǂݍ���
//
// Argument : �摜�̃p�X
//
// Return :  �摜�̃|�C���^
//////////////////////////////////////////////
std::shared_ptr<Texture> SpriteManager::LoadSprite(wchar_t * fileName)
{
	//�摜���L���b�V������
	if (spritePool_.count(fileName) == 0)
		spritePool_[fileName] = std::shared_ptr<Texture>(new Texture(fileName));

	return spritePool_[fileName];
}