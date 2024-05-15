#include "Main.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Stage/Stage.h"
#include"DxLib.h"

#define STAGE_DATA	("Resource/datas/stage.csv")
#define D_PIBOT_CENTER


StageDat stagedat;
FILE* fp = NULL;
int block = 0;
int type;

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
	stagedat = { 0,0 };

	/*********************�I�u�W�F�N�g�𐶐�����********************/

	//�Ǎ��t�@�C�����J��
	fopen_s(&fp, STAGE_DATA, "r");

	//�G���[�`�F�b�N
	if (fp == NULL)
	{
		throw("�t�@�C�����ǂݍ��߂܂���\n");
	}
	else
	{
		while (true)
		{
			block = fgetc(fp);
			stagedat.STAGE_WIDTH++;
			if (block == EOF)
			{
				break;
			}
			else if (block == ',')
			{
				stagedat.STAGE_WIDTH--;
				continue;
			}
			else if (block == '\n')
			{
				stagedat.STAGE_HEIGHT++;
				stagedat.STAGE_WIDTH = 0;
				continue;
			}
			else if (block - 48 <= 0)
			{
				type = block;
				CreateObject<Stage>(Vector2D(
					stagedat.STAGE_WIDTH  * 50.0f - 435.f,
					stagedat.STAGE_HEIGHT * 50.0f - 665.f));
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

	//�v���C���[���X�e�[�W�O�ɂ����Ȃ�����
	for (int i = 0; i < objects.size(); i++)
	{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[objects.size() - 1]);
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

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			DrawFormatString(j * 20+10, i * 20+50, 0xffff00, "%d", Stage::GetStage(i,j));
		}
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

//�X�e�[�W�̑傫�����擾
StageDat Main::GetStageSiz()
{
	return stagedat;
}

//�X�e�[�W�̃^�C�v���擾
int Main::GetStageType()
{
	return type;
}

#ifdef D_PIBOT_CENTER

//�����蔻��`�F�b�N�����i��`�̒��S�œ����蔻����Ƃ�j
void Main::HitCheckObject(GameObject* a, GameObject* b)
{
	//�Q�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//�Q�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#else
//�����蔻��`�F�b�N�����i���㒸�_�̍��W���瓖���蔻��v�Z���s���j
void Main::HitCheckObject(GameObject* a, GameObject* b)
{
	//���E���_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif //D_PIVOT_CENTER
