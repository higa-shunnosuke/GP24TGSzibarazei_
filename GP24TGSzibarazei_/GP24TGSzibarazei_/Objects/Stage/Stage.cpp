#include "Stage.h"
#include "../../Utility/InputControl.h"
#include "../../Scenes/Main.h"
#include "../Player/Player.h"
#include"DxLib.h"


//移動の速さ
Vector2D velocity;
int hit = 0;

//ステージ情報
int stage[3][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0} };


//コンストラクタ
Stage::Stage()
{
	type = 0;
}

//デストラクタ
Stage::~Stage()
{

}

//初期化処理
void Stage::Initialize()
{
	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 500.0;

	//初期画像の設定
	image = NULL;

	type = Main::GetStageType();
}

//更新処理
void Stage::Update()
{
	//移動処理
	Movement();

}

//描画処理
void Stage::Draw() const
{
	//画像の描画
	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y,
		GetColor(255,255,255),TRUE);

	DrawFormatString(10, 200, 0xffffff, "%d", hit);

	__super::Draw();
}

//終了時処理
void Stage::Finalize()
{
	
}

//当たり判定通知処理
void Stage::OnHitCollision(GameObject* hit_object,int i)
{
	//当たった時の処理
	hit = i;
}

//位置情報取得処理
Vector2D Stage::GetLocation() const
{
	return this->location;
}

//大きさ取得処理
Vector2D Stage::Getscale() const
{
	return this->scale;
}

//位置情報設定処理
void Stage::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//ステージ情報取得処理
int Stage::GetStage(int i,int j)
{
	return stage[i][j];
}

//ステージ情報設定処理
void Stage::SetStage()
{

}

//移動処理
void Stage::Movement()
{
	velocity = 0.0f;

	if (hit == 0)
	{
		//左右移動
		if (InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
		{
			velocity.x += 5.0f;
		}
		else if (InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
		{
			velocity.x += -5.0f;
		}
		else
		{
			velocity.x += 0.0f;
		}

		//上下移動
		if (InputControl::GetKey(KEY_INPUT_UP) || InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
		{
			velocity.y += 5.0f;
		}
		else if (InputControl::GetKey(KEY_INPUT_DOWN) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
		{
			velocity.y += -5.0f;
		}
		else
		{
			velocity.y = 0.0f;
		}
	}
	else
	{
		velocity = 0;
	}

	location += velocity;
}

