#pragma once

#include"GameObject.h"
#include "../Scenes/SceneBase.h"

class DeleteClass :public GameObject
{
protected:
	//�I�u�W�F�N�g���폜����template���Ăяo�����c
	template <class D>
	D* Deleteclass(GameObject* deleteobject)
	{
		return scene->DeleteObject<D>(deleteobject);
	}

};