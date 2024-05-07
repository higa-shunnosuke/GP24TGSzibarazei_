#include "Title.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Title::Title() :background_image(NULL), menu_image(NULL), 
cursor_image(NULL), menu_cursor(0)
{

}

Title::~Title()
{
	
}


//����������
void Title::Initialize()
{
	////�摜�̓ǂݍ���
	//background_image = LoadGraph("../Resource/images/");
	//menu_image = LoadGraph("../Resource/images/");
	//cursor_image = LoadGraph("../Resource/images/");

	////�G���[�`�F�b�N
	//if (background_image == -1)
	//{
	//	throw("../Resource/images/������܂���\n");
	//}
	//if (menu_image == -1)
	//{
	//	throw("../Resource/images/������܂���\n");
	//}
	//if (cursor_image == -1)
	//{
	//	throw("../Resource/images/������܂���\n");
	//}
}


//�X�V����
eSceneType Title::Update()
{
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//�P�ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 2)
		{
			menu_cursor = 0;
		}
	}


	//�J�[�\����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		//�P�ԏ�ɓ��B������A��ԉ��ɂ���
		if (menu_cursor < 0)
		{
			menu_cursor = 2;
		}
	}

	//�J�[�\������i���肵����ʂɑJ�ڂ���j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
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
	//�J�[�\���摜�̕`��
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}


//�I��������
void Title::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}


//���݂̃V�[�������擾
eSceneType Title::GetNowScene()const
{
	return eSceneType::E_TITLE;
}