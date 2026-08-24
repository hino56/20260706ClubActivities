#include"camera.h"
#include"player.h"

//定数(画面上でプレイヤーを表示させるための固定位置)
const float PLAYER_SCREEN_X = 150.0f;

//初期化
float cameraX = 0.0f;

//カメラの更新
void UpdateCamera()
{
	//プレイヤーが画面内に表示されるようにする
	cameraX = player.x - PLAYER_SCREEN_X;
}