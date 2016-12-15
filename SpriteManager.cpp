#include "SpriteManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

SpriteManager::SpriteManager()
{
}


SpriteManager::~SpriteManager()
{
}

std::shared_ptr<Texture> SpriteManager::LoadSprite(wchar_t * fileName)
{
	//‰æ‘œ‚ðƒLƒƒƒbƒVƒ…‚·‚é
	if (spritePool_.count(fileName) == 0)
		spritePool_[fileName] = std::shared_ptr<Texture>(new Texture(fileName));

	return spritePool_[fileName];
}