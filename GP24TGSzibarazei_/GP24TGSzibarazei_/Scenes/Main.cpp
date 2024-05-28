#include "Main.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Stage/Stage.h"
#include "../Utility/InputControl.h"
#include"DxLib.h"

#define STAGE_DATA	("Resource/datas/stage.csv")

StageDat stagedat;
FILE* fp = NULL;
int block = 0;
int type;

Player* p;

//コンストラクタ
Main::Main() :objects()
{
	Is_pause = false;		//ポーズ状態か（YES＝true、NO＝false）
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
	//ステージの情報を格納（横幅、縦幅）
	stagedat = { 0,0 };

	/*********************オブジェクトを生成する********************/

	//ステージの生成
	//読込ファイルを開く
	fopen_s(&fp, STAGE_DATA, "r");

	//エラーチェック
	if (fp == NULL)
	{
		throw("ファイルが読み込めません\n");
	}
	else
	{
		//ファイルの最後までループする
		while (block != EOF)
		{
			//ファイル情報を１つずつ読み込む
			block = fgetc(fp);
			stagedat.STAGE_WIDTH++;
			
			//カンマは無視する
			if (block == ',')
			{
				stagedat.STAGE_WIDTH--;
				continue;
			}
			//改行する
			else if (block == '\n')
			{
				stagedat.STAGE_HEIGHT++;
				stagedat.STAGE_WIDTH = 0;
				continue;
			}
			//読み込んだ文字が１以上なら、ブロックを生成
			else if (block - '0' > 0)
			{
				type = block;
				CreateObject<Stage>(Vector2D(
					stagedat.STAGE_WIDTH  * 100.0f - 0.f,
					stagedat.STAGE_HEIGHT * 100.0f - 0.f));
			}
		}	
		//ファイルを閉じる
		fclose(fp);
	}

	//プレイヤーを生成
	/*Player* */p = CreateObject<Player>(Vector2D(640.0f, 360.0f));

	//エネミーの生成
	//CreateObject<Enemy>(Vector2D(640.0f, 360.0f))->SetPlayer(p);
}

//更新処理
eSceneType Main::Update()
{
	//ポーズ状態でないなら
	if (Is_pause == false)
	{
		//シーンに存在するオブジェクトの更新処理
		for (GameObject* obj : objects)
		{
			obj->Update();
		}

		//プレイヤーの当たり判定
		for (int i = 0; i < objects.size()-1; i++)
		{
			//当たり判定チェック処理
			HitCheckObject(p,objects[i]);
		}		

		//スタートボタンが押されたら、ポーズする
		if (InputControl::GetButtonDown(XINPUT_BUTTON_START) || InputControl::GetKeyDown(KEY_INPUT_SPACE))
		{
			Is_pause = true;
		}
	}
	//ポーズ状態なら
	else
	{
		//スタートボタンが押されたら、ポーズを解除する
		if (InputControl::GetButtonDown(XINPUT_BUTTON_START) || InputControl::GetKeyDown(KEY_INPUT_SPACE))
		{
			Is_pause = false;
		}
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

	//ステージ情報描画
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			DrawFormatString(j * 20+10, i * 20+50, 0xffff00, "%d", Stage::GetStage(i,j));
		}
	}

	//ポーズ状態の可視化
	if (Is_pause==true)
	{
		SetFontSize(100);
		DrawFormatString(515,310, 0xffffff, "PAUSE");
	}
	SetFontSize(20);

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

//ステージの大きさを取得
StageDat Main::GetStageSiz()
{
	return stagedat;
}

//ステージのタイプを取得
int Main::GetStageType()
{
	return type;
}

//当たり判定チェック処理（矩形の中心で当たり判定をとる）
void Main::HitCheckObject(GameObject* a, GameObject* b)
{
	//２つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//２つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
