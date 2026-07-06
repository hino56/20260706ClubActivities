#include"DxLib.h"
using namespace std;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	//ゲーム画面の設定(TRUE:ウィンドウモード)(FALSE:フルスクリーンモード)
	ChangeWindowMode(TRUE);
	//DxLibの初期化
	DxLib_Init();
	//ゲームウィンドウのタイトル設定
	SetWindowText("SpiderGame");
	//画面のサイズと色数の設定(画面の横幅、画面の高さ、色の深さ)
	SetGraphMode(680, 560, 32);
	//初期化失敗時の終了設定
	if (DxLib_Init() == -1)
	{
		return -1;    //１行なので{}省略可能
	}
	
	//裏画面へのみ表示
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームを動かし続けるループ
	while (ProcessMessage() == 0)   //意味:ウィンドウが生きている限り動かし続ける(0→正常(続ける)｜-1→終了)
	//動作:ウィンドウの更新、キーボードの入力処理、OSからの終了要求チェック
	{
		ClearDrawScreen();    //画面を真っ白(リセット)にする
		//書かないと:前フレームの描画画残り、絵が重なるため画面がぐちゃぐちゃになる


		ScreenFlip();   //裏画面の完成品を表に描画する
		//『SetDrawScreen(DX_SCREEN_BACK)』で裏画面に表示、描画作業が完成したら『ScreenFlip』で表画面に表示
	}

	DxLib_End();    //ゲーム終了時にDxLibを終了させる
	return 0;     //プログラムが正常に終了した合図
}