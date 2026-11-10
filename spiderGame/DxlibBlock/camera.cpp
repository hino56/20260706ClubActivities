#include"camera.h"
#include"player.h"

//定数(画面上でプレイヤーを表示させるための固定位置)
const float PLAYER_SCREEN_X = 200.0f;
const float PLAYER_SCREEN_Y = 400.0f;

//初期化
float cameraX = 0.0f;
float cameraY = 0.0f;

//カメラの更新
void UpdateCamera()
{
	//プレイヤーが画面内に表示されるようにする
	cameraX = player.x - PLAYER_SCREEN_X;
	cameraY = player.y - PLAYER_SCREEN_Y;

	if (cameraX < 0)
	{
		cameraX = 0;
	}
	if (cameraY < 0)
	{
		cameraY = 0;
	}

}