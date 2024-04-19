#include "Stage.h"
#include"DxLib.h"

//�R���X�g���N�^
Stage::Stage()
{
	image[0] = NULL;
	image[1] = NULL;
	image[2] = NULL;
	image[3] = NULL;
}

//�f�X�g���N�^
Stage::~Stage()
{

}

//����������
void Stage::Initialize()
{
	//�摜�̓ǂݍ���
	image[0] = LoadGraph("Resource/images/XY-grid.png");
	image[1] = LoadGraph("Resource/images/back.png");
	image[2] = LoadGraph("Resource/images/room.png");
	image[3] = LoadGraph("Resource/images/road.png");

	//�G���[�`�F�b�N
	for (int i = 0; i < 4; i++)
	{
		if (image[i] == -1)
		{
			throw ("�摜������܂���\n");
		}
	}
}

//�X�V����
void Stage::Update()
{
	CreateStage();	//�X�e�[�W��������
}

//�`�揈��
void Stage::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(640, 360, 1.0, 0, image[0], TRUE, FALSE);
	DrawRotaGraphF(640, 360, 1.5, 0, image[1], TRUE, FALSE);
	DrawRotaGraphF(640, 360, 0.2, 0, image[2], TRUE, FALSE);
	DrawRotaGraphF(640, 360, 0.2, 0, image[3], TRUE, FALSE);
}

//�I��������
void Stage::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(image[0]);
	DeleteGraph(image[1]);
	DeleteGraph(image[2]);
	DeleteGraph(image[3]);
}

//�X�e�[�W��������
void Stage::CreateStage()
{
	
}
