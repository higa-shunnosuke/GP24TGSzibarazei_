#include"Enemy.h"
#include"DxLib.h"
#include"../Player/Player.h"
#include<math.h>
#include"../../Scenes/SceneBase.h"
#include"Enemy_Attack.h"

Enemy_Attack* EA;
static int type;

Enemy::Enemy() :animation_count(0),ATK (10),Speed(1),AS(15.0),HP(10),AL(80),ET(0),isBoss(false)
{
	for (int i = 0; i < 20; i++) {
		animation[i]  = NULL;
	}
}

Enemy::~Enemy()
{
}

void Enemy::Attack()
{
	if (EA->SetEnemy(ATK, AL, AS,this->location) == false)
	{
		throw("�G�l�~�[�ƃG�l�~�[�A�^�b�N�Ԃ̒l�n���ɖ�肪����܂��B");
	}
	CreateObject<Enemy_Attack>(this->location,0);

}

void Enemy::Initialize(int enemy_type)
{
	LoadDivGraph("Resource/images/Enemy/troll/troll_all.png", 20, 5, 4, 198, 132, animation);

	//�G���[�`�F�b�N
	for (int i = 0; i < 20; i++)
	{
		if (animation[i] == -1)
		{
			throw("�G�l�~�[�摜�ɕs��������܂�\n");
		}
	}

	//�����E�傫���E�����摜�̐ݒ�
	radian = 0.0f;
	scale = 80.0f;
	image = animation[0];

	EA = CreateObject<Enemy_Attack>(Vector2D(),0);
}

void Enemy::Update()
{
	AnimeControl();
	
	Movement();

}

void Enemy::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1, radian, image, TRUE, FALSE);

	//�����蔻��̕`��
	__super::Draw();

}

void Enemy::OnHitCollision(GameObject* hit_object)
{
	if (hit_object == player)
	{
	//�v���C���[������_���[�W�̒l�����āA���̒l��HP������
	HP--;
	}

	//HP��0��菬�����Ȃ����玀�S���遦�o���l�𗎂Ƃ�
	if (HP <= 0)
	{
		DeleteObject(this);
	}
}


void Enemy::SetLocation(const Vector2D& location)
{
}

void Enemy::Movement()
{

	location -= player->GetVelocity();
	//�v���C���[�ƃG�l�~�[�̎��g�̍�
	Vector2D diff = player->GetLocation() - this->GetLocation();

	//�x�N�g������p�x��m��
	float radian = (float)atan2(diff.y, diff.x);

	if (diff.x > AL)
	{
		if (image != animation[13] && image != animation[14])
		{
			//�E�����̉摜
			image = animation[13];
		}
		//���̃x�N�g���ɉ����Ĉړ�����(0or180�ɋ߂��Ƒ傫��90or270�ɋ߂��قǏ��������遦���ʂ͂P)
		location += Vector2D(cosf(radian), sinf(radian));
	}
	else if (diff.x < -AL)
	{
		if (image != animation[3] && image != animation[4])
		{
			//�������̉摜
			image = animation[3];
		}
		//���̃x�N�g���ɉ����Ĉړ�����(0or180�ɋ߂��Ƒ傫��90or270�ɋ߂��قǏ��������遦���ʂ͂P)
		location += Vector2D(cosf(radian), sinf(radian));
	}
	else if (diff.y > AL)
	{
		//���̃x�N�g���ɉ����Ĉړ�����(0or180�ɋ߂��Ƒ傫��90or270�ɋ߂��قǏ��������遦���ʂ͂P)
		location += Vector2D(cosf(radian), sinf(radian));
	}
	else if (diff.y < -AL)
	{
		//���̃x�N�g���ɉ����Ĉړ�����(0or180�ɋ߂��Ƒ傫��90or270�ɋ߂��قǏ��������遦���ʂ͂P)
		location += Vector2D(cosf(radian), sinf(radian));
	}
	else if (image == animation[13] || image == animation[14])
	{
		image = animation[10];
		Attack();
	}
	else if (image == animation[3] || image == animation[4])
	{
		image = animation[0];
		Attack();
	}
}

void Enemy::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
	//���݂̃A�j���[�V�����摜�����ǂ̒i�K�����擾����(j��Anim�̌��݂���������)(i�͏I�����������s�����ߓ��ɕs�v)
	if (animation_count >= 60)
	{
		int i = 0, j = 0;
		while (i == 1 || j < 20)
		{
			if (image == animation[j])
			{
				i = 1;
				break;
			}
			j++;
		}
		if (j == 20 && i == 0)
		{
			throw("�G�l�~�[�摜�ɕs��������܂�\n");
		}

		//�J�E���g�̃��Z�b�g
		animation_count = 0;


		//5/13

		//�摜�̐؂�ւ�
		if (j == 0)
		{
			image = animation[1];
		}
		if (j == 1)
		{
			image = animation[2];
		}
		if (j == 2)
		{
			image = animation[0];
		}

		if (j == 3)
		{
			image = animation[4];
		}
		if (j == 4)
		{
			image = animation[3];
		}

		if (j == 10)
		{
			image = animation[11];
		}
		if (j == 11 )
		{
			image = animation[12];
		}
		if (j == 12)
		{
			image = animation[10];
		}
	/*	if (j == 10)
		{
			image = animation[11];
			ac = 0;
		}
		if (j == 11 && ac == 0)
		{
			image = animation[12];
		}
		if (j == 11 && ac == 1)
		{
			image = animation[10];
		}
		if (j == 12)
		{
			image = animation[11];
			ac = 1;
		}*/

		if (j == 13)
		{
			image = animation[14];
		}
		if (j == 14)
		{
			image = animation[13];
		}


	}
}

Vector2D Enemy::GetLocation() const
{
	return location;
}

Vector2D Enemy::Getscale() const
{
	return scale;
}

void Enemy::Finalize()
{
	//effect�t����
	//���X�ɏ�����
	//�g�p�����摜���J������
	for (int i = 0; i < 20; i++)
	{
		DeleteGraph(animation[i]);
	}
	//���j����������������^�[��

	
}

void Enemy::SetPlayer(Player* player)
{
	this->player = player;
}

//�X�e�[�W�̃^�C�v�擾����
int Enemy::GetType() const
{
	return type;
}