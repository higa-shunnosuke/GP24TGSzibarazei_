#include "Stage.h"
#include"DxLib.h"

//コンストラクタ
Stage::Stage()
{
	image[0] = NULL;
	image[1] = NULL;
	image[2] = NULL;
	image[3] = NULL;
}

//デストラクタ
Stage::~Stage()
{

}

//初期化処理
void Stage::Initialize()
{
	//画像の読み込み
	image[0] = LoadGraph("Resource/images/XY-grid.png");
	image[1] = LoadGraph("Resource/images/back.png");
	image[2] = LoadGraph("Resource/images/room.png");
	image[3] = LoadGraph("Resource/images/road.png");

	//エラーチェック
	for (int i = 0; i < 4; i++)
	{
		if (image[i] == -1)
		{
			throw ("画像がありません\n");
		}
	}
}

//更新処理
void Stage::Update()
{
	CreateStage();	//ステージ生成処理
}

//描画処理
void Stage::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(640, 360, 1.0, 0, image[0], TRUE, FALSE);
	DrawRotaGraphF(640, 360, 1.5, 0, image[1], TRUE, FALSE);
	DrawRotaGraphF(640, 360, 0.2, 0, image[2], TRUE, FALSE);
	DrawRotaGraphF(640, 360, 0.2, 0, image[3], TRUE, FALSE);
}

//終了時処理
void Stage::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(image[0]);
	DeleteGraph(image[1]);
	DeleteGraph(image[2]);
	DeleteGraph(image[3]);
}

//ステージ生成処理
void Stage::CreateStage()
{
	
}
