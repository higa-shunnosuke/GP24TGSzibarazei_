#pragma once

#include"GameObject.h"
#include "../Scenes/SceneBase.h"

class DeleteClass :public GameObject
{
protected:
	//オブジェクトを削除するtemplateを呼び出すヤツ
	template <class D>
	D* Deleteclass(GameObject* deleteobject)
	{
		return scene->DeleteObject<D>(deleteobject);
	}

};