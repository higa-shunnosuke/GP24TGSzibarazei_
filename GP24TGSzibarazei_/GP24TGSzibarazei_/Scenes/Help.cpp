#include "Help.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Help::Help() :background_image(NULL)
{

}

Help::~Help()
{

}


//����������
void Help::Initialize()
{
	//�摜�̓ǂݍ���
	background_image = LoadGraph("../Resource/images/");

	//�G���[�`�F�b�N
	if (background_image == -1)
	{
		throw("../Resource/images.Title.bmp������܂���\n");
	}
}


//�X�V����
eSceneType Help::Update()
{
	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}


//�`�揈��
void Help::Draw()const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, background_image, FALSE);

	//�Q�[������
	SetFontSize(16);
	DrawString(20, 120, "�w���v���", 0xffffff, 0);

	DrawString(150, 450, "B�{�^���������ă^�C�g���֖߂�", 0xffffff, 0);
}


//�I������
void Help::Finalize()
{
	//�ǂݍ��񂾉摜�̍폜
	DeleteGraph(background_image);
}

//���݂̃V�[�������擾
eSceneType Help::GetNowScene()const
{
	return eSceneType::E_HELP;
}