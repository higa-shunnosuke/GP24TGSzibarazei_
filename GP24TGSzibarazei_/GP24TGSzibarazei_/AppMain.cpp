#include"DxLib.h"
#include"Utility/InputControl.h"
#include"Scenes/Scene.h"

#define D_SCREEN_WIDTH (1280)
#define D_SCREEN_HEIGHT (720)

//ここからプログラムを開始する
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmbLine, _In_ int nShowCmb)
{
	//ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	//画面サイズの設定
	SetGraphMode(D_SCREEN_WIDTH, D_SCREEN_HEIGHT, 32);

	//DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		return -1;	//エラー発生
	}

	// 背景色を透過させる
	SetTransColor(255, 255, 255);

	//ローカル変数定義
	Scene* scene = new Scene();		//シーン情報


	//描画先を裏画面に指定
	SetDrawScreen(DX_SCREEN_BACK);

	//初期化
	scene->Initialize();

	//ゲームメインループ（ESCキーorBACKボタンを押すと終了）
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
	{
	
		//入力機能：更新処理
		InputControl::Update();

		//更新処理
		scene->Update();

		//画面初期化処理
		ClearDrawScreen();

		//描画処理
		scene->Draw();

		//裏画面の内容を表画面に反映する
		ScreenFlip();
	}

	//情報を削除する
	if (scene != nullptr)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}

	//DXライブラリの使用を終了する
	DxLib_End();

	//終了状態を通知
	return 0;
}