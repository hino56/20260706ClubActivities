#pragma once
class Hook
{
public:
	//hookの座標(接続している)
	float x, y;

	//ロープの長さ
	float ropeLength;

	//hookが接続されているかを判断するための変数
	bool isActive;
};

class HookPoint
{
public:
	float x, y;
};

//定数
const int HOOK_POINT_COUNT = 6;

//hookをを複数のcppで使用できるようにする
extern Hook hook;

//複数のフックポイント
extern HookPoint hookPoints[HOOK_POINT_COUNT];

//関数
void InputHook();
void UpdateHook();
void DrawHook();