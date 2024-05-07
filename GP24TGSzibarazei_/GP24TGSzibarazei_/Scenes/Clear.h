#pragma once

#include "SceneBase.h"

class Clear :public SceneBase
{
private:
	int background_image; //”wŒi‰æ‘œ

public:
	Clear();
	virtual ~Clear();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};