#include "Main.h"

#include "../Objects/Player/Player.h"
#include "../Objects/Stage/Stage.h"

//�R���X�g���N�^
Main::Main() :objects()
{}

//�f�X�g���N�^
Main::~Main()
{
	//�Y��h�~
	Finalize();
}

//����������
void Main::Initialize()
{
	//�v���C���[�𐶐�����
	CreateObject<Stage>(Vector2D(640.0f, 360.0f));
	CreateObject<Player>(Vector2D(640.0f, 360.0f));
}

//�X�V����
void Main::Update()
{
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}
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

