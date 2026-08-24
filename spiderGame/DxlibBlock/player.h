#pragma once
class Player
{
public:
	//floatを使用→少数が使える→動きが滑らかに
	float x, y;			//playerの座標

	float vx, vy;       //playerの速度

	bool isGround;

	bool isGameOver;

	bool isClear;
};

//playerを複数のcppで使用できるようにする
extern Player player;

//定数
const float JUMP_POWER = -3.0f;

const float GAME_OVER_Y = 650.0f;

const float CLEAR_X = 3200.0f;

//関数
void InputPlayer();
void UpdatePlayer();
void DrawPlayer();
void DrawGround();