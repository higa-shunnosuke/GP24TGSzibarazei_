#include "Main.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Stage/Stage.h"
#include"DxLib.h"

#define STAGE_DATA		("Resource/datas/stage.csv")


FILE* fp = NULL;
int block = 0;
int STAGE_WIDTH;
int STAGE_HEIGHT;

//コンストラクタ
Main::Main() :objects()
{

}

//デストラクタ
Main::~Main()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Main::Initialize()
{
	STAGE_WIDTH = 0;
	STAGE_HEIGHT = 0;

	/*********************オブジェクトを生成する********************/

	//読込ファイルを開く
	fopen_s(&fp, STAGE_DATA, "r");

	//エラーチェック
	if (fp == NULL)
	{

	}
	else
	{
		while (true)
		{
			block = fgetc(fp);
			STAGE_WIDTH++;
			if (block == EOF)
			{
				break;
			}
			else if (block == ',')
			{
				STAGE_WIDTH--;
				continue;
			}
			else if (block == '\n')
			{
				STAGE_HEIGHT++;
				STAGE_WIDTH = 0;
				continue;
			}
			else if (block > 48)
			{
				CreateObject<Stage>(Vector2D(STAGE_WIDTH * 50.0f, STAGE_HEIGHT * 50.0f));
			}
		}	

		fclose(fp);
	}

	
	//プレイヤーを生成
	CreateObject<Player>(Vector2D(640.0f, 360.0f));

}

//更新処理
eSceneType Main::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	return GetNowScene();

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

//現在のシーン情報を取得
eSceneType Main::GetNowScene()const
{
	return eSceneType::E_MAIN;
}
