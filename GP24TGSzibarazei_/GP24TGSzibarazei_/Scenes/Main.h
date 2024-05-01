#pragma once

#include"vector"
#include"string"
#include"../Objects/GameObject.h"

class Main
{
private:
	std::vector<GameObject*> objects;

public:
	Main();
	~Main();

	//����������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw() const;
	//�I��������
	void Finalize();

private:
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
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

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

