#include "stage.h"
#include "camera.h"
#include "DxLib.h"

namespace
{
	// このファイル内で管理する画像ハンドル
	int groundImage = -1;
}

// 初期化：ゲームループの前に1回だけ呼ぶ
void InitStage()
{
	groundImage = LoadGraph("stage/Ground.png");
}

// 地面の描画：毎フレーム呼ぶ
void DrawGround()
{
	// スタート地点の足場
	DrawBox(
		(int)(-100 - cameraX),
		(int)(Stage::GROUND_Y - cameraY),
		(int)(100 - cameraX),
		(int)(2000 - cameraY),
		GetColor(100, 100, 100),
		TRUE
	);

	// ゴール：X・Yの両方にカメラ座標を反映
	DrawBox(
		(int)(6000 - cameraX),
		(int)(Stage::GOAL_Y - cameraY),
		(int)(6060 - cameraX),
		(int)(1000 - cameraY),
		GetColor(255, 255, 0),
		TRUE
	);

	// 画像の読み込みに失敗していたら、画像の描画を行わない
	if (groundImage == -1)
	{
		return;
	}

	// 画像1枚を表示する横幅
	const int DRAW_WIDTH = 2500;

	// 左端から右端まで、横幅1000の画像を並べる
	for (int x = Stage::GROUND_LEFT;
		x < Stage::GROUND_RIGHT;
		x += DRAW_WIDTH)
	{
		DrawExtendGraph(
			(int)(x - cameraX),                    // 左端
			(int)(Stage::OUT_LINE_Y - cameraY),    // 上端
			(int)(x + DRAW_WIDTH - cameraX),       // 右端
			(int)(Stage::GROUND_BOTTOM - cameraY), // 下端
			groundImage,
			TRUE                                  // 透過を有効にする
		);
	}
}