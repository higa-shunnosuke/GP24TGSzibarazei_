#pragma once
#include "../Player/Player.h"
#include"../GameObject.h"

class Stage :public GameObject
{
private:
	int type;			//�X�e�[�W�̃^�C�v
	Vector2D move;		//�ړ�����
	Player* player;

public:
	Stage();
	~Stage();

	virtual void Initialize() override;	//����������
	virtual void Update() override;		//�X�V����
	virtual void Draw() const override;	//�`�揈��
	virtual void Finalize() override;	//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object,int i) override;
	//�ʒu���擾����
	virtual Vector2D GetLocation() const override;
	//�傫���擾����
	virtual Vector2D Getscale() const override;
	//�ʒu���ύX����
	virtual void SetLocation(const Vector2D& location) override;

	static int GetStage(int i,int j);
	static void SetStage();

private:
};

