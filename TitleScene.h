#pragma once

#include "Scene.h"

class TitleScene:public Scene
{
private:

public:
	TitleScene();
	~TitleScene();

	void Initialize() override;
	void Update() override;
	void Render() override;
	void Finalize() override;
};

