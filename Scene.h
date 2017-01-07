//////////////////////////////////////////////
// Name : Scene
//
// Author : 山田 聖弥
//
// Date : 2017/1/8 
//////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////
// Class Name : Scene
//
// Over View : シーンの基底クラス
//////////////////////////////////////////////
class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Finalize() = 0;
};

