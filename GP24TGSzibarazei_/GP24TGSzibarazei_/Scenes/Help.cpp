#include "Help.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Help::Help() :background_image(NULL)
{

}

Help::~Help()
{

}


//初期化処理
void Help::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("../Resource/images/");

	//エラーチェック
	if (background_image == -1)
	{
		throw("../Resource/images.Title.bmpがありません\n");
	}
}


//更新処理
eSceneType Help::Update()
{
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}


//描画処理
void Help::Draw()const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//ゲーム説明
	SetFontSize(16);
	DrawString(20, 120, "ヘルプ画面", 0xffffff, 0);

	DrawString(150, 450, "Bボタンを押してタイトルへ戻る", 0xffffff, 0);
}


//終了処理
void Help::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
}

//現在のシーン情報を取得
eSceneType Help::GetNowScene()const
{
	return eSceneType::E_HELP;
}