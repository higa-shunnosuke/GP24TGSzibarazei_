#pragma once


//�X�e�[�W�p�N���X
class Stage
{
private:
	int image[4];		//�摜
	int stage[];		//�X�e�[�W

public:
	Stage();
	~Stage();

	virtual void Initialize();	//����������
	virtual void Update();		//�X�V����
	virtual void Draw() const;	//�`�揈��
	virtual void Finalize();	//�I��������

private:
	void CreateStage();			//�X�e�[�W����
};

