#include"DxLib.h"
#include"Utility/InputControl.h"

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

	//ローカル変数定義


	//描画先を裏画面に指定
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームメインループ（ESCキーorBACKボタンを押すと終了）
	while (ProcessMessage() != -1 && InputControl::GetExitButton() != TRUE)
	{
		//入力機能：更新処理
		InputControl::Update();

		//画面初期化処理
		ClearDrawScreen();

		//裏画面の内容を表画面に反映する
		ScreenFlip();

	}

	//DXライブラリの使用を終了する
	DxLib_End();

	//終了状態を通知
	return 0;
}