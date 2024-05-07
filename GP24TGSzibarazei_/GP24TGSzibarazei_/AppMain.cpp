#include"DxLib.h"
#include"Utility/InputControl.h"
#include "Scenes/SceneManager.h"
#include "Scenes/Main.h"

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
	Main* scene = new Main();		//シーン情報


	//描画先を裏画面に指定
	SetDrawScreen(DX_SCREEN_BACK);

	//初期化
	scene->Initialize();

	//ゲームメインループ（ESCキーorBACKボタンを押すと終了）
	while (ProcessMessage() != -1 
		&& CheckHitKey(KEY_INPUT_ESCAPE) != TRUE 
		&& InputControl::GetButton(XINPUT_BUTTON_BACK) != TRUE)
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

	////例外処理（異常が発生したら、catch分に飛びます）
	//try
	//{
	//	//シーンマネージャー機能の生成

	//	SceneManager manager;

	//	//シーンマネージャー機能の更新処理
	//	manager.Initialize();

	//	//シーンマネージャー機能の更新処理
	//	manager.Update();

	//	//シーンマネージャー機能の終了時処理
	//	manager.Finalize();
	//}
	//catch (const char* err_log)
	//{
	//	//エラー発生内容の出力
	//	OutputDebugString(err_log);

	//	//エラー終了を通知
	//	return -1;
	//}

	////正常終了を通知
	//return 0;
}