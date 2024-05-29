#pragma once

#include "SceneBase.h"
#include"vector"
#include"string"
#include"../Objects/GameObject.h"

//�X�e�[�W�̑傫��
typedef struct
{
	int STAGE_WIDTH;	//�X�e�[�W�̉���
	int STAGE_HEIGHT;	//�X�e�[�W�̏c��
}StageDat;

class Main:public SceneBase
{
private:
	bool Is_pause;		//�|�[�Y��Ԃ��H

public:
	Main();
	~Main();

	//����������
	virtual void Initialize() override;
	//�X�V����
	virtual eSceneType Update() override;
	//�`�揈��
	virtual void Draw() const override;
	//�I��������
	virtual void Finalize() override;
	//���݂̃V�[�����擾
	virtual eSceneType GetNowScene() const override;
	//�X�e�[�W�̑傫�����擾
	static StageDat GetStageSiz();
	//�X�e�[�W�̃^�C�v���擾
	static int GetStageType();


private:
	//�����蔻��`�F�b�N����(�q�b�g��)
	void HitCheckObject(GameObject* a, GameObject* b);
};

