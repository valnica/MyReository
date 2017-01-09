//////////////////////////////////////////////
// Name : SpriteManager
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#include "SpriteManager.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

//////////////////////////////////////////////
// Name : SpriteManager
//
// Over View : コンストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
SpriteManager::SpriteManager()
{
}

//////////////////////////////////////////////
// Name : ~SpriteManager
//
// Over View : デストラクタ
//
// Argument : 無し
//////////////////////////////////////////////
SpriteManager::~SpriteManager()
{
}

//////////////////////////////////////////////
// Name : LoadSprite
//
// Over View : 画像の読み込み
//
// Argument : 画像のパス
//
// Return :  画像のポインタ
//////////////////////////////////////////////
std::shared_ptr<Texture> SpriteManager::LoadSprite(wchar_t * fileName)
{
	//画像をキャッシュする
	if (spritePool_.count(fileName) == 0)
		spritePool_[fileName] = std::shared_ptr<Texture>(new Texture(fileName));

	return spritePool_[fileName];
}