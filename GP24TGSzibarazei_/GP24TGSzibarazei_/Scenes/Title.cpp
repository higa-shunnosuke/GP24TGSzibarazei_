#include "Title.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Title::Title() :background_image(NULL), 
cursor_number(0)
{

}

Title::~Title()
{
	
}


//初期化処理
void Title::Initialize()
{
	
}


//更新処理
eSceneType Title::Update()
{
	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) || InputControl::GetKeyDown(KEY_INPUT_DOWN))
	{
		cursor_number++;
		//１番下に到達したら、一番上にする
		if (cursor_number > 2)
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
			cursor_number = 2;
		}
	}

	//カーソル決定（決定した画面に遷移する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A) || InputControl::GetKeyDown(KEY_INPUT_A))
	{
		switch (cursor_number)
		{
		case 0:
			return eSceneType::E_CHARACTERSELECT;

		case 1:
			return eSceneType::E_HELP;

		case 2:
			return eSceneType::E_END;
		}
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}


//描画処理
void Title::Draw()const
{
	//タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//カーソル画像の描画

	//タイトル表示
	SetFontSize(100);
	DrawString(290, 160, "IMMORTAL QUEST", 0xffffff, 0);
	
	//メニュー表示
	SetFontSize(50);

	switch (cursor_number)
	{
	case 0:
		DrawString(540, 400, "スタート", 0x00ff00);
		DrawString(560, 450, "ヘルプ", 0xffffff);
		DrawString(560, 500, "エンド", 0xffffff);
		break;
	case 1:
		DrawString(540, 400, "スタート", 0xffffff);
		DrawString(560, 450, "ヘルプ", 0x00ff00);
		DrawString(560, 500, "エンド", 0xffffff);
		break;
	default:
		DrawString(540, 400, "スタート", 0xffffff);
		DrawString(560, 450, "ヘルプ", 0xffffff);
		DrawString(560, 500, "エンド", 0x00ff00);
		break;
	}
	DrawTriangle(500, 410 + (cursor_number * 50), 500, 440 + (cursor_number * 50), 540, 425 + (cursor_number * 50), 0x00ff00, TRUE);
}


//終了時処理
void Title::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);

}


//現在のシーン情報を取得
eSceneType Title::GetNowScene()const
{
	return eSceneType::E_TITLE;
}