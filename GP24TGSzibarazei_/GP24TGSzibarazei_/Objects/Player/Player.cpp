#include "Player.h"
#include "../../Utility/InputControl.h"
#include"DxLib.h"


static Vector2D velocity;		//移動距離

//コンストラクタ
Player::Player() :animation_count(0), flip_flag(FALSE)
{
	hp = 4;
	max_hp = 5;
	mp = 20;
	level = 1;
	exp = 0;
	max_exp = 4;
	ult_count = 0;
	ult_active = false;
	move_image = 0;
	move_flag = 1;

	//移動距離
	velocity = Vector2D(0.0f);

	for (int i = 0; i < 8; i++)
	{
		animation[i] = NULL;
	}
	for (int i = 0; i < 7; i++)
	{
		ui_image[i] = NULL;
	}
}

//デストラクタ
Player::~Player()
{}

//初期化処理
void Player::Initialize()
{
	//前方向画像の読み込み
	LoadDivGraph("Resource/images/Player/samurai/samurai_all.png", 30, 6, 6, 133, 166, animation);

	///////////////////////画像追加予定
	////HP画像
	ui_image[0] = LoadGraph("Resource/images/Player/ui/Hp1.png");
	ui_image[1] = LoadGraph("Resource/images/Player/ui/Hp2.png");
	
	////MP画像
	//ui_image[3] = LoadGraph("Resource/images/Player/ui/Mp_1.png");
	//ui_image[4] = LoadGraph("Resource/images/Player/ui/Mp_2.png");
	//ui_image[5] = LoadGraph("Resource/images/Player/ui/Mp_3.png");
	////Level画像
	//ui_image[6] = LoadGraph("Resource/images/Player/ui/Exp_1.png");
	

	////エラーチェック（キャラ画像）
	//for (int i = 0; i < 36; i++)
	//{
	//	if (animation[i] == -1)
	//	{
	//		throw("ナイトの画像がありません\n");
	//	}
	//}
	if (animation[0] == -1)
	{
		throw("ナイトの画像がありません\n");
	}

	////////////////////画像追加予定
	//エラーチェック（UI画像）
	for (int i = 0; i < 2; i++)
	{
		if (ui_image[i] == -1)
		{
			throw("UI画像がありません\n");
		}
	}

	/*if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("ナイトの画像がありません\n");
	}*/

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 50.0f;

	//初期画像の設定
	image = animation[0];

	//移動距離
	velocity = Vector2D(0.0f);
}

//更新処理
void Player::Update()
{
	if (move_flag = 1)
	{
		//移動処理
		Movement();
		//攻撃処理
		Atack();
		//アニメーション制御
		AnimeControl();
	}
	else if (move_flag == 0)
	{
		//パッシブ獲得処理
		AcquisitionPassive();
	}
}

//描画処理
void Player::Draw() const
{
	if (move_flag == 1)
	{
		//プレイヤー画像の描画
		DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
		//HP画像の描画
		for (int i = 0; i < max_hp; i++)
		{
			if (i <= hp)
			{
				DrawRotaGraphF(30.f + (i * 50.f), 25.f, 0.04, radian, ui_image[0], TRUE, flip_flag);
			}
			else
			{
				DrawRotaGraphF(30.f + (i * 50.f), 25.f, 0.04, radian, ui_image[1], TRUE, flip_flag);
			}
		}
	}
	else if (move_flag == 0)
	{
		DrawFormatString(location.x, location.y, GetColor(0, 255, 0), "LevelUp");
	}
	
	DrawFormatString(10, 25, GetColor(0, 0, 255), "mp");
	DrawFormatString(50, 10, GetColor(0, 0, 255), "%d",exp);
	DrawFormatString(50, 25, GetColor(0, 0, 255), "%d", max_exp);
	DrawFormatString(50, 35, GetColor(255, 0, 0), "%d", level);
	DrawFormatString(480, 360, GetColor(255, 0, 0), "%d", ult_count);
	if (ult_active == true)
	{
		DrawFormatString(480, 380, GetColor(255, 0, 0), "ok");
	}
	else if (ult_active == false)
	{
		DrawFormatString(480, 340, GetColor(255, 0, 0), "no");
	}
	//デバック用
	__super::Draw();
}

