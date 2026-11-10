#include"DxLib.h"
#include "player.h"
#include "hook.h"
#include"camera.h"
#include"stage.h"


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

	//ゲーム画面の設定(TRUE:ウィンドウモード)(FALSE:フルスクリーンモード)
	ChangeWindowMode(FALSE);


	//画面のサイズと色数の設定(画面の横幅、画面の高さ、色の深さ)
	SetGraphMode(1000, 720, 32);


	//ゲームウィンドウのタイトル設定
	SetWindowText("SpiderGame");


	//初期化失敗時の終了設定
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// タイトル画像は起動時に一度だけ読み込む
	const int titleImage = LoadGraph("stage/title.png");
	bool isTitle = true;


	//stageの初期化
	InitStage();

	//裏画面へのみ表示
	SetDrawScreen(DX_SCREEN_BACK);


	//
	bool wasSpaceDown = false;


	//ゲームを動かし続けるループ
	while (ProcessMessage() == 0)
	{

		ClearDrawScreen();    //画面を真っ白(リセット)にする


		const bool isSpaceDown = CheckHitKey(KEY_INPUT_RETURN) != 0;
		const bool spacePressed = isSpaceDown && !wasSpaceDown;
		wasSpaceDown = isSpaceDown;

		if (!isTitle && (player.isClear || player.isGameOver) && spacePressed)
		{
			isTitle = true;
		}


		if (isTitle)
		{
			// 画像の横幅を画面に合わせ、16:9の比率で高さを決める
			const int titleWidth = 1000;
			const int titleHeight = titleWidth * 9 / 16;

			// 上下の余白が同じになるように、画像の開始位置を決める
			const int titleY = (720 - titleHeight) / 2;

			if (titleImage != -1)
			{
				DrawExtendGraph(
					0, titleY,                          // 画像の左上
					titleWidth, titleY + titleHeight,   // 画像の右下
					titleImage, FALSE
				);
			}

			//タイトル画像の内側に、黄色い枠を描く
			const int borderWidth = 3;
			const unsigned int borderColor = GetColor(255, 255, 255);

			for (int i = 0; i < borderWidth; ++i)
			{
				DrawBox(
					i, titleY + i,                               // 枠の左上
					titleWidth - 1 - i, titleY + titleHeight - 1 - i, // 枠の右下
					borderColor, FALSE                           // 塗りつぶさず輪郭だけ描く
				);
			}

			// スタート案内を中央に表示する
			const char startText[] = " < START  :  [ ENTER ] > ";
			const int textWidth = GetDrawStringWidth(
				startText, sizeof(startText) - 1
			);

			DrawString(
				(1000 - textWidth) / 2,
				titleY + titleHeight * 3 / 4, // 画像の上端から75%の位置
				startText,
				GetColor(255, 255, 255)
			);

			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				InitPlayer();  // 初期位置に戻し、isClear を false にする
				InitHook();    // フックを初期状態に戻す
				isTitle = false;
			}

			ScreenFlip();
			continue; // タイトル表示中は、この下のゲーム処理を飛ばす
		}

		//更新
		UpdatePlayer();
		UpdateCamera();
		// タイトル画像と同じ表示サイズにする
		const int viewWidth = 1000;
		const int viewHeight = viewWidth * 9 / 16; // 562
		const int viewY = (720 - viewHeight) / 2;  // 上の余白は79
		const int viewBottom = viewY + viewHeight;

		// ゲームの描画を、タイトルと同じ範囲に収める
		SetDrawArea(0, viewY, viewWidth, viewBottom);

		DrawGround();
		DrawPlayer();
		DrawHook();

		// 描画範囲を画面全体に戻す
		SetDrawArea(0, 0, 1000, 720);

		// ゲーム画面の内側に3ピクセルの白枠を描く
		const int borderWidth = 3;
		const unsigned int borderColor = GetColor(255, 255, 255);

		for (int i = 0; i < borderWidth; ++i)
		{
			DrawBox(
				i, viewY + i,                            // 左上
				viewWidth - 1 - i, viewBottom - 1 - i,   // 右下
				borderColor, FALSE                       // 輪郭だけ描く
			);
		}


		//// 確認用
		//DrawFormatString(
		//	10, 10,
		//	GetColor(255, 255, 255),
		//	"player.x = %.1f",
		//	player.x
		//);

		//DrawFormatString(
		//	10, 40,
		//	GetColor(255, 255, 255),
		//	"cameraX = %.1f",
		//	cameraX
		//);

		//DrawFormatString(
		//	10, 70,
		//	GetColor(255, 255, 255),
		//	"player.y=%.1f",
		//	player.y
		//);

		//DrawFormatString(
		//	10, 100,
		//	GetColor(255, 255, 255),
		//	"cameraY=%.1f",
		//	cameraY
		//);


		ScreenFlip();   //裏画面の完成品を表に描画する


		//終了処理
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

	}

	DxLib_End();    //ゲーム終了時にDxLibを終了させる
	return 0;     //プログラムが正常に終了した合図
}