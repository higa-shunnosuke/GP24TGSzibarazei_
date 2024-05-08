#include "Main.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Stage/Stage.h"
#include"DxLib.h"

#define STAGE_WIDTH		(21)
#define STAGE_HEIGHT	(21)
#define STAGE_DATA		("Resource/datas/stage.csv")

Stage* stage[STAGE_HEIGHT][STAGE_WIDTH];

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
	FILE* fp = NULL;
	 
	int block = 0;

	/*********************�I�u�W�F�N�g�𐶐�����********************/
	
	//�Ǎ��t�@�C�����J��
	OutputDebugString("�t�@�C����ǂݍ��݂܂�");
	fopen_s(&fp, STAGE_DATA, "r");

	//�G���[�`�F�b�N
	if (fp == NULL)
	{
		OutputDebugString("�t�@�C����ǂݍ��߂܂���");
	}
	else
	{
		/*while (true)
		{
			if (fgetc(fp) == EOF)
			{
				break;
			}

			CreateObject<Stage>(Vector2D(50.0f, 50.0f));
		}*/

		fclose(fp);
	}
	


	//�v���C���[�𐶐�
	CreateObject<Stage>(Vector2D(640.0f, 360.0f));
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
