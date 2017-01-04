#pragma once

#include <memory>
#include <vector>

class LandShape;
class Marker;

class ResultStage
{
private:
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

