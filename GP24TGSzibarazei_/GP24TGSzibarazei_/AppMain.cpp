#include"DxLib.h"
#include"Utility/InputControl.h"


//��������v���O�������J�n����
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmbLine, _In_ int nShowCmb)
{
	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		return -1;	//�G���[����
	}

	//���[�J���ϐ���`


	//�`���𗠉�ʂɎw��
	SetDrawScreen(DX_SCREEN_BACK);

	//�Q�[�����C�����[�v�iESC�L�[orBACK�{�^���������ƏI���j
	while (ProcessMessage() != -1 && InputControl::GetExitButton() != TRUE)
	{
		//���͋@�\�F�X�V����
		InputControl::Update();

		//��ʏ���������
		ClearDrawScreen();

		//����ʂ̓��e��\��ʂɔ��f����
		ScreenFlip();

	}

	//DX���C�u�����̎g�p���I������
	DxLib_End();

	//�I����Ԃ�ʒm
	return 0;
}