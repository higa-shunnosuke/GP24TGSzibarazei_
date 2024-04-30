#pragma once

//�I�u�W�F�N�g�̍��W
struct Location
{
	float x;
	float y;
};

//�I�u�W�F�N�g�̃T�C�Y
struct Scale
{
	float x;
	float y;
};

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Location location;	//�ʒu���
	Scale scale;		//�傫��
	double radian;		//����
	int image;			//�`�悷��摜
	int sound;			//�Đ����鉹��

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();	//����������
	virtual void Update();		//�X�V����
	virtual void Draw() const;	//�`�揈��
	virtual void Finalize();	//�I��������

	//�q�b�g�`�F�b�N
	bool HitCheck(const class GameObject* GemeObject)const;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);
	//�ʒu���擾����
	virtual Location GetLocation() const;
	//�傫���擾����
	virtual Scale Getscale() const;
	//�ʒu���ύX����
	virtual void SetLocation(const Location& location);


};

