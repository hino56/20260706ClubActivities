#include "DxLib.h"
#include "player.h"
#include "stage.h"
#include "hook.h"
#include"camera.h"

//型　 変数
Player player;

//初期化
void InitPlayer()
{
	player.x = 50.0f;
	player.y = 150.0f;

	/*player.positionTest.x = 50.0f;
	player.positionTest.y = 50.0f;*/

	player.vx = 0.0f;
	player.vy = 0.0f;

	player.isGround = false;
	player.isGameOver = false;
	player.isClear = false;
}

//更新
void UpdatePlayer()
{
	//ゲームオーバーの時実行
	if (player.isGameOver || player.isClear)
	{
		return;
	}


	//CheckHitKey() → キーが押されているか調べる関数
	//(KEY_INPUT_W) → 対象のキーは、W

	if (!hook.isActive)
	{
		//Aキーの設定
		if (CheckHitKey(KEY_INPUT_A))
		{
			player.x -= 2.0f;
		}

		//Dキーの設定
		if (CheckHitKey(KEY_INPUT_D))
		{
			player.x += 2.0f;
		}
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && player.isGround)
	{
		player.vy = JUMP_POWER;
	}

	//ジャンプ判定
	player.isGround = false;

	//重力の追加
	player.vy += 0.1f;

	//座標の更新
	player.x += player.vx;
	player.y += player.vy;

	//地面の当たり判定
	if (player.x >= -100 && player.x <= 100)
	{
		if (player.y + 10 >= Stage::GROUND_Y)
		{
			player.y = Stage::GROUND_Y - 10;
			player.vy = 0;

			player.vx = 0;  //横方向の慣性をなくす
			player.vy = 0;  //落下を止める

			player.isGround = true;
		}

	}

	//一定距離進んだらゲームクリア
	if (player.x >= CLEAR_X)
	{
		player.isClear = true;
		return;
	}

	if (!hook.isActive)
	{
		//一定の高さ落ちたらゲームオーバー
		if (player.y >= GAME_OVER_Y)
		{
			player.isGameOver = true;
			return;
		}
	}

	//hookの判定
	UpdateHook();
}

//描画
void DrawPlayer()
{
	if (player.isGameOver)
	{
		//ゲームオーバーの表示
		DrawString(300, 270, "GAME OVER", GetColor(255, 0, 0));

		return;
	}

	if (player.isClear)
	{
		DrawString(300, 270, "GAME CLEAR", GetColor(255, 255, 0));

		return;
	}

	//プレイヤーの描画
	DrawCircle((int)(player.x - cameraX), (int)player.y, 10, GetColor(255, 255, 255), TRUE);
}


