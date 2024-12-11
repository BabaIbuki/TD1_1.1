#include<Novice.h>
#include"structer.h"
#include"enum.h"
#include"buddy.h"
#include"enemy.h"
#include"stage.h"

//初期化関数
void SystemInitialize(System* system) {
	system->scene = Title;
}


/*
void Restart(GameObject* go, Key* key, System* system) {
	if (system->sc.backColor > 0xffffff00) {
		system->sc.backColor -= 0x00000011;
	}

	

	if (key->keys[DIK_R] && !key->preKeys[DIK_R]) {
		/*system->sc.Restart = true;
		system->sc.backColor = 0xffffffff;
	}

	if (system->sc.Restart) {
		BuddyGameInitialize(go);
		EnemyMoveGameInitialize(go);
		StageGenerate(go, system);
		if (system->sc.backColor == 0xffffff00) {
			system->sc.Restart = false;
		}
	}

}
*/

void RestartDraw(System* system) {
	Novice::DrawSprite(0, 0, system->sc.RestartImage, 1, 1, 0, system->sc.backColor);
	if (system->sc.backColor > 0xffffff00) {
		system->sc.backColor -= 0x00000011;
	}
}


void SceneChangeInitialize(System* system) {

	system->sc.changeFlag = false;
	system->sc.Pos[0] = { -1216,0 };
	system->sc.Pos[1] = { -1216,192 };
	system->sc.Pos[2] = { -1216,384 };
	system->sc.Pos[3] = { -1216,576 };
	system->sc.image= Novice::LoadTexture("./MyResources./SceneChange.png");
	system->sc.RestartImage = Novice::LoadTexture("./MyResources./RestartSceneChange.png");
	system->sc.backColor = 0xffffff00;

}

void SceneChangeFunction(System* system) {

	if (system->sc.changeFlag) {
		if (system->sc.Pos[0].x < 0.0f) {
			system->sc.Pos[0].x += 64.0f;
		}
		if (system->sc.Pos[0].x >= -912.0f) {
			if (system->sc.Pos[1].x < 0.0f) {
				system->sc.Pos[1].x += 64.0f;
			}
		}
		if (system->sc.Pos[0].x >= -608.0f) {
			if (system->sc.Pos[2].x < 0.0f) {
				system->sc.Pos[2].x += 64.0f;
			}
		}
		if (system->sc.Pos[0].x >= -304.0f) {
			if (system->sc.Pos[3].x < 0.0f) {
				system->sc.Pos[3].x += 64.0f;
			}
		}
	}
	else {
		if (system->sc.Pos[0].x > -1216.0f) {
			system->sc.Pos[0].x -= 64.0f;
		}
		if (system->sc.Pos[0].x <= -304.0f) {
			if (system->sc.Pos[1].x > -1216.0f) {
				system->sc.Pos[1].x -= 64.0f;
			}
		}
		if (system->sc.Pos[0].x <= -608.0f) {
			if (system->sc.Pos[2].x > -1216.0f) {
				system->sc.Pos[2].x -= 64.0f;
			}
		}
		if (system->sc.Pos[0].x <= -912.0f) {
			if (system->sc.Pos[3].x > -1216.0f) {
				system->sc.Pos[3].x -= 64.0f;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		Novice::DrawSprite(int(system->sc.Pos[i].x), int(system->sc.Pos[i].y), system->sc.image, 1, 1, 0, WHITE);
	}
	
}


