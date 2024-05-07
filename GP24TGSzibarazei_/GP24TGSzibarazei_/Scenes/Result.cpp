#include "Result.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Result::Result() :back_ground(NULL), score(0)
{

}

Result::~Result()
{

}


//����������
void Result::Initialize()
{
	//�摜�̓ǂݍ���
	back_ground = LoadGraph("../Resource/images/");

	//�G���[�`�F�b�N
	if (back_ground == -1)
	{
		throw("../Resource/images/������܂���\n");
	}
	
	//�Q�[�����ʂ̓ǂݍ���
	ReadResultData();
}


//�X�V����
eSceneType Result::Update()
{
	//A�{�^���Ń^�C�g���ɑJ�ڂ���
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}


//�`�揈��
void Result::Draw()const
{
	//�w�i�摜��`��
	DrawGraph(0, 0, back_ground, TRUE);

	//�X�R�A���\���̈�
	DrawBox(150, 150, 490, 330, GetColor(0, 153, 0), TRUE);
	DrawBox(150, 150, 490, 330, GetColor(0, 0, 0), FALSE);

	DrawBox(500, 0, 640, 480, GetColor(0, 153, 0), TRUE);

	SetFontSize(20);
	DrawString(220, 170, "�Q�[���I�[�o�[", GetColor(204, 0, 0));
	
}


//�I��������
void Result::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(back_ground);
	
}


//���݂̃V�[�������擾
eSceneType Result::GetNowScene()const
{
	return eSceneType::E_RESULT;
}

//���U���g�f�[�^�̓ǂݍ���
void Result::ReadResultData()
{
	//�t�@�C���I�[�v��
	FILE* fp = nullptr;
	errno_t result = fopen_s(&fp, "../Resource/dat/", "r");

	//�G���[�`�F�b�N
	if (result != 0)
	{
		throw("../Resource/dat/���ǂݍ��߂܂���\n");
	}

	//���ʂ�ǂݍ���
	fscanf_s(fp, "%d,\n", &score);

	//�t�@�C���N���[�Y
	fclose(fp);
}
