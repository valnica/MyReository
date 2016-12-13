#include "SpriteManager.h"

void SpriteManager::TextureRelease()
{
	auto it = spritePool_.begin();
	while (it != spritePool_.end())
	{
		delete it->second;
		it = spritePool_.erase(it);
	}
}

SpriteManager::SpriteManager()
{
}


SpriteManager::~SpriteManager()
{
	TextureRelease();
}

Texture * SpriteManager::LoadSprite(wchar_t * fileName)
{
	//‰æ‘œ‚ðƒLƒƒƒbƒVƒ…‚·‚é
	if (spritePool_.count(fileName) == 0)
		spritePool_[fileName] = new Texture(fileName);

	return spritePool_[fileName];
}