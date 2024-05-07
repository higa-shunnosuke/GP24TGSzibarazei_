#include "Main.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Stage/Stage.h"

#define STAGE_WIDTH		(30)
#define STAGE_HEIGHT	(20)

Stage* stage[STAGE_HEIGHT][STAGE_WIDTH];//ステージの[縦][横]


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
	FILE* fp;

	//オブジェクトを生成する
	
	//読込ファイルを開く
	fopen_s(&fp, "../Resource/datas/stage.csv", "r");

	/*for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			fscanf(fp, "%d,%[^,],%d", &stage[i][j]);
		}
	}
	fclose(fp);*/
	
	CreateObject<Stage>(Vector2D(640.0f, 360.0f));
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
