#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../Stage/Stage.h"
#include "DxLib.h"


static Vector2D velocity;		//移動距離

//どこが当たっているか
static bool hit_l;
static bool hit_r;
static bool hit_u;
static bool hit_d;

//コンストラクタ
Player::Player() :animation_count(0), flip_flag(FALSE)
{
	hp = 4;
	max_hp = 5;
	limit_hp = 0;
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
	for (int i = 0; i < 10; i++)
	{
		number_image[i] = NULL;
	}
	for (int i = 0; i < 2; i++)
	{
		ui_number[i] = NULL;
	}
}

//デストラクタ
Player::~Player()
{}

//初期化処理
void Player::Initialize(int player_type)
{
	//前方向画像の読み込み
	LoadDivGraph("Resource/images/Player/knight/knight_all.png", 23, 5, 5, 160, 200, animation);

	///////////////////////画像追加予定
	////HP画像
	ui_image[0] = LoadGraph("Resource/images/Player/ui/Hp1.png");
	ui_image[1] = LoadGraph("Resource/images/Player/ui/Hp2.png");
	ui_image[2] = LoadGraph("Resource/images/Player/ui/HpArmor2.png");
	////アルティメット画像
	ui_image[3] = LoadGraph("Resource/images/Player/ui/ult_put.png");
	ui_image[4] = LoadGraph("Resource/images/Player/ui/ult_icon.png");
	////MP画像
	//ui_image[3] = LoadGraph("Resource/images/Player/ui/Mp_1.png");
	//ui_image[4] = LoadGraph("Resource/images/Player/ui/Mp_2.png");
	//ui_image[5] = LoadGraph("Resource/images/Player/ui/Mp_3.png");
	////Level画像
	//ui_image[6] = LoadGraph("Resource/images/Player/ui/Exp_1.png");
	
	////数字画像
	number_image[0] = LoadGraph("Resource/images/Player/ui/number_0.png");
	number_image[1] = LoadGraph("Resource/images/Player/ui/number_1.png");
	number_image[2] = LoadGraph("Resource/images/Player/ui/number_2.png");
	number_image[3] = LoadGraph("Resource/images/Player/ui/number_3.png");
	number_image[4] = LoadGraph("Resource/images/Player/ui/number_4.png");
	number_image[5] = LoadGraph("Resource/images/Player/ui/number_5.png");
	number_image[6] = LoadGraph("Resource/images/Player/ui/number_6.png");
	number_image[7] = LoadGraph("Resource/images/Player/ui/number_7.png");
	number_image[8] = LoadGraph("Resource/images/Player/ui/number_8.png");
	number_image[9] = LoadGraph("Resource/images/Player/ui/number_9.png");

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
	for (int i = 0; i < 4; i++)
	{
		if (ui_image[i] == -1)
		{
			throw("UI画像がありません\n");
		}
	}

	/*for (int i = 0; i < 10; i++)
	{
		if (number_image[i] == -1)
		{
			throw("数字画像がありません\n");
		}
	}*/

	/*if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("ナイトの画像がありません\n");
	}*/

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 50.0f;

	//初期画像の設定
	image = animation[5];

	//移動距離
	velocity = Vector2D(0.0f);
}

//更新処理
void Player::Update()
{
	if (move_flag == 1)
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

	//hitを初期化（移動処理の後に初期化する）
	hit_l = false;
	hit_r = false;
	hit_u = false;
	hit_d = false;
}

//描画処理
void Player::Draw() const
{
	if (move_flag == 1)
	{
		//プレイヤー画像の描画
		DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
		//HP画像の描画
		for (int i = 0; i < max_hp+limit_hp; i++)
		{
			if (i <= hp)
			{
				DrawRotaGraphF(30.f + (i * 50.f), 25.f, 0.04, radian, ui_image[0], TRUE, flip_flag);
			}
			else if(i<max_hp)
			{
				DrawRotaGraphF(30.f + (i * 50.f), 25.f, 0.04, radian, ui_image[1], TRUE, flip_flag);
			}
			else
			{
				DrawRotaGraphF(30.0f + (i * 50.f), 25.f, 0.04, radian, ui_image[2], TRUE, flip_flag);
			}
		}
	}
	else if (move_flag == 0)
	{
		DrawFormatString(location.x, location.y, GetColor(0, 255, 0), "LevelUp");
	}
	//アルティメット描画
	DrawRotaGraphF(1050.f, 500.f,1.5, radian, ui_image[3], TRUE, flip_flag);
	DrawRotaGraphF(1050.f, 500.f, 2, radian, ui_image[4], TRUE, flip_flag);

	//その他
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
void Player::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	//hp--;
	
	Vector2D pl = this->GetLocation();
	Vector2D ps = this->GetBoxSize() / 2.0f;
	Vector2D ol = hit_object->GetLocation();
	Vector2D os = hit_object->GetBoxSize() / 2.0f;

	//横方向
	//プレイヤーの左側がステージの左側より右のとき
	if (pl.x-ps.x >= ol.x-os.x)
	{
		hit_l = true;
	}
	//プレイヤーの右側がステージの右側より左のとき
	if (pl.x+ps.x <= ol.x+os.x)
	{
		hit_r = true;
	}
	
	//縦方向
	//プレイヤーの上側がステージの上側より下のとき
	if (pl.y-ps.y >= ol.y-os.y)
	{
		hit_u = true;
	}
	//プレイヤーの下側がステージの下側より上のとき
	if (pl.y+ps.y <= ol.y+os.y)
	{
		hit_d = true;
	}

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
	if ((InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT)) && hit_l != false )
	{
		velocity.x += -5.0f;

		//プレイヤー画像を左向きにする
		move_image = LEFT;
		image = animation[10];
	}
	if ((InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT)) && hit_r != false)
	{
		velocity.x += 5.0f;

		//プレイヤー画像を右向きにする
		move_image = RIGHT;
		image = animation[15];
	}

	//上下移動
	if ((InputControl::GetKey(KEY_INPUT_UP) || InputControl::GetButton(XINPUT_BUTTON_DPAD_UP)) && hit_u != false)
	{
		velocity.y += -5.0f;

		//プレイヤー画像を後ろ向きにする
		move_image = BACK;
		image = animation[2];
	}
	if ((InputControl::GetKey(KEY_INPUT_DOWN) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN)) && hit_d != false)
	{
		velocity.y += 5.0f;

		//プレイヤー画像を前向きにする
		move_image = FRONT;
		image = animation[5];
	}
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
		if (limit_hp > 0)
		{
			limit_hp--;
		}
		else
		{
			hp--;
		}
		
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
}

void Player::Ultimate()
{
	limit_hp = 3;
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
		case FRONT:
			//画像の切り替え
			if (image == animation[5])
			{
				image = animation[7];
			}
			else
			{
				image = animation[5];
			}
			break;
			
		case BACK:
			//画像の切り替え
			if (image == animation[0])
			{
				image = animation[2];
			}
			else
			{
				image = animation[0];
			}
			break;
			
		case LEFT:
			//画像の切り替え
			if (image == animation[10])
			{
				image = animation[12];
			}
			else
			{
				image = animation[10];
			}
			break;
			
		case RIGHT:
			//画像の切り替え
			if (image == animation[15])
			{
				image = animation[17];
			}
			else
			{
				image = animation[15];
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
