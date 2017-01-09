//////////////////////////////////////////////
// Name : SpriteManager
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include <map>
#include "Texture.h"
#include "Singleton.h"

//////////////////////////////////////////////
// Class Name : SpriteManager
//
// Over View : 画像の管理クラス
//////////////////////////////////////////////
class SpriteManager:public Singleton<SpriteManager>
{
private:
	//画像保存プール
	std::map<std::wstring, std::shared_ptr<Texture>> spritePool_;

	friend class Singleton<SpriteManager>;

protected:
	SpriteManager();

public:
	~SpriteManager();

	//画像読み込み
	std::shared_ptr<Texture> LoadSprite(wchar_t* fileName = nullptr);
};

