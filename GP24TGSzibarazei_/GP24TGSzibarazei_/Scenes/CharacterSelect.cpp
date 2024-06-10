#include "CharacterSelect.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

CharacterSelect::CharacterSelect() :background_image(NULL),
cursor_image(NULL), cursor_number(0)
{

}

CharacterSelect::~CharacterSelect()
{

}


//����������
void CharacterSelect::Initialize()
{
	////�摜�̓ǂݍ���
	//background_image = LoadGraph("../Resource/images/");
	//cursor_image = LoadGraph("../Resource/images/");

	////�G���[�`�F�b�N
	//if (background_image == -1)
	//{
	//	throw("../Resource/images/������܂���\n");
	//}
	//if (cursor_image == -1)
	//{
	//	throw("../Resource/images/������܂���\n");
	//}
}


//�X�V����
eSceneType CharacterSelect::Update()
{
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN) || InputControl::GetKeyDown(KEY_INPUT_DOWN))
	{
		cursor_number++;
		//�P�ԉ��ɓ��B������A��ԏ�ɂ���
		if (cursor_number > 3)
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
			cursor_number = 3;
		}
	}

	//�J�[�\������i���삷��L������I������j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A) || InputControl::GetKeyDown(KEY_INPUT_A))
	{
		switch (cursor_number)
		{
		case 0:
			return eSceneType::E_MAIN;

		case 1:

			break;

		case 2:

			break;

		case 3:

			break;

		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) || InputControl::GetKeyDown(KEY_INPUT_B))
	{
		return eSceneType::E_TITLE;
	}

	//���݂̃V�[���^�C�v��Ԃ�
	return GetNowScene();
}


//�`�揈��
void CharacterSelect::Draw()const
{
	//�L�����N�^�[�Z���N�g�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�J�[�\���摜�̕`��
	DrawRotaGraph(90, 220 + cursor_number * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);

	SetFontSize(50);
	DrawString(20, 20, "�L�����N�^�[�Z���N�g���", 0xffffff, 0);

	DrawString(265, 550, "A�{�^���������ăX�^�[�g", 0xffffff, 0);
	DrawString(265, 600, "B�{�^���������ă^�C�g���֖߂�", 0xffffff, 0);

}


//�I��������
void CharacterSelect::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
	DeleteGraph(cursor_image);
}


//���݂̃V�[�������擾
eSceneType CharacterSelect::GetNowScene()const
{
	return eSceneType::E_CHARACTERSELECT;
}