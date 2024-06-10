#include "CharacterSelect.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

CharacterSelect::CharacterSelect() :background_image(NULL),
cursor_image(NULL), cursor_number(0)
{

}

CharacterSelect::~CharacterSelect()
{

}


//初期化処理
void CharacterSelect::Initialize()
{
	////画像の読み込み
	//background_image = LoadGraph("../Resource/images/");
	//cursor_image = LoadGraph("../Resource/images/");

	////エラーチェック
	//if (background_image == -1)
	//{
	//	throw("../Resource/images/がありません\n");
	//}
	//if (cursor_image == -1)
	//{
	//	throw("../Resource/images/がありません\n");
	//}
}


//更新処理
eSceneType CharacterSelect::Update()
{
	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) || InputControl::GetKeyDown(KEY_INPUT_DOWN))
	{
		cursor_number++;
		//１番下に到達したら、一番上にする
		if (cursor_number > 3)
		{
			cursor_number = 0;
		}
	}


	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP) || InputControl::GetKeyDown(KEY_INPUT_UP))
	{
		cursor_number--;
		//１番上に到達したら、一番下にする
		if (cursor_number < 0)
		{
			cursor_number = 3;
		}
	}

	//カーソル決定（操作するキャラを選択する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A) || InputControl::GetKeyDown(KEY_INPUT_A))
	{
		switch (cursor_number)
		{
		case 0:
			return eSceneType::E_MAIN;

		case 1:

			break;

		case 2:

			break;

		case 3:

			break;

		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) || InputControl::GetKeyDown(KEY_INPUT_B))
	{
		return eSceneType::E_TITLE;
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}


//描画処理
void CharacterSelect::Draw()const
{
	//キャラクターセレクト画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//カーソル画像の描画
	DrawRotaGraph(90, 220 + cursor_number * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);

	SetFontSize(50);
	DrawString(20, 20, "キャラクターセレクト画面", 0xffffff, 0);

	DrawString(265, 550, "Aボタンを押してスタート", 0xffffff, 0);
	DrawString(265, 600, "Bボタンを押してタイトルへ戻る", 0xffffff, 0);

}


//終了時処理
void CharacterSelect::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(cursor_image);
}


//現在のシーン情報を取得
eSceneType CharacterSelect::GetNowScene()const
{
	return eSceneType::E_CHARACTERSELECT;
}