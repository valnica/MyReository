#pragma once

#include <map>
#include "Texture.h"
#include "Singleton.h"

class SpriteManager:public Singleton<SpriteManager>
{
private:
	std::map<std::wstring, std::shared_ptr<Texture>> spritePool_;

	friend class Singleton<SpriteManager>;

protected:
	SpriteManager();

public:
	~SpriteManager();

	std::shared_ptr<Texture> LoadSprite(wchar_t* fileName = nullptr);
};

