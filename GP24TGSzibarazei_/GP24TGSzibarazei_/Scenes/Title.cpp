#include "Title.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Title::Title() :background_image(NULL), menu_image(NULL), 
cursor_image(NULL), menu_cursor(0)
{

}

Title::~Title()
{
	
}


//初期化処理
void Title::Initialize()
{
	////画像の読み込み
	//background_image = LoadGraph("../Resource/images/");
	//menu_image = LoadGraph("../Resource/images/");
	//cursor_image = LoadGraph("../Resource/images/");

	////エラーチェック
	//if (background_image == -1)
	//{
	//	throw("../Resource/images/がありません\n");
	//}
	//if (menu_image == -1)
	//{
	//	throw("../Resource/images/がありません\n");
	//}
	//if (cursor_image == -1)
	//{
	//	throw("../Resource/images/がありません\n");
	//}
}


//更新処理
eSceneType Title::Update()
{
	//カーソル下移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//１番下に到達したら、一番上にする
		if (menu_cursor > 2)
		{
			menu_cursor = 0;
		}
	}


	//カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//１番上に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 2;
		}
	}

	//カーソル決定（決定した画面に遷移する）
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
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
	//カーソル画像の描画
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}


//終了時処理
void Title::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}


//現在のシーン情報を取得
eSceneType Title::GetNowScene()const
{
	return eSceneType::E_TITLE;
}