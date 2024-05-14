#pragma once

#include "SceneBase.h"

class CharacterSelect :public SceneBase
{
private:

private:
	int background_image;
	int cursor_image;
	int menu_cursor;

public:
	CharacterSelect();
	virtual ~CharacterSelect();

	virtual void  Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
};

