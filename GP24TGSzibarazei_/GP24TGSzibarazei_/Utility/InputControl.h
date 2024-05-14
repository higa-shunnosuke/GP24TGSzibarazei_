#pragma 

#include "Vector2D.h"

//�L�[�R�[�h�̐�
#define D_KEYCODE_MAX (256)

//���͋@�\�p�N���X
class InputControl
{
private:
	//�L�[�{�[�h����
	static char now_key[D_KEYCODE_MAX];		//���݃t���[�����͒l
	static char old_key[D_KEYCODE_MAX];		//�O�t���[�����͒l

	//�R���g���[���[����
	static bool now_button[16];  //���݃t���[�����͒l
	static bool old_button[16];  //�O�t���[�����͒l
	static float trigger[2];     //���E�g���K�[���͒l
	static Vector2D stick[2];    //���E�X�e�B�b�N���͒l

public:
	//�X�V����
	static void Update();

	//�L�[�擾(�����Ă����)
	static bool GetKey(int key_code);
	//�L�[�擾(�������u��)
	static bool GetKeyDown(int key_code);
	//�L�[�擾(�������u��)
	static bool GetKeyUp(int key_code);

	//�擾(�����Ă����)
	static bool GetButton(int button);
	//�擾(�������u��)
	static bool GetButtonDown(int button);
	//�擾(�������u��)
	static bool GetButtonUp(int button);

	//���g���K�[�擾
	static float GetLeftTrigger();
	//�E�g���K�[�擾
	static float GetRightTrigger();
	//���X�e�B�b�N�擾
	static Vector2D GetLeftStick();
	//�E�X�e�B�b�N�擾
	static Vector2D GetRightStick();
private:
	//�L�[�R�[�h�̗L���͈̓`�F�b�N
	static bool CheckKeyCodeRange(int key_code);
	//�{�^���z��͈̓`�F�b�N
	static bool CheckButtonRange(int button);
};

