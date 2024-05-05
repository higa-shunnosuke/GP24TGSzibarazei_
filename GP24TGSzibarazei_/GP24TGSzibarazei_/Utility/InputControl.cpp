#include "InputControl.h"
#include "DxLib.h"

//メンバ変数定義
char InputControl::now_key[D_KEYCODE_MAX] = {};		//現在のキー
char InputControl::old_key[D_KEYCODE_MAX] = {};		//前のキー
bool InputControl::now_button[16] = {};				//現在のボタン
bool InputControl::old_button[16] = {};				//前のボタン
float InputControl::trigger[2] = {};				//トリガー
Vector2D InputControl::stick[2] = {};				//スティック

//入力機能：更新処理
void InputControl::Update()
{
	//XIputコントローラーの入力値を取得する
	XINPUT_STATE input_state = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input_state);

	//メモリ領域をコピー（前フレームの入力情報に現在の入力情報をコピー）
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	//ボタン入力値の更新
	for (int i = 0; i < 16; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = (bool)input_state.Buttons[i];
	}

	//トリガー入力の更新(0.0f～1.0fに範囲を制限する)
	trigger[0] = (float)input_state.LeftTrigger / (float)UCHAR_MAX;
	trigger[1] = (float)input_state.RightTrigger / (float)UCHAR_MAX;

	//左スティック入力値の更新(-1.0f～1.0fに範囲を制限する)
	if (input_state.ThumbLX > 0.0f)
	{
		stick[0].x = (float)input_state.ThumbLX / (float)SHRT_MAX;
	}
	else
	{
		stick[0].x = -((float)input_state.ThumbLX / (float)SHRT_MIN);
	}
	if (input_state.ThumbLY > 0.0f)
	{
		stick[0].y = (float)input_state.ThumbLY / (float)SHRT_MAX;
	}
	else
	{
		stick[0].y = (float)input_state.ThumbLY / (float)SHRT_MIN;
	}

	//右スティック入力値の更新(-1.0f～1.0fに範囲を制限する)
	if (input_state.ThumbRX > 0.0f)
	{
		stick[1].x = (float)input_state.ThumbRX / (float)SHRT_MAX;
	}
	else
	{
		stick[1].x = -((float)input_state.ThumbRX / (float)SHRT_MIN);
	}
	if (input_state.ThumbRY > 0.0f)
	{
		stick[1].y = (float)input_state.ThumbRY / (float)SHRT_MAX;
	}
	else
	{
		stick[1].y = (float)input_state.ThumbRY / (float)SHRT_MIN;
	}

	//現在の入力情報の更新
	GetHitKeyStateAll(now_key);
}

//キー取得：押している間（true=押している,false=押していない）
bool InputControl::GetKey(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == TRUE));
}

//キー取得：押した瞬間（true=押した瞬間,false=押した瞬間ではない）
bool InputControl::GetKeyDown(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == FALSE));
}

//キー取得：離した瞬間（true=離した瞬間,false=離した瞬間ではない）
bool InputControl::GetKeyUp(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == FALSE) &&
		(old_key[key_code] == TRUE));
}

//ボタン取得：押してる間
bool InputControl::GetButton(int button)
{
	return CheckButtonRange(button) && (now_button[button] &&
		old_button[button]);
}

//ボタン取得：押した瞬間
bool InputControl::GetButtonDown(int button)
{
	return CheckButtonRange(button) && (now_button[button] &&
		!old_button[button]);
}

//ボタン取得：離した瞬間
bool InputControl::GetButtonUp(int button)
{
	return CheckButtonRange(button) && (!now_button[button] &&
		old_button[button]);
}

//左トリガー取得
float InputControl::GetLeftTrigger()
{
	return trigger[0];
}

//右トリガー取得
float InputControl::GetRightTrigger()
{
	return trigger[1];
}

//左スティック取得
Vector2D InputControl::GetLeftStick()
{
	return stick[0];
}

//右スティック取得
Vector2D InputControl::GetRightStick()
{
	return stick[1];
}

//キーコードの範囲チェック（true=有効,false=無効）
bool InputControl::CheckKeyCodeRange(int key_code)
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}

//ボタン配列範囲チェック
bool InputControl::CheckButtonRange(int button)
{
	return(0 <= button && button < 16);
}