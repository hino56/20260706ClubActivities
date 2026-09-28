#include "hook.h"
#include "player.h"
#include"camera.h"
#include <math.h>
#include "DxLib.h"

//定数
const float RELEASE_UP_POWER = 2.0f;

//型　 変数
Hook hook;

//配列
HookPoint hookPoints[HOOK_POINT_COUNT] = { {500.0f,200.0f},{1500.0f,100.0f},{2500.0f,250.0f},{3500.0f,150.0f},{4500.0f,200.0f},{5500.0f,250.0f} };

//hookの初期化
void InitHook()
{
	//座標の初期化
	hook.x = 0.0f;
	hook.y = 0.0f;
	hook.ropeLength = 0.0f;

	//hookがどこにも接続されていない状態にする
	hook.isActive = false;
}

//hookに関する状態の更新
void UpdateHook()
{
	//Qキー入力時に実行
	if (CheckHitKey(KEY_INPUT_Q))
	{
		//!hook.isActiveの結果が「true」の時実行
		if (!hook.isActive)
		{
			int nearestIndex = 0;

			//プレイヤーとhookの距離座標計算
			float dx = hookPoints[0].x - player.x;
			float dy = hookPoints[0].y - player.y;

			float minDistance = sqrtf(dx * dx + dy * dy);

			for (int i = 0;i < HOOK_POINT_COUNT;i++)
			{
				float dx = hookPoints[i].x - player.x;
				float dy = hookPoints[i].y - player.y;


				float distance = sqrtf(dx * dx + dy * dy);


				//今までよりも距離が近かった場合
				if (distance < minDistance)
				{
					minDistance = distance;
					nearestIndex = i;
				}
			}

			//1番近いフックに接続
			hook.x = hookPoints[nearestIndex].x;
			hook.y = hookPoints[nearestIndex].y;


			//接続した距離でロープを繋ぐ
			hook.ropeLength = minDistance;
		}

		//falseからtrueに置き換え
		hook.isActive = true;

		//プレイヤーとhookの距離座標計算
		float dx = player.x - hook.x;
		float dy = player.y - hook.y;

		//座標から直線距離を求める式
		float distance = sqrtf(dx * dx + dy * dy);

		// ロープの長さを超えた場合
		if (distance > 0.0f)
		{
			//hookPointから見たプレイヤーの方向計算
			float dirX = dx / distance;
			float dirY = dy / distance;

			//playerをロープの位置まで戻す
			player.x = hook.x + dirX * hook.ropeLength;
			player.y = hook.y + dirY * hook.ropeLength;

			//プレイヤーの速度がロープを伸ばす方向にどれほどかかっているか
			float velocityDot = player.vx * dirX + player.vy * dirY;

			//ロープの方向への速度を消す
			player.vx -= velocityDot * dirX;
			player.vy -= velocityDot * dirY;
		}
	}
	//hookを離したとき(Qキーを離す)に接続状態を「false」にする　
	else
	{
		//hookが接続されている場合
		if (hook.isActive)
		{
			if (hook.y < player.y)
			{
				//上方向へ加速
				player.vy -= RELEASE_UP_POWER;
			}
		}

		//hook.isActiveをfalseに変更
		hook.isActive = false;
	}
}

//hookの描画
void DrawHook()
{
	for (int i = 0;i < HOOK_POINT_COUNT;i++)
	{
		//hookPointの描画
		DrawCircle((int)(hookPoints[i].x - cameraX), (int)hookPoints[i].y, 5, GetColor(255, 0, 0), TRUE);
	}

	//hookが接続されているとき
	if (hook.isActive)
	{
		//hookPointからプレイヤーまでのロープを描画
		DrawLine((int)(player.x - cameraX), (int)player.y, (int)(hook.x - cameraX), (int)hook.y, GetColor(255, 255, 255));
	}

}
