#include "Stage.h"
#include "../../Utility/InputControl.h"
#include "../../Scenes/Main.h"
#include "../Player/Player.h"
#include"DxLib.h"


//移動の速さ
Vector2D velocity;

//ステージ情報
int stage[3][3] = {
	{0,0,0},
	{0,0,0},
	{0,0,0} };

//コンストラクタ
Stage::Stage() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
	color = 0xffffff;
	type = 0;
}

//デストラクタ
Stage::~Stage()
{}

//初期化処理
void Stage::Initialize()
{
	//画像の読み込み
	//animation[0] = loadgraph("resource/images/tri-pilot1.png");
	//animation[1] = loadgraph("resource/images/tri-pilot2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw ("ステージの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 50.0;

	//初期画像の設定
	image = animation[0];

	type = Main::GetStageType();
}

//更新処理
void Stage::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	//AnimeControl();
}

//描画処理
void Stage::Draw() const
{
	//画像の描画
	Vector2D upper_left = location - (scale / 2.0f);
	Vector2D lower_right = location + (scale / 2.0f);

	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y,
		GetColor(255,255,255),TRUE);

	__super::Draw();
}

//終了時処理
void Stage::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Stage::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	if (InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		velocity.x += -5.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		velocity.x += 5.0f;
	}

	//上下移動
	if (InputControl::GetKey(KEY_INPUT_UP) || InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		velocity.y += -5.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		velocity.y += 5.0f;
	}
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

	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		velocity.x += +5.0f;
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
		velocity.y += +5.0f;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		velocity.y += -5.0f;
	}
	else
	{
		velocity.y += 0.0f;
	}

	////壁の処理
	//if (location.x < (640.0f - scale.x + 25.0f + scale.x / 2))
	//{	//左の壁
	//	velocity.x += 0.0f;
	//	location.x = 640 - scale.x + 25 + scale.x / 2.0f;
	//}
	//else if (location.x > (640.0f + scale.x - 25.0f - scale.x / 2.0f))
	//{	//右の壁
	//	velocity.x = 0.0f;
	//	location.x = 640.0f + scale.x - 25.0f - scale.x / 2.0f;
	//}
	//if (location.y < (360.0f - scale.y + 25.0f + scale.y / 2.0f))
	//{	//上の壁
	//	velocity.y = 0.0f;
	//	location.y = 360.0f - scale.y + 25.0f + scale.y / 2.0f;
	//}
	//else if (location.y > (360.0f + scale.y - 25.0f - scale.y / 2.0f))
	//{	//下の壁
	//	velocity.y = 0.0f;
	//	location.y = 360.0f + scale.y - 25.0f - scale.y / 2.0f;
	//}

	//現在の位置座標に速さを加算する
	location += velocity;
}

//アニメーション制御
//void Stage::AnimeControl()
//{
//	//フレームカウントを加算する
//	animation_count++;
//
//	//６０フレーム目に到達したら
//	if (animation_count >= 60)
//	{
//		//カウントのリセット
//		animation_count = 0;
//
//		//画像の切り替え
//		if (image == animation[0])
//		{
//			image = animation[1];
//		}
//		else
//		{
//			image = animation[0];
//		}
//	}
//}
