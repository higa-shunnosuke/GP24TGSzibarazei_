#include "Main.h"

#include "../Objects/Player/Player.h"
#include "../Objects/Stage/Stage.h"

//コンストラクタ
Main::Main() :objects()
{}

//デストラクタ
Main::~Main()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Main::Initialize()
{
	//プレイヤーを生成する
	CreateObject<Stage>(Vector2D(640.0f, 360.0f));
	CreateObject<Player>(Vector2D(640.0f, 360.0f));
}

//更新処理
void Main::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}
}

//描画処理
void Main::Draw() const
{
	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
void Main::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();
}

