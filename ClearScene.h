#pragma once

#include "Scene.h"

class ClearScene:public Scene
{
private:

public:
	ClearScene();
	~ClearScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};

