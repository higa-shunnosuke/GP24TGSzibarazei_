#pragma 

#include "Vector2D.h"

//キーコードの数
#define D_KEYCODE_MAX (256)

//入力機能用クラス
class InputControl
{
private:
	//キーボード入力
	static char now_key[D_KEYCODE_MAX];		//現在フレーム入力値
	static char old_key[D_KEYCODE_MAX];		//前フレーム入力値

	//コントローラー入力
	static bool now_button[16];  //現在フレーム入力値
	static bool old_button[16];  //前フレーム入力値
	static float trigger[2];     //左右トリガー入力値
	static Vector2D stick[2];    //左右スティック入力値

public:
	//更新処理
	static void Update();

	//キー取得(押している間)
	static bool GetKey(int key_code);
	//キー取得(押した瞬間)
	static bool GetKeyDown(int key_code);
	//キー取得(離した瞬間)
	static bool GetKeyUp(int key_code);

	//取得(押している間)
	static bool GetButton(int button);
	//取得(押した瞬間)
	static bool GetButtonDown(int button);
	//取得(離した瞬間)
	static bool GetButtonUp(int button);

	//左トリガー取得
	static float GetLeftTrigger();
	//右トリガー取得
	static float GetRightTrigger();
	//左スティック取得
	static Vector2D GetLeftStick();
	//右スティック取得
	static Vector2D GetRightStick();
private:
	//キーコードの有効範囲チェック
	static bool CheckKeyCodeRange(int key_code);
	//ボタン配列範囲チェック
	static bool CheckButtonRange(int button);
};

