#include"DxLib.h"
#include"Utility/InputControl.h"
#include"Scenes/Scene.h"

#define D_SCREEN_WIDTH (1280)
#define D_SCREEN_HEIGHT (720)

//��������v���O�������J�n����
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmbLine, _In_ int nShowCmb)
{
	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//��ʃT�C�Y�̐ݒ�
	SetGraphMode(D_SCREEN_WIDTH, D_SCREEN_HEIGHT, 32);

	//DX���C�u�����̏�����
	if (DxLib_Init() == -1)
	{
		return -1;	//�G���[����
	}

	// �w�i�F�𓧉߂�����
	SetTransColor(255, 255, 255);

	//���[�J���ϐ���`
	Scene* scene = new Scene();		//�V�[�����


	//�`���𗠉�ʂɎw��
	SetDrawScreen(DX_SCREEN_BACK);

	//������
	scene->Initialize();

	//�Q�[�����C�����[�v�iESC�L�[orBACK�{�^���������ƏI���j
	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
	{
	
		//���͋@�\�F�X�V����
		InputControl::Update();

		//�X�V����
		scene->Update();

		//��ʏ���������
		ClearDrawScreen();

		//�`�揈��
		scene->Draw();

		//����ʂ̓��e��\��ʂɔ��f����
		ScreenFlip();
	}

	//�����폜����
	if (scene != nullptr)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}

	//DX���C�u�����̎g�p���I������
	DxLib_End();

	//�I����Ԃ�ʒm
	return 0;
}