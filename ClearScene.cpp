#include <Novice.h>

#include"structer.h"
#include"enum.h"
#include "stage.h"
#include "buddy.h"
#include "enemy.h"


void ClearSceneInitialize(System* system) {

	system->clearscene = DRAW;

	system->clearframe = 0;

	system->selectMenu = 2;

	system->ClearSceneSelectCoolTime = 15;
	system->ClearSceneSelect = false;

	system->ClearUI_Pos[0] = { 1408,384 };//もう一度
	system->ClearUI_Pos[1] = { 1408,474 };//次のステージ
	system->ClearUI_Pos[2] = { 1408,564 };//ステージセレクト
	system->ClearUI_Pos[3] = { WindowWidth / 2,WindowHeight / 2 };//ステージセレクト
	system->ClearUI_Pos[4] = { 1408,660 };//決定
	system->ClearUI_Pos[5] = { 0,0 };//決定

	system->selectFrame[0] = 0;
	system->selectFrame[1] = 0;
	system->selectFrame[2] = 0;


	//画像関連
	system->ClearUI_image[0] = Novice::LoadTexture("./MyResources./ClearUI.png");
	system->ClearUI_image[1] = Novice::LoadTexture("./MyResources./ClearUI.png");
	system->ClearUI_image[2] = Novice::LoadTexture("./MyResources./ClearUI.png");
	system->ClearUI_image[3] = Novice::LoadTexture("./MyResources./Clear_Push.png");
	system->ClearUI_image[4] = Novice::LoadTexture("./MyResources./ClearDecideUI.png");
	system->ClearUI_image[5] = Novice::LoadTexture("./MyResources./ClearBackUI.png");

	system->ClearUIColor = 0x00000000;

}

void ClearScene(GameObject* go, Key* key, System* system,Audio*audio) {

	if (go->buddy.IsClear) {

		//ブロックの角度を0にする
		//for (int i = 0; i < VerBlockNum; i++) {
		//	for (int j = 0; j < HolBlockNum; j++) {
		//		go->MapChip[i][j].degree = 0.0f;
		//		go->MapChip[i][j].theta = 0.0f;
		//	}
		//}


		switch (system->clearscene) {
		case DRAW:

			if (system->clearframe == 0) {
				Novice::PlayAudio(audio->se.clear, false, 1.5f);
			}
			system->clearframe++;
			if (system->clearframe < 120) {
				audio->bgm.volume = 0.05f;
			}
			else {
				audio->bgm.volume = 0.2f;
			}

			
			if (key->keys[DIK_J] && !key->preKeys[DIK_J]) {
				system->clearscene = SELECT;
				Novice::PlayAudio(audio->se.decide, false, 1.0f);
				system->clearframe = 0;

				//星の最高記録
				if (go->buddy.MaxStarCount[system->stageselect.select - 1] < go->buddy.starGetCount) {
					go->buddy.MaxStarCount[system->stageselect.select - 1] = go->buddy.starGetCount;
				}

			}

			break;

		case SELECT:

			if (system->ClearUIColor < 0x000000cc) {
				system->ClearUIColor += 0x00000011;
			}
			system->clearframe++;
			if (system->clearframe < 45) {
				for (int i = 0; i < 5; i++) {
					system->ClearUI_Pos[i].x = float(EASE::InOutQuad(-328, 1408, 45, system->clearframe));
				}
			}
			else {

				//選択
				if (system->ClearSceneSelectCoolTime == 15) {
					if (key->keys[DIK_W]) {
						if (system->selectMenu != 1) {
							system->selectMenu -= 1;
							system->ClearSceneSelect = true;
							Novice::PlayAudio(audio->se.select, false, 1.0f);
						}
					}
					else if (key->keys[DIK_S]) {
						if (system->selectMenu != 3) {
							system->selectMenu += 1;
							system->ClearSceneSelect = true;
							Novice::PlayAudio(audio->se.select, false, 1.0f);
						}
					}
				}

				if (system->ClearSceneSelect) {
					system->ClearSceneSelectCoolTime--;
					if (system->ClearSceneSelectCoolTime == 0) {
						system->ClearSceneSelectCoolTime = 15;
						system->ClearSceneSelect = false;
					}
				}

				////見た目の処理
				if (system->selectMenu == 1) {

					if (system->selectFrame[0] <= 15) {
						system->selectFrame[0]++;
					}
					system->selectFrame[1] = 0;
					system->selectFrame[2] = 0;
					
					//もう一度
					system->ClearUI_Pos[0].x = float(EASE::InOutQuad(-56, 1080, 15, system->selectFrame[0]));
					//それ以外の動き
					if (system->ClearUI_Pos[1].x < 1080) {
						system->ClearUI_Pos[1].x = float(EASE::InOutQuad(56, 1024, 15, system->selectFrame[0]));
					}
					if (system->ClearUI_Pos[2].x < 1080) {
						system->ClearUI_Pos[2].x = float(EASE::InOutQuad(56, 1024, 15, system->selectFrame[0]));
					}
				}
				else if (system->selectMenu == 2) {
					if (system->selectFrame[1] <= 15) {
						system->selectFrame[1]++;
					}
					system->selectFrame[0] = 0;
					system->selectFrame[2] = 0;

					//次のステージ
					system->ClearUI_Pos[1].x = float(EASE::InOutQuad(-56, 1080, 15, system->selectFrame[1]));
					//それ以外の動き
					if (system->ClearUI_Pos[0].x < 1080) {
						system->ClearUI_Pos[0].x = float(EASE::InOutQuad(56, 1024, 15, system->selectFrame[1]));
					}
					if (system->ClearUI_Pos[2].x < 1080) {
						system->ClearUI_Pos[2].x = float(EASE::InOutQuad(56, 1024, 15, system->selectFrame[1]));
					}
				}
				else if (system->selectMenu == 3) {
					if (system->selectFrame[2] <= 15) {
						system->selectFrame[2]++;
					}
					system->selectFrame[0] = 0;
					system->selectFrame[1] = 0;

					//ステージセレクト
					system->ClearUI_Pos[2].x = float(EASE::InOutQuad(-56, 1080, 15, system->selectFrame[2]));
					//それ以外の動き
					if (system->ClearUI_Pos[0].x < 1080) {
						system->ClearUI_Pos[0].x = float(EASE::InOutQuad(56, 1024, 15, system->selectFrame[2]));
					}
					if (system->ClearUI_Pos[1].x < 1080) {
						system->ClearUI_Pos[1].x = float(EASE::InOutQuad(56, 1024, 15, system->selectFrame[2]));
					}
				}

				//決定			
				if (system->selectMenu == 1) {
					if (key->keys[DIK_J] && !key->preKeys[DIK_J]) {
						system->sc.changeFlag = true;
						//SE
						Novice::PlayAudio(audio->se.decide, false, 1.0f);
					}
					if (system->sc.changeFlag && system->sc.Pos[3].x == 0.0f) {
						//もう一度
						ClearSceneInitialize(system);
						BuddyGameInitialize(go);
						EnemyMoveGameInitialize(go);
						StageGenerate(go, system);
						system->sc.changeFlag = false;
					}
				}
				else if (system->selectMenu == 2) {
					if (key->keys[DIK_J] && !key->preKeys[DIK_J]) {
						system->sc.changeFlag = true;
						//SE
						Novice::PlayAudio(audio->se.decide, false, 1.0f);
					}
					if (system->sc.changeFlag && system->sc.Pos[3].x == 0.0f) {
						//次のステージ
						ClearSceneInitialize(system);
						if (system->stageselect.select != 15) {
							system->stageselect.select += 1;

							//ステージセレクトの描画変数を変更する
							for (int i = 0; i < StageNum; i++) {
								system->stageselect.siobj[i].Pos.x -= WindowWidth;
								system->stageselect.siobj[i].PrePos.x = system->stageselect.siobj[i].Pos.x;
							}


						}
						BuddyGameInitialize(go);
						EnemyMoveGameInitialize(go);
						StageGenerate(go, system);



						system->sc.changeFlag = false;
					}
				}
				else if (system->selectMenu == 3) {
					if (key->keys[DIK_J] && !key->preKeys[DIK_J]) {
						system->sc.changeFlag = true;
						//SE
						Novice::PlayAudio(audio->se.decide, false, 1.0f);
					}
					if (system->sc.changeFlag && system->sc.Pos[3].x == 0.0f) {
					//ステージセレクト
					system->scene = StageSelect;
					ClearSceneInitialize(system);
					EnemyMoveGameInitialize(go);
					BuddyGameInitialize(go);
					system->sc.changeFlag = false;
					}
				}
				
			}

			break;
		}

	}

}

