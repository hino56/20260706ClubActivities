#include "stage.h"
#include"camera.h"
#include "DxLib.h"

////地面の描画
void DrawGround()
{
	//DrawBox(左上X、左上Y、右下X、右下Y、色、塗りつぶし);
	DrawBox((0 - cameraX), Stage::GROUND_Y, (100 - cameraX), 560, GetColor(100, 100, 100), TRUE);     //TRUEなら塗りつぶし、FALSEなら線だけ書く

}

