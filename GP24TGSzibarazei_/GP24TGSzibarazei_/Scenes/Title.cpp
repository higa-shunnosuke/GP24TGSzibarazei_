#include "Title.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Title::Title() :background_image(NULL), 
cursor_number(0)
{

}

Title::~Title()
{
	
}


//����������
void Title::Initialize()
{
	
}


//�X�V����
eSceneType Title::Update()
{
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) || InputControl::GetKeyDown(KEY_INPUT_DOWN))
	{
		cursor_number++;
		//�P�ԉ��ɓ��B������A��ԏ�ɂ���
		if (cursor_number > 2)
		{
			cursor_number = 0;
		}
	}


	//�J�[�\����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP) || InputControl::GetKeyDown(KEY_INPUT_UP))
	{
		cursor_number--;
		//�P�ԏ�ɓ��B������A��ԉ��ɂ���
		if (cursor_number < 0)
		{
			cursor_number = 2;
		}
	}

	//�J�[�\������i���肵����ʂɑJ�ڂ���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A) || InputControl::GetKeyDown(KEY_INPUT_A))
	{
		switch (cursor_number)
		{
		case 0:
			return eSceneType::E_CHARACTERSELECT;

		case 1:
			return eSceneType::E_HELP;

		case 2:
			return eSceneType::E_END;
		}
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}


//�`�揈��
void Title::Draw()const
{
	//�^�C�g���摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�J�[�\���摜�̕`��

	//�^�C�g���\��
	SetFontSize(100);
	DrawString(290, 160, "IMMORTAL QUEST", 0xffffff, 0);
	
	//���j���[�\��
	SetFontSize(50);

	switch (cursor_number)
	{
	case 0:
		DrawString(540, 400, "�X�^�[�g", 0x00ff00);
		DrawString(560, 450, "�w���v", 0xffffff);
		DrawString(560, 500, "�G���h", 0xffffff);
		break;
	case 1:
		DrawString(540, 400, "�X�^�[�g", 0xffffff);
		DrawString(560, 450, "�w���v", 0x00ff00);
		DrawString(560, 500, "�G���h", 0xffffff);
		break;
	default:
		DrawString(540, 400, "�X�^�[�g", 0xffffff);
		DrawString(560, 450, "�w���v", 0xffffff);
		DrawString(560, 500, "�G���h", 0x00ff00);
		break;
	}
	DrawTriangle(500, 410 + (cursor_number * 50), 500, 440 + (cursor_number * 50), 540, 425 + (cursor_number * 50), 0x00ff00, TRUE);
}


//�I��������
void Title::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);

}


//���݂̃V�[�������擾
eSceneType Title::GetNowScene()const
{
	return eSceneType::E_TITLE;
}