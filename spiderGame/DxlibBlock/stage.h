#pragma once
class Stage
{
public:
	//地面の高さを決める
	static const int GROUND_Y = 180;
	static const int OUT_LINE_Y = 500;
	static const int GOAL_Y = -1000;
	static const int GROUND_LEFT = -1000;
	static const int GROUND_RIGHT = 7000;
	static const int GROUND_BOTTOM = 1500;
};

//関数
void DrawGround();
void InitStage();