#include "Main.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/Enemy_Attack.h"
#include "../Objects/Stage/Stage.h"
#include "../Utility/InputControl.h"
#include"DxLib.h"

#define STAGE_DATA	("Resource/datas/stage.csv")

StageDat stagedat;
FILE* fp = NULL;
int block = 0;
int type;

//コンストラクタ
Main::Main()
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
	stagedat = { 0,0 };

	/*********************オブジェクトを生成する********************/

	//読込ファイルを開く
	fopen_s(&fp, STAGE_DATA, "r");

	//エラーチェック
	if (fp == NULL)
	{
		throw("ファイルが読み込めません\n");
	}
	else
	{
		while (true)
		{
			block = fgetc(fp);
			stagedat.STAGE_WIDTH++;
			if (block == EOF)
			{
				break;
			}
			else if (block == ',')
			{
				stagedat.STAGE_WIDTH--;
				continue;
			}
			else if (block == '\n')
			{
				stagedat.STAGE_HEIGHT++;
				stagedat.STAGE_WIDTH = 0;
				continue;
			}
			else if (block - '0' <= 0)
			{
				type = block;
				CreateObject<Stage>(Vector2D(
					stagedat.STAGE_WIDTH  * 50.0f - 435.f,
					stagedat.STAGE_HEIGHT * 50.0f - 665.f));
			}
		}	
		fclose(fp);
	}
	
	//プレイヤーを生成
	//CreateObject<Stage>(Vector2D(640.0f, 360.0f));
	Player* p =	CreateObject<Player>(Vector2D(640.0f, 360.0f));
	CreateObject<Enemy>(Vector2D(640.0f, 360.0f))->SetPlayer(p);
}

//更新処理
eSceneType Main::Update()
{
	if (Is_pause == false)
	{
		//プレイヤーがステージ外にいかない処理
		for (int i = 0; i < objects.size(); i++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[objects.size() - 1]);
		}

		//シーンに存在するオブジェクトの更新処理
		for (GameObject* obj : objects)
		{
			obj->Update();
		}

		//スタートボタンが押されたら、ポーズする
		if (InputControl::GetButtonDown(XINPUT_BUTTON_START) || InputControl::GetKeyDown(KEY_INPUT_SPACE))
		{
			Is_pause = true;
		}
	}
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
