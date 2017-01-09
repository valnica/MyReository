//////////////////////////////////////////////
// Name : ResultStage
//
// Author : �R�c ����
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
// Over View : ���U���g�p�̃X�e�[�W
//////////////////////////////////////////////
class ResultStage
{
private:
	//�n�`
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

