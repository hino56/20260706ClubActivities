#include "player.h"
#include "DxLib.h"

void DrawPlayer()
{
	//ƒvƒŒƒCƒ„[‚Ì•`‰æ
	DrawCircle((int)player.x, (int)player.y, 20, GetColor(255, 255, 255), TRUE);
}
