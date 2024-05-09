#include "Main.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Stage/Stage.h"
#include"DxLib.h"

#define STAGE_DATA		("Resource/datas/stage.csv")


FILE* fp = NULL;
int block = 0;
int STAGE_WIDTH;
int STAGE_HEIGHT;

//�R���X�g���N�^
Main::Main() :objects()
{

}

//�f�X�g���N�^
Main::~Main()
{
	//�Y��h�~
	Finalize();
}

//����������
void Main::Initialize()
{
	STAGE_WIDTH = 0;
	STAGE_HEIGHT = 0;

	/*********************�I�u�W�F�N�g�𐶐�����********************/

	//�Ǎ��t�@�C�����J��
	fopen_s(&fp, STAGE_DATA, "r");

	//�G���[�`�F�b�N
	if (fp == NULL)
	{

	}
	else
	{
		while (true)
		{
			block = fgetc(fp);
			STAGE_WIDTH++;
			if (block == EOF)
			{
				break;
			}
			else if (block == ',')
			{
				STAGE_WIDTH--;
				continue;
			}
			else if (block == '\n')
			{
				STAGE_HEIGHT++;
				STAGE_WIDTH = 0;
				continue;
			}
			else if (block > 48)
			{
				CreateObject<Stage>(Vector2D(STAGE_WIDTH * 50.0f, STAGE_HEIGHT * 50.0f));
			}
		}	

		fclose(fp);
	}

	
	//�v���C���[�𐶐�
	CreateObject<Player>(Vector2D(640.0f, 360.0f));

}

//�X�V����
eSceneType Main::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	return GetNowScene();

}

//�`�揈��
void Main::Draw() const
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Main::Finalize()
{
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();
}

//���݂̃V�[�������擾
eSceneType Main::GetNowScene()const
{
	return eSceneType::E_MAIN;
}
