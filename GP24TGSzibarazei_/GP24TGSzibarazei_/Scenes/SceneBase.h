#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

//シーン情報
enum eSceneType
{
	E_TITLE,
	E_HELP,
	E_CHARACTERSELECT,
	E_MAIN,
	E_CLEAR,
	E_RESULT,
	E_END
};

//基底シーンクラス
class SceneBase
{
protected:
	std::vector<GameObject*> objects;
	bool PlayerDown = false;

public:
	SceneBase() {}
	virtual ~SceneBase() {}

	//初期化処理
	virtual void Initialize() {}
	//更新処理
	virtual eSceneType Update()
	{
		return GetNowScene();
	}
	//描画処理
	virtual void Draw() const {}
	//終了時処理
	virtual void Finalize() {}

	virtual void PlayerChange() {
		PlayerDown = true;
	}

	//現在のシーン情報を取得
	virtual eSceneType GetNowScene() const = 0;

	//オブジェクト生成処理
	template <class T>
	T* CreateObject(const Vector2D& location,int type)
	{
		//
		T* new_instance = new T();
		//指定したクラスを生成する
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("ゲームオブジェクトが生成できませんでした");
			exit(-1);
			return nullptr;
		}

		//シーンの情報を設定
		new_object->SetSceneBase(this);

		//初期化処理
		new_object->Initialize(type);
		//位置情報の設定
		new_object->SetLocation(location);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}

	//オブジェクトを削除する
	void DeleteObject(GameObject* deleteobject)
	{
		int i;
		GameObject* delete_object = dynamic_cast<GameObject*>(deleteobject);

		if (delete_object == nullptr)
		{
			delete delete_object;
			throw std::string("ゲームオブジェクトを特定できませんでした");
		}

		//①(オブジェクトの中身を見て一致する) or ②(オブジェクトの最後)までループ
		for (i = 0; i < objects.size(); i++)
		{
			if (delete_object == objects.at(i))
			{
				break;
			}
		}

		//上記のどちらの条件で終了したかの確認:(① and ②)
		if (delete_object != objects.at(i) && i == objects.size())
		{
			throw("オブジェクトの削除が不出来です。");
		}

		//Finalizeを通し、先頭からi番目(削除するオブジェクト)を消す
		delete_object->Finalize();
		objects.erase(objects.begin() + i);
	}
};