void ClearSceneDraw(GameObject* go, System* system) {

	if (go->buddy.IsClear) {
		switch (system->clearscene) {
		case DRAW:

			Novice::DrawQuad(
				//左上
				int(system->ClearUI_Pos[3].x - 320),
				int(system->ClearUI_Pos[3].y - 192),

				//右上
				int(system->ClearUI_Pos[3].x + 320),
				int(system->ClearUI_Pos[3].y - 192),

				//左下
				int(system->ClearUI_Pos[3].x - 320),
				int(system->ClearUI_Pos[3].y + 192),

				//右下
				int(system->ClearUI_Pos[3].x + 320),
				int(system->ClearUI_Pos[3].y + 192),

				//画像上の座標
				0, 0,

				//横幅、縦幅
				640, 384,

				//テクスチャハンドル
				system->ClearUI_image[3],

				//色
				0xFFFFFFFF
			);

			break;

		case SELECT:

			//描画処理

			Novice::DrawSprite(int(system->ClearUI_Pos[5].x), int(system->ClearUI_Pos[5].y), system->ClearUI_image[5], 1, 1, 0, system->ClearUIColor);

			for (int i = 0; i < 3; i++) {

				Novice::DrawQuad(
					//左上
					int(system->ClearUI_Pos[i].x - 192),
					int(system->ClearUI_Pos[i].y - 32),

					//右上
					int(system->ClearUI_Pos[i].x + 192),
					int(system->ClearUI_Pos[i].y - 32),

					//左下
					int(system->ClearUI_Pos[i].x - 192),
					int(system->ClearUI_Pos[i].y + 32),

					//右下
					int(system->ClearUI_Pos[i].x + 192),
					int(system->ClearUI_Pos[i].y + 32),

					//画像上の座標
					i * 384, 0,

					//横幅、縦幅
					384, 64,

					//テクスチャハンドル
					system->ClearUI_image[i],

					//色
					0xFFFFFFFF
				);

			}

			Novice::DrawQuad(
				//左上
				int(system->ClearUI_Pos[4].x - 96),
				int(system->ClearUI_Pos[4].y - 32),

				//右上
				int(system->ClearUI_Pos[4].x + 96),
				int(system->ClearUI_Pos[4].y - 32),

				//左下
				int(system->ClearUI_Pos[4].x - 96),
				int(system->ClearUI_Pos[4].y + 32),

				//右下
				int(system->ClearUI_Pos[4].x + 96),
				int(system->ClearUI_Pos[4].y + 32),

				//画像上の座標
				0, 0,

				//横幅、縦幅
				192, 64,

				//テクスチャハンドル
				system->ClearUI_image[4],

				//色
				0xFFFFFFFF
			);

			break;
		}
		

	}

}