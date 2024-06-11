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
	
}


//�X�V����
eSceneType Help::Update()
{
	//B�{�^���������ꂽ��A�^�C�g���ɖ߂�
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) || InputControl::GetKeyDown(KEY_INPUT_B))
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
	SetFontSize(50);
	DrawString(20, 20, "�w���v���", 0xffffff, 0);

	DrawString(265, 550, "B�{�^���������ă^�C�g���֖߂�", 0xffffff, 0);
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