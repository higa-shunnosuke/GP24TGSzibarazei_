#pragma once

#include"GameObject.h"
#include "../Scenes/SceneBase.h"

class DeleteClass :public GameObject
{
protected:
	//�I�u�W�F�N�g���폜����template���Ăяo�����c
void Deleteclass(GameObject* deleteobject)
	{
		return SB->DeleteObject(deleteobject);
	}

};