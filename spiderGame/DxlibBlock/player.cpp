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


	// 横移動する前のX座標を保存
	float beforeX = player.x;

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

	// 移動前の足元のY座標を保存
	float beforeFootY = player.y + 10;

	// 接地状態をリセット
	player.isGround = false;

	// 重力の追加
	player.vy += 0.1f;

	// 座標の更新（それぞれ1回だけ）
	player.x += player.vx;
	player.y += player.vy;

	// 足場と縦方向に重なっているときだけ、横の衝突を調べる
// 足場の上端：Stage::GROUND_Y、下端：2000
	if (player.y + 10 > Stage::GROUND_Y &&
		player.y - 10 < 2000)
	{
		// 左から衝突：プレイヤーの右端が足場の左端を通過した
		if (beforeX + 10 <= -100 && player.x + 10 > -100)
		{
			player.x = -110; // 右端を足場の左端に合わせる
			player.vx = 0;   // 横方向の慣性を止める
		}
		// 右から衝突：プレイヤーの左端が足場の右端を通過した
		else if (beforeX - 10 >= 100 && player.x - 10 < 100)
		{
			player.x = 110; // 左端を足場の右端に合わせる
			player.vx = 0;  // 横方向の慣性を止める
		}
	}

	// 地面の当たり判定
	if (player.x + 10 > -100 && player.x - 10 < 100)
	{
		// 落下中に足場の上面を通過したら着地
		if (player.vy >= 0 &&
			beforeFootY <= Stage::GROUND_Y &&
			player.y + 10 >= Stage::GROUND_Y)
		{
			player.y = Stage::GROUND_Y - 10;
			player.vy = 0;
			player.vx = 0;

		}
	}

	//一定距離進んだらゲームクリア
	if (player.x >= CLEAR_X)
	{
		player.isClear = true;
		return;
	}

	// フックに接続中でも、一定の高さまで落ちたらゲームオーバー
	if (player.y >= GAME_OVER_Y)
	{
		player.isGameOver = true;
		return;
	}

	//hookの判定
	UpdateHook();
}

void DrawPlayer()
{
	if (player.isGameOver || player.isClear)
	{
		constexpr int CENTER_X = 500;
		constexpr int CENTER_Y = 275;
		constexpr int RESULT_FONT_SIZE = 48;
		constexpr int GUIDE_FONT_SIZE = 20;
		constexpr int GUIDE_OFFSET_Y = 50;

		const char clearText[] = "GAME CLEAR";
		const char gameOverText[] = "GAME OVER";
		const char guideText[] = " <  RETRY  :  [ ENTER ] > ";

		const int oldFontSize = GetFontSize();

		// 結果の文字を大きくして、白枠の中央に描く
		SetFontSize(RESULT_FONT_SIZE);

		const char* resultText = player.isClear ? clearText : gameOverText;
		const int resultLength = player.isClear
			? sizeof(clearText) - 1
			: sizeof(gameOverText) - 1;
		const int resultWidth = GetDrawStringWidth(resultText, resultLength);
		const unsigned int resultColor = player.isClear
			? GetColor(255, 255, 0)
			: GetColor(255, 0, 0);

		DrawString(
			CENTER_X - resultWidth / 2,
			CENTER_Y - GetFontSize() / 2,
			resultText,
			resultColor
		);

		// 操作案内を結果の下に描く
		SetFontSize(GUIDE_FONT_SIZE);
		const int guideWidth = GetDrawStringWidth(
			guideText, sizeof(guideText) - 1
		);

		DrawString(
			CENTER_X - guideWidth / 2,
			CENTER_Y + GUIDE_OFFSET_Y,
			guideText,
			GetColor(255, 255, 255)
		);

		SetFontSize(oldFontSize);
		return;
	}

	// プレイ中は白い丸を描く
	DrawCircle(
		static_cast<int>(player.x - cameraX),
		static_cast<int>(player.y - cameraY),
		10,
		GetColor(255, 255, 255),
		TRUE
	);
}