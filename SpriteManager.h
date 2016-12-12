#pragma once

#include <map>
#include "Texture.h"

class SpriteManager
{
private:
	static SpriteManager* instance_;
	std::map<std::wstring, Texture*> spritePool_;

	void TextureRelease();
protected:
	SpriteManager();

public:
	~SpriteManager();

	Texture* LoadSprite(wchar_t* fileName = nullptr);
	static SpriteManager* GetInstance();
};

