#include "InputControl.h"
#include "DxLib.h"

//�����o�ϐ���`
char InputControl::now_key[D_KEYCODE_MAX] = {};		//���݂̃L�[
char InputControl::old_key[D_KEYCODE_MAX] = {};		//�O�̃L�[
bool InputControl::now_button[16] = {};				//���݂̃{�^��
bool InputControl::old_button[16] = {};				//�O�̃{�^��
float InputControl::trigger[2] = {};				//�g���K�[
Vector2D InputControl::stick[2] = {};				//�X�e�B�b�N

//���͋@�\�F�X�V����
void InputControl::Update()
{
	//XIput�R���g���[���[�̓��͒l���擾����
	XINPUT_STATE input_state = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input_state);

	//�������̈���R�s�[�i�O�t���[���̓��͏��Ɍ��݂̓��͏����R�s�[�j
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	//�{�^�����͒l�̍X�V
	for (int i = 0; i < 16; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = (bool)input_state.Buttons[i];
	}

	//�g���K�[���͂̍X�V(0.0f�`1.0f�ɔ͈͂𐧌�����)
	trigger[0] = (float)input_state.LeftTrigger / (float)UCHAR_MAX;
	trigger[1] = (float)input_state.RightTrigger / (float)UCHAR_MAX;

	//���X�e�B�b�N���͒l�̍X�V(-1.0f�`1.0f�ɔ͈͂𐧌�����)
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

	//�E�X�e�B�b�N���͒l�̍X�V(-1.0f�`1.0f�ɔ͈͂𐧌�����)
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

	//���݂̓��͏��̍X�V
	GetHitKeyStateAll(now_key);
}

//�L�[�擾�F�����Ă���ԁitrue=�����Ă���,false=�����Ă��Ȃ��j
bool InputControl::GetKey(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == TRUE));
}

//�L�[�擾�F�������u�ԁitrue=�������u��,false=�������u�Ԃł͂Ȃ��j
bool InputControl::GetKeyDown(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == FALSE));
}

//�L�[�擾�F�������u�ԁitrue=�������u��,false=�������u�Ԃł͂Ȃ��j
bool InputControl::GetKeyUp(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == FALSE) &&
		(old_key[key_code] == TRUE));
}

//�{�^���擾�F�����Ă��
bool InputControl::GetButton(int button)
{
	return CheckButtonRange(button) && (now_button[button] &&
		old_button[button]);
}

//�{�^���擾�F�������u��
bool InputControl::GetButtonDown(int button)
{
	return CheckButtonRange(button) && (now_button[button] &&
		!old_button[button]);
}

//�{�^���擾�F�������u��
bool InputControl::GetButtonUp(int button)
{
	return CheckButtonRange(button) && (!now_button[button] &&
		old_button[button]);
}

//���g���K�[�擾
float InputControl::GetLeftTrigger()
{
	return trigger[0];
}

//�E�g���K�[�擾
float InputControl::GetRightTrigger()
{
	return trigger[1];
}

//���X�e�B�b�N�擾
Vector2D InputControl::GetLeftStick()
{
	return stick[0];
}

//�E�X�e�B�b�N�擾
Vector2D InputControl::GetRightStick()
{
	return stick[1];
}

//�L�[�R�[�h�͈̔̓`�F�b�N�itrue=�L��,false=�����j
bool InputControl::CheckKeyCodeRange(int key_code)
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}

//�{�^���z��͈̓`�F�b�N
bool InputControl::CheckButtonRange(int button)
{
	return(0 <= button && button < 16);
}