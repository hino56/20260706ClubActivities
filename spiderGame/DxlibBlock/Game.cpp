#include"DxLib.h"
#include"Game.h"
#include<cmath>

//グローバル変数
Player player;

//描画
void DrawGame()
{
	
	//プレイヤーの描画
	DrawCircle((int)player.x,(int) player.y,10, GetColor(255, 255, 255), TRUE);

	//地面の描画


}

void InitGame()
{
	//プレイヤーの位置初期化
	player.x = 50;
	player.y = 100;


}
