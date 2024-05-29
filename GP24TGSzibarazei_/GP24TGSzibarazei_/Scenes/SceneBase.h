#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

//�V�[�����
enum eSceneType
{
	E_TITLE,
	E_HELP,
	E_CHARACTERSELECT,
	E_MAIN,
	E_CLEAR,
	E_RESULT,
	E_END
};

//���V�[���N���X
class SceneBase
{
protected:
	std::vector<GameObject*> objects;

public:
	SceneBase() {}
	virtual ~SceneBase() {}

	//����������
	virtual void Initialize() {}
	//�X�V����
	virtual eSceneType Update()
	{
		return GetNowScene();
	}
	//�`�揈��
	virtual void Draw() const {}
	//�I��������
	virtual void Finalize() {}

	//���݂̃V�[�������擾
	virtual eSceneType GetNowScene() const = 0;

	//�I�u�W�F�N�g��������
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//
		T* new_instance = new T();
		//�w�肵���N���X�𐶐�����
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
			exit(-1);
			return nullptr;
		}

		//�V�[���̏���ݒ�
		new_object->SetSceneBase(this);

		//����������
		new_object->Initialize();
		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};