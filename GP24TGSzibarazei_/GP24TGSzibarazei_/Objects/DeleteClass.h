#pragma once

#include"GameObject.h"
#include "../Scenes/SceneBase.h"

class DeleteClass :public GameObject
{
protected:
	//オブジェクトを削除するtemplateを呼び出すヤツ
void Deleteclass(GameObject* deleteobject)
	{
		return SB->DeleteObject(deleteobject);
	}

};