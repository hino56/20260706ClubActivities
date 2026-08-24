#include"DxLib.h"
#include "player.h"
#include "hook.h"
#include"camera.h"
using namespace std;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

	//ゲーム画面の設定(TRUE:ウィンドウモード)(FALSE:フルスクリーンモード)
	ChangeWindowMode(TRUE);


	//画面のサイズと色数の設定(画面の横幅、画面の高さ、色の深さ)
	SetGraphMode(680, 560, 32);


	//ゲームウィンドウのタイトル設定
	SetWindowText("SpiderGame");


	//初期化失敗時の終了設定
	if (DxLib_Init() == -1)
	{
		return -1;
	}


	//playerの座標
	InputPlayer();

	//hookの座標
	InputHook();

	//裏画面へのみ表示
	SetDrawScreen(DX_SCREEN_BACK);


	//ゲームを動かし続けるループ
	while (ProcessMessage() == 0)
	{

		ClearDrawScreen();    //画面を真っ白(リセット)にする

		//更新
		UpdatePlayer();
		UpdateCamera();

		//地面の描画
		DrawGround();

		//プレイヤーの描画
		DrawPlayer();

		//hookの描画
		DrawHook();

		ScreenFlip();   //裏画面の完成品を表に描画する

	}

	DxLib_End();    //ゲーム終了時にDxLibを終了させる
	return 0;     //プログラムが正常に終了した合図
}