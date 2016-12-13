#pragma once

#include <map>
#include "Texture.h"
#include "Singleton.h"

class SpriteManager:public Singleton<SpriteManager>
{
private:
	std::map<std::wstring, Texture*> spritePool_;

	friend class Singleton<SpriteManager>;

	void TextureRelease();
protected:
	SpriteManager();

public:
	~SpriteManager();

	Texture* LoadSprite(wchar_t* fileName = nullptr);
	//static SpriteManager* GetInstance();
};

