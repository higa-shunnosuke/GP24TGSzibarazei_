#pragma once

#include "GameObject.h"
#include "../Scenes/SceneBase.h"

class CreateClass : public GameObject
{
protected:
	template <class T>
	T* CreateObject(const Vector2D& location,int type)
	{
		return SB->CreateObject<T>(location,type);
	}
};