#include "Clear.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Clear::Clear() :background_image(NULL)
{

}

Clear::~Clear()
{

}


//初期化処理
void Clear::Initialize()
{
	////画像の読み込み
	//background_image = LoadGraph("../Resource/images/");

	////エラーチェック
	//if (background_image == -1)
	//{
	//	throw("../Resource/images.がありません\n");
	//}
}


//更新処理
eSceneType Clear::Update()
{
	//Aボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}


//描画処理
void Clear::Draw()const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//ゲーム説明
	SetFontSize(16);
	DrawString(20, 120, "クリア画面", 0xffffff, 0);

	DrawString(150, 450, "Aボタンを押してタイトルへ戻る", 0xffffff, 0);
}


//終了処理
void Clear::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
}

//現在のシーン情報を取得
eSceneType Clear::GetNowScene()const
{
	return eSceneType::E_CLEAR;
}