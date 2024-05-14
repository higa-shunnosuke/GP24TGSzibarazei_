#pragma once

#include "SceneBase.h"
#include"vector"
#include"string"
#include"../Objects/GameObject.h"

class Main:public SceneBase
{
private:
	std::vector<GameObject*> objects;

public:
	Main();
	~Main();

	//初期化処理
	virtual void Initialize() override;
	//更新処理
	virtual eSceneType Update() override;
	//描画処理
	virtual void Draw() const override;
	//終了時処理
	virtual void Finalize() override;
	//現在のシーンをか取得
	virtual eSceneType GetNowScene() const override;

private:
	//オブジェクト生成処理
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//
		T* new_instance = new T();
		//指定したクラスを生成する
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}

		//初期化処理
		new_object->Initialize();
		//位置情報の設定
		new_object->SetLocation(location);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};

