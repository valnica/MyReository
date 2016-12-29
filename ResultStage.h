#pragma once

#include "Stage.h"

class ResultStage:public Stage
{
private:


public:
	ResultStage();
	~ResultStage();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};

