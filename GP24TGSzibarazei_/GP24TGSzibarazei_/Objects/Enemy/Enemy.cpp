#include"Enemy.h"
#include"DxLib.h"
#include"../Player/Player.h"

Enemy::Enemy() :animation_count(0),ATK (0),Speed(0),AS(0.0),HP(0)
{
	int i;
	for (i = 0; i < 8; i++) {
		animation[i]=NULL;
	}
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	//後々イラストをもらい次第実装確認
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	//animation[0] = LoadGraph("resource/images/enemy/~~~~~");
	
	//エラーチェック
	for (int i = 0; i < 8; i++)
	{
		if (animation[i] == -1)
		{
			throw("エネミー画像に不備があります\n");
		}
	}

	//向き・大きさ・初期画像の設定
	radian = 0.0f;
	scale = 5.0f;
	image = animation[0];
}

void Enemy::Update()
{

}

void Enemy::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 0.4, radian, image, TRUE, TRUE);

	//デバック用
#if _DEBUG
//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) *
		(float)scale.x / 2.0f);
	Vector2D box_collision_upper_right = location + (Vector2D(1.0f) *
		(float)scale.y / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_upper_right.x, box_collision_upper_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

void Enemy::Finalize()
{
	//使用した画像を開放する
	for (int i = 0; i < 8; i++)
	{
	DeleteGraph(animation[i]);
	}
}

void Enemy::OnHitCollision(GameObject* hit_object)
{
	HP--;
	if (HP == 0)
	{
		Finalize();
	}
}


void Enemy::SetLocation(const Vector2D& location)
{
}

void Enemy::Movement()
{
	Vector2D PlayerLocation;
	Vector2D PlayeToEnemy;
	//プレイヤーの位置を獲得
	PlayerLocation = (640.0f, 360.0f);
	//その方向に向かう
	PlayeToEnemy = PlayerLocation - GetLocation();

	//自身の攻撃範囲を目指してプレイヤーに対して歩く
	if (PlayeToEnemy.y > 0)
	{
		//上に向かう
		location.y++;
		WaitTimer(60);
	}
	else if (PlayeToEnemy.y < 0)
	{
		//下に向かう
		location.y--;
		WaitTimer(60);

	}

	if (PlayeToEnemy.x > 0)
	{
		//左に向かう
		location.x++;
		WaitTimer(60);

	}
	else if (PlayeToEnemy.x < 0)
	{
		//右に向かう
		location.x--;
		WaitTimer(60);
	}

	//遠距離なら、離れる
	//自身の攻撃範囲を目指してプレイヤーに対して歩く
	if (PlayeToEnemy.y > 0)
	{
		location.y--;
		WaitTimer(60);
	}
	else if (PlayeToEnemy.y < 0)
	{
		location.y++;
		WaitTimer(60);

	}

	if (PlayeToEnemy.x > 0)
	{
		location.x--;
		WaitTimer(60);

	}
	else if (PlayeToEnemy.x < 0)
	{
		location.x++;
		WaitTimer(60);
	}
	//ステージの移動に合わせて動く
}

void Enemy::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//６０フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
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
	//effect付ける
	//徐々に消える
	//使用した画像を開放する
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(animation[i]);
	}
	//撃破数か何かしらをリターン
}