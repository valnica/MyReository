//////////////////////////////////////////////
// Name : ResultStage
//
// Author : 山田 聖弥
//
// Date : 2017/1/9
//////////////////////////////////////////////
#pragma once

#include <memory>
#include <vector>

class LandShape;
class Marker;

//////////////////////////////////////////////
// Class Name : ResultStage
//
// Over View : リザルト用のステージ
//////////////////////////////////////////////
class ResultStage
{
private:
	//地形
	std::vector<std::shared_ptr<LandShape>> landshapeList_;
	std::shared_ptr<Marker> marker_;

public:
	ResultStage();
	~ResultStage();

	void Initialize();
	void Update();
	void Render();
	void Finalize();
};

