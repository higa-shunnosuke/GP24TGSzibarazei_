#include "Result.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Result::Result() :back_ground(NULL), score(0)
{

}

Result::~Result()
{

}


//初期化処理
void Result::Initialize()
{
	//画像の読み込み
	back_ground = LoadGraph("../Resource/images/");

	//エラーチェック
	if (back_ground == -1)
	{
		throw("../Resource/images/がありません\n");
	}
	
	//ゲーム結果の読み込み
	ReadResultData();
}


//更新処理
eSceneType Result::Update()
{
	//Aボタンでタイトルに遷移する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}


//描画処理
void Result::Draw()const
{
	//背景画像を描画
	DrawGraph(0, 0, back_ground, TRUE);

	//スコア等表示領域
	DrawBox(150, 150, 490, 330, GetColor(0, 153, 0), TRUE);
	DrawBox(150, 150, 490, 330, GetColor(0, 0, 0), FALSE);

	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);

	SetFontSize(20);
	DrawString(220, 170, "ゲームオーバー", GetColor(204, 0, 0));
	
}


//終了時処理
void Result::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(back_ground);
	
}


//現在のシーン情報を取得
eSceneType Result::GetNowScene()const
{
	return eSceneType::E_RESULT;
}

//リザルトデータの読み込み
void Result::ReadResultData()
{
	//ファイルオープン
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "../Resource/dat/", "r");

	//エラーチェック
	if (result != 0)
	{
		throw("../Resource/dat/が読み込めません\n");
	}

	//結果を読み込む
	fscanf_s(fp, "%d,\n", &score);

	//ファイルクローズ
	fclose(fp);
}
