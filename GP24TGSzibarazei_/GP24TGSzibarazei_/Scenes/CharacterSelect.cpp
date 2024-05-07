#include "CharacterSelect.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

CharacterSelect::CharacterSelect() :background_image(NULL),
cursor_image(NULL), menu_cursor(0)
{

}

CharacterSelect::~CharacterSelect()
{

}


//����������
void CharacterSelect::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("../Resource/images/");
	cursor_image = LoadGraph("../Resource/images/");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("../Resource/images/������܂���\n");
	}
	if (cursor_image == -1)
	{
		throw("../Resource/images/������܂���\n");
	}
}


//�X�V����
eSceneType CharacterSelect::Update()
{
	//�J�[�\�����ړ�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		//�P�ԉ��ɓ��B������A��ԏ�ɂ���
		if (menu_cursor > 3)
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
			menu_cursor = 3;
		}
	}

	//�J�[�\������i���삷��L������I������j
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		switch (menu_cursor)
		{
		case 0:

			break;

		case 1:

			break;

		case 2:

			break;

		case 3:

			break;

		}
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
	DrawRotaGraph(90, 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
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