//終了時処理
void Player::Finalize()
{
	//使用した画像を開放する
	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(animation[i]);
	}
	//使用した画像を開放する
	for (int i = 0; i < 2; i++)
	{
		DeleteGraph(ui_image[i]);
	}
}

//当たり判定通知処理
void Player::OnHitCollision(GameObject* hit_object,int i)
{
	//当たった時の処理
	//hp--;
}

//位置情報取得処理
Vector2D Player::GetLocation() const
{
	return this->location;
}

//大きさ取得処理
Vector2D Player::Getscale() const
{
	return this->scale;
}

//位置情報設定処理
void Player::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//移動処理
void Player::Movement()
{
	velocity = Vector2D(0.0f);

	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		velocity.x += -5.0f;

		//プレイヤー画像を左向きにする
		move_image = 2;
		image = animation[4];
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		velocity.x += 5.0f;

		//プレイヤー画像を右向きにする
		move_image = 3;
		image = animation[6];
	}
	else
	{
		velocity.x += 0.0f;
	}

	//上下移動
	if (InputControl::GetKey(KEY_INPUT_UP) || InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		velocity.y += -5.0f;

		//プレイヤー画像を後ろ向きにする
		move_image = 1;
		image = animation[2];
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		velocity.y += 5.0f;

		//プレイヤー画像を前向きにする
		move_image = 0;
		image = animation[0];
	}
	else
	{
		velocity.y += 0.0f;
	}

	//現在の位置座標に速さを加算する
	//location += velocity;
}

void Player::Atack()
{
	if(ult_count<=1800)
	ult_count++;
	if (ult_count >= 1800)
	{
		ult_active = true;
	}
	if (InputControl::GetKeyDown(KEY_INPUT_Q) && ult_active==true)
	{
		ult_active = false;
		ult_count = 0;
		Ultimate();
	}

	int get = 2;
	if (InputControl::GetKeyDown(KEY_INPUT_A))
	{
		LevelUp(get);
	}
	if (InputControl::GetKeyDown(KEY_INPUT_S))
	{
		hp--;
		if (hp < -1)
		{
			hp = -1;
		}
	}
	if (InputControl::GetKeyDown(KEY_INPUT_D))
	{
		hp++;
		if (hp > max_hp-1)
		{
			hp = max_hp-1;
		}
	}
	Ultimate();
}

void Player::Ultimate()
{
	
}

void Player::LevelUp(int get_exp)
{
	//現在の経験値に取得した経験値を加算
	exp += get_exp;
	//レベルアップに必要な経験値がたまったとき
	if (exp >= max_exp)
	{
		//レベルを1つ上げる
		level++;
		//余った経験値を現在の経験値にする
		exp = max_exp - exp;
		//次のレベルアップに必要な経験値を増やす
		max_exp=max_exp * 2;
		move_flag = 0;
	}
}

//アニメーション制御
void Player::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//６０フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントのリセット
		animation_count = 0;

		switch (move_image)
		{
		case 0:
			//画像の切り替え
			if (image == animation[0])
			{
				image = animation[1];
			}
			else
			{
				image = animation[0];
			}
			break;
			
		case 1:
			//画像の切り替え
			if (image == animation[2])
			{
				image = animation[3];
			}
			else
			{
				image = animation[2];
			}
			break;
			
		case 2:
			//画像の切り替え
			if (image == animation[4])
			{
				image = animation[5];
			}
			else
			{
				image = animation[4];
			}
			break;
			
		case 3:
			//画像の切り替え
			if (image == animation[6])
			{
				image = animation[7];
			}
			else
			{
				image = animation[6];
			}
			break;
		}
	}
}


void Player::AcquisitionPassive()
{
	if (InputControl::GetKeyDown(KEY_INPUT_V))
	{
		move_flag = 1;
	}
}

//移動距離取得処理
Vector2D Player::GetVelocity()
{
	return velocity;
}
