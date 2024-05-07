#include "Clear.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Clear::Clear() :background_image(NULL)
{

}

Clear::~Clear()
{

}


//����������
void Clear::Initialize()
{
	////�摜�̓ǂݍ���
	//background_image = LoadGraph("../Resource/images/");

	////�G���[�`�F�b�N
	//if (background_image == -1)
	//{
	//	throw("../Resource/images.������܂���\n");
	//}
}


//�X�V����
eSceneType Clear::Update()
{
	//A�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}


//�`�揈��
void Clear::Draw()const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�Q�[������
	SetFontSize(16);
	DrawString(20, 120, "�N���A���", 0xffffff, 0);

	DrawString(150, 450, "A�{�^���������ă^�C�g���֖߂�", 0xffffff, 0);
}


//�I������
void Clear::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
}

//���݂̃V�[�������擾
eSceneType Clear::GetNowScene()const
{
	return eSceneType::E_CLEAR;
}