#include <Novice.h>
#include"structer.h"


void UIInitialize(System* system) {

	system->ui.PlayUI_image=  Novice::LoadTexture("./MyResources./PlayUI.png");
	system->ui.PlayUI_Pos = {};
	system->ui.NotMovingTimer = 0;
	system->ui.DrawHight = 32.0f;
	system->ui.DrawWidth = 96.0f;

}

void PlayUI(System* system, GameObject* go, Key* key) {

	system->ui.PlayUI_Pos.x = go->player.Pos.x;
	system->ui.PlayUI_Pos.y = go->player.Pos.y + 64.0f;

	if (!go->buddy.IsClear) {
		system->ui.NotMovingTimer++;
	}

	if (key->keys[DIK_W] || key->keys[DIK_A] || key->keys[DIK_S] || key->keys[DIK_D] || key->keys[DIK_J]) {
		system->ui.NotMovingTimer = 0;
	}

	if (system->ui.NotMovingTimer >= 120) {
		if (system->ui.DrawHight < 32.0f) {
			system->ui.DrawHight += 4.0f;
		}
		if (system->ui.DrawWidth < 96.0f) {
			system->ui.DrawWidth += 12.0f;
		}
	}
	else {
		if (system->ui.DrawHight > 0.0f) {
			system->ui.DrawHight -= 2.0f;
		}
		if (system->ui.DrawWidth > 0.0f) {
			system->ui.DrawWidth -= 6.0f;
		}
	}

}

void PlayUIDraw(System* system) {

	Novice::DrawQuad(
		//左上
		int(system->ui.PlayUI_Pos.x - system->ui.DrawWidth / 2),
		int(system->ui.PlayUI_Pos.y - system->ui.DrawHight / 2),

		//右上
		int(system->ui.PlayUI_Pos.x + system->ui.DrawWidth / 2),
		int(system->ui.PlayUI_Pos.y - system->ui.DrawHight / 2),

		//左下
		int(system->ui.PlayUI_Pos.x - system->ui.DrawWidth / 2),
		int(system->ui.PlayUI_Pos.y + system->ui.DrawHight / 2),

		//右下
		int(system->ui.PlayUI_Pos.x + system->ui.DrawWidth / 2),
		int(system->ui.PlayUI_Pos.y + system->ui.DrawHight / 2),

		//画像上の座標
		0, 0,

		//横幅、縦幅
		96, 32,

		//テクスチャハンドル
		system->ui.PlayUI_image,

		//色
		WHITE
	);

}