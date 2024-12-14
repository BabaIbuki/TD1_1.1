//ソースファイルの読み込み
#include<Novice.h>

//ヘッダーファイルの読み込み
#include"structer.h"
#include"common.h"

//最初に読み込むプレイヤーの初期化の関数
void PlayerInitialize(GameObject* go) {

	//座標の初期化
	//go->player.Pos.x = BLOCKSIZE + BLOCKSIZE / 2;
	//go->player.Pos.y = BLOCKSIZE * 3 + BLOCKSIZE / 2;

	go->player.Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 5 * BLOCKSIZE + BLOCKSIZE / 2;

	//サイズの初期化
	go->player.width = BLOCKSIZE;
	go->player.height = BLOCKSIZE;

	// アニメーション用の変数
	go->player.frameCount = 0;
	go->player.animCount = 0;

	//動きの制限
	go->player.MoveCoolTime = 10;
	go->player.MoveFlag = false;

	go->player.predicitionBlockFrameCount = 0;
	go->player.predicitionBlockAnimCount = 0;

	// 向き
	go->player.direction = RIGHT;

	//画像関連
	go->player.image = Novice::LoadTexture("./MyResources./player.png");
	go->player.predicitionBlockgraphHandle = Novice::LoadTexture("./MyResources./PlayerCursol.png");
	go->player.clearedImage = Novice::LoadTexture("./MyResources./playerCleared.png");
	go->player.color = WHITE;

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->player.select[i][j] = false;
		}
	}
}

//ゲームプレイ中の初期化
//void PlayerGameInitialize(GameObject* go) {
//
//}

//プレイヤーの動きの関数（マップチップとの当たり判定も込みの可能性もあり）
void PlayerMove(GameObject* go, Key* key) {
	go->player.PrePos = go->player.Pos;

	if (!go->buddy.IsClear) {
		if (go->player.MoveCoolTime == 10) {
			if (key->keys[DIK_W]) {
				go->player.Pos.y -= BLOCKSIZE;
				go->player.MoveFlag = true;
			} else if (key->keys[DIK_S]) {
				go->player.Pos.y += BLOCKSIZE;
				go->player.MoveFlag = true;
			} else if (key->keys[DIK_A]) {
				go->player.Pos.x -= BLOCKSIZE;
				go->player.MoveFlag = true;
				if (go->player.direction != LEFT) {
					go->player.direction = LEFT;
				}
			} else if (key->keys[DIK_D]) {
				go->player.Pos.x += BLOCKSIZE;
				go->player.MoveFlag = true;
				if (go->player.direction != RIGHT) {
					go->player.direction = RIGHT;
				}
			}
		}
	}

	if (go->player.MoveFlag) {
		go->player.MoveCoolTime--;
	}
	if (go->player.MoveCoolTime <= 0) {
		go->player.MoveCoolTime = 10;
		go->player.MoveFlag = false;
	}

	if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].Map == 1
		//|| go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].Map == 2
		/* || go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].Map == 3*/) {
		go->player.Pos = go->player.PrePos;
	}
}


//色を付ける・回収する関数
void ColorSystem(GameObject* go, Key* key, Audio* audio) {

	if (!go->buddy.IsClear) {

		if (key->keys[DIK_J] && !key->preKeys[DIK_J]) {

			//SE
			Novice::PlayAudio(audio->se.inversion, false, 1.0f);

			//範囲内にオブジェクトがあれば色を塗れるフラグを折る
			for (int i = 0; i < 10; i++) {
				if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].Map == 2) {
					if ((go->player.Pos.x - go->player.width / 2) < (go->buddy.Pos.x + go->buddy.width / 2) &&
						(go->buddy.Pos.x - go->buddy.width / 2) < (go->player.Pos.x + go->player.width / 2) &&
						(go->player.Pos.y - go->player.height / 2) < (go->buddy.Pos.y + go->buddy.height / 2) &&
						(go->buddy.Pos.y - go->buddy.height / 2) < (go->player.Pos.y + go->player.height / 2)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].CanPaint = false;
					} else if ((go->player.Pos.x - go->player.width / 2) < (go->enemy[i].Pos.x + go->enemy[i].width / 2) &&
						(go->enemy[i].Pos.x - go->enemy[i].width / 2) < (go->player.Pos.x + go->player.width / 2) &&
						(go->player.Pos.y - go->player.height / 2) < (go->enemy[i].Pos.y + go->enemy[i].height / 2) &&
						(go->enemy[i].Pos.y - go->enemy[i].height / 2) < (go->player.Pos.y + go->player.height / 2)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].CanPaint = false;
					}
					/*else {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].IsPaint = true;
					}*/
				} else {
					go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].CanPaint = false;
				}
				if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE].Map == 2) {
					if ((go->player.Pos.x - go->player.width / 2) < (go->buddy.Pos.x + go->buddy.width / 2) &&
						(go->buddy.Pos.x - go->buddy.width / 2) < (go->player.Pos.x + go->player.width / 2) &&
						(go->player.Pos.y - go->player.height / 2 + BLOCKSIZE) < (go->buddy.Pos.y + go->buddy.height / 2) &&
						(go->buddy.Pos.y - go->buddy.height / 2) < (go->player.Pos.y + go->player.height / 2 + BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE].CanPaint = false;
					} else if ((go->player.Pos.x - go->player.width / 2) < (go->enemy[i].Pos.x + go->enemy[i].width / 2) &&
						(go->enemy[i].Pos.x - go->enemy[i].width / 2) < (go->player.Pos.x + go->player.width / 2) &&
						(go->player.Pos.y - go->player.height / 2 + BLOCKSIZE) < (go->enemy[i].Pos.y + go->enemy[i].height / 2) &&
						(go->enemy[i].Pos.y - go->enemy[i].height / 2) < (go->player.Pos.y + go->player.height / 2 + BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE].CanPaint = false;
					}
					/*else {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE].IsPaint = true;
					}*/
				} else {
					go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE].CanPaint = false;
				}
				if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE + 1].Map == 2) {
					if ((go->player.Pos.x - go->player.width / 2 + BLOCKSIZE) < (go->buddy.Pos.x + go->buddy.width / 2) &&
						(go->buddy.Pos.x - go->buddy.width / 2) < (go->player.Pos.x + go->player.width / 2 + BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2 + BLOCKSIZE) < (go->buddy.Pos.y + go->buddy.height / 2) &&
						(go->buddy.Pos.y - go->buddy.height / 2) < (go->player.Pos.y + go->player.height / 2 + BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint = false;
					} else if ((go->player.Pos.x - go->player.width / 2 + BLOCKSIZE) < (go->enemy[i].Pos.x + go->enemy[i].width / 2) &&
						(go->enemy[i].Pos.x - go->enemy[i].width / 2) < (go->player.Pos.x + go->player.width / 2 + BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2 + BLOCKSIZE) < (go->enemy[i].Pos.y + go->enemy[i].height / 2) &&
						(go->enemy[i].Pos.y - go->enemy[i].height / 2) < (go->player.Pos.y + go->player.height / 2 + BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint = false;
					}
					/*else {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE + 1].IsPaint = true;
					}*/
				} else {
					go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint = false;
				}
				if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE - 1].Map == 2) {
					if ((go->player.Pos.x - go->player.width / 2 - BLOCKSIZE) < (go->buddy.Pos.x + go->buddy.width / 2) &&
						(go->buddy.Pos.x - go->buddy.width / 2) < (go->player.Pos.x + go->player.width / 2 - BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2 + BLOCKSIZE) < (go->buddy.Pos.y + go->buddy.height / 2) &&
						(go->buddy.Pos.y - go->buddy.height / 2) < (go->player.Pos.y + go->player.height / 2 + BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint = false;
					} else if ((go->player.Pos.x - go->player.width / 2 - BLOCKSIZE) < (go->enemy[i].Pos.x + go->enemy[i].width / 2) &&
						(go->enemy[i].Pos.x - go->enemy[i].width / 2) < (go->player.Pos.x + go->player.width / 2 - BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2 + BLOCKSIZE) < (go->enemy[i].Pos.y + go->enemy[i].height / 2) &&
						(go->enemy[i].Pos.y - go->enemy[i].height / 2) < (go->player.Pos.y + go->player.height / 2 + BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint = false;
					}
					/*else {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE - 1].IsPaint = true;
					}*/
				} else {
					go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint = false;
				}
				if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE - 1].Map == 2) {
					if ((go->player.Pos.x - go->player.width / 2 - BLOCKSIZE) < (go->buddy.Pos.x + go->buddy.width / 2) &&
						(go->buddy.Pos.x - go->buddy.width / 2) < (go->player.Pos.x + go->player.width / 2 - BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2) < (go->buddy.Pos.y + go->buddy.height / 2) &&
						(go->buddy.Pos.y - go->buddy.height / 2) < (go->player.Pos.y + go->player.height / 2)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint = false;
					} else if ((go->player.Pos.x - go->player.width / 2 - BLOCKSIZE) < (go->enemy[i].Pos.x + go->enemy[i].width / 2) &&
						(go->enemy[i].Pos.x - go->enemy[i].width / 2) < (go->player.Pos.x + go->player.width / 2 - BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2) < (go->enemy[i].Pos.y + go->enemy[i].height / 2) &&
						(go->enemy[i].Pos.y - go->enemy[i].height / 2) < (go->player.Pos.y + go->player.height / 2)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint = false;
					}
					/*else {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE - 1].IsPaint = true;
					}*/
				} else {
					go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint = false;
				}
				if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE + 1].Map == 2) {
					if ((go->player.Pos.x - go->player.width / 2 + BLOCKSIZE) < (go->buddy.Pos.x + go->buddy.width / 2) &&
						(go->buddy.Pos.x - go->buddy.width / 2) < (go->player.Pos.x + go->player.width / 2 + BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2) < (go->buddy.Pos.y + go->buddy.height / 2) &&
						(go->buddy.Pos.y - go->buddy.height / 2) < (go->player.Pos.y + go->player.height / 2)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint = false;
					} else if ((go->player.Pos.x - go->player.width / 2 + BLOCKSIZE) < (go->enemy[i].Pos.x + go->enemy[i].width / 2) &&
						(go->enemy[i].Pos.x - go->enemy[i].width / 2) < (go->player.Pos.x + go->player.width / 2 + BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2) < (go->enemy[i].Pos.y + go->enemy[i].height / 2) &&
						(go->enemy[i].Pos.y - go->enemy[i].height / 2) < (go->player.Pos.y + go->player.height / 2)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint = false;
					}
					/*else {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE + 1].IsPaint = true;
					}*/
				} else {
					go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint = false;
				}
				if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE - 1].Map == 2) {
					if ((go->player.Pos.x - go->player.width / 2 - BLOCKSIZE) < (go->buddy.Pos.x + go->buddy.width / 2) &&
						(go->buddy.Pos.x - go->buddy.width / 2) < (go->player.Pos.x + go->player.width / 2 - BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2 - BLOCKSIZE) < (go->buddy.Pos.y + go->buddy.height / 2) &&
						(go->buddy.Pos.y - go->buddy.height / 2) < (go->player.Pos.y + go->player.height / 2 - BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint = false;
					} else if ((go->player.Pos.x - go->player.width / 2 - BLOCKSIZE) < (go->enemy[i].Pos.x + go->enemy[i].width / 2) &&
						(go->enemy[i].Pos.x - go->enemy[i].width / 2) < (go->player.Pos.x + go->player.width / 2 - BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2 - BLOCKSIZE) < (go->enemy[i].Pos.y + go->enemy[i].height / 2) &&
						(go->enemy[i].Pos.y - go->enemy[i].height / 2) < (go->player.Pos.y + go->player.height / 2 - BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint = false;
					}
					/*else {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE - 1].IsPaint = true;
					}*/
				} else {
					go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint = false;
				}
				if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE].Map == 2) {
					if ((go->player.Pos.x - go->player.width / 2) < (go->buddy.Pos.x + go->buddy.width / 2) &&
						(go->buddy.Pos.x - go->buddy.width / 2) < (go->player.Pos.x + go->player.width / 2) &&
						(go->player.Pos.y - go->player.height / 2 - BLOCKSIZE) < (go->buddy.Pos.y + go->buddy.height / 2) &&
						(go->buddy.Pos.y - go->buddy.height / 2) < (go->player.Pos.y + go->player.height / 2 - BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE].CanPaint = false;
					} else if ((go->player.Pos.x - go->player.width / 2) < (go->enemy[i].Pos.x + go->enemy[i].width / 2) &&
						(go->enemy[i].Pos.x - go->enemy[i].width / 2) < (go->player.Pos.x + go->player.width / 2) &&
						(go->player.Pos.y - go->player.height / 2 - BLOCKSIZE) < (go->enemy[i].Pos.y + go->enemy[i].height / 2) &&
						(go->enemy[i].Pos.y - go->enemy[i].height / 2) < (go->player.Pos.y + go->player.height / 2 - BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE].CanPaint = false;
					}
					/*else {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE].IsPaint = true;
					}*/
				} else {
					go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE].CanPaint = false;
				}
				if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE + 1].Map == 2) {
					if ((go->player.Pos.x - go->player.width / 2 + BLOCKSIZE) < (go->buddy.Pos.x + go->buddy.width / 2) &&
						(go->buddy.Pos.x - go->buddy.width / 2) < (go->player.Pos.x + go->player.width / 2 + BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2 - BLOCKSIZE) < (go->buddy.Pos.y + go->buddy.height / 2) &&
						(go->buddy.Pos.y - go->buddy.height / 2) < (go->player.Pos.y + go->player.height / 2 - BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint = false;
					} else if ((go->player.Pos.x - go->player.width / 2 + BLOCKSIZE) < (go->enemy[i].Pos.x + go->enemy[i].width / 2) &&
						(go->enemy[i].Pos.x - go->enemy[i].width / 2) < (go->player.Pos.x + go->player.width / 2 + BLOCKSIZE) &&
						(go->player.Pos.y - go->player.height / 2 - BLOCKSIZE) < (go->enemy[i].Pos.y + go->enemy[i].height / 2) &&
						(go->enemy[i].Pos.y - go->enemy[i].height / 2) < (go->player.Pos.y + go->player.height / 2 - BLOCKSIZE)) {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint = false;
					}
					/*else {
						go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE + 1].IsPaint = true;
					}*/
				} else {
					go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint = false;
				}
			}

			//色を塗れるフラグがtrueなら色を付けるフラグを立てる
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].CanPaint) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].IsPaint = true;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE].CanPaint) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE].IsPaint = true;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE + 1].IsPaint = true;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE - 1].IsPaint = true;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE - 1].IsPaint = true;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE + 1].IsPaint = true;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE - 1].CanPaint) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE - 1].IsPaint = true;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE].CanPaint) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE].IsPaint = true;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE + 1].CanPaint) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE + 1].IsPaint = true;
			}


			//回収
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].Map == 3) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE].IsPaint = false;
				//go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE].Map = 2;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE].Map == 3) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE].IsPaint = false;
				//go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE].Map = 2;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE + 1].Map == 3) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE + 1].IsPaint = false;
				//go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE + 1].Map = 2;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE - 1].Map == 3) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE - 1].IsPaint = false;
				//go->MapChip[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE - 1].Map = 2;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE - 1].Map == 3) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE - 1].IsPaint = false;
				//go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE - 1].Map = 2;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE + 1].Map == 3) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE + 1].IsPaint = false;
				//go->MapChip[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE + 1].Map = 2;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE - 1].Map == 3) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE - 1].IsPaint = false;
				//go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE - 1].Map = 2;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE].Map == 3) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE].IsPaint = false;
				//go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE].Map = 2;
			}
			if (go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE + 1].Map == 3) {
				go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE + 1].IsPaint = false;
				//go->MapChip[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE + 1].Map = 2;
			}

		}

		//IsPaintがtrueだったらマップ番号を変更
		for (int i = 0; i < VerBlockNum; i++) {
			for (int j = 0; j < HolBlockNum; j++) {

				if (go->MapChip[i][j].IsPaint) {
					if (go->MapChip[i][j].Map == 2 || go->MapChip[i][j].Map == 3) {
						go->MapChip[i][j].Map = 3;
					}
				} else {
					if (go->MapChip[i][j].Map == 2 || go->MapChip[i][j].Map == 3) {
						go->MapChip[i][j].Map = 2;
					}
				}

				//色を付けられるかのフラグ初期化
				go->MapChip[i][j].CanPaint = true;


			}
		}
	}
}

//予測8マスを作る
void Predicition8Block(GameObject* go) {

	//はじめにすべてのフラグを折る
	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->player.select[i][j] = false;
		}
	}


	go->player.select[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE - 1] = true;
	go->player.select[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE] = true;
	go->player.select[int(go->player.Pos.y) / BLOCKSIZE - 1][int(go->player.Pos.x) / BLOCKSIZE + 1] = true;
	go->player.select[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE - 1] = true;
	go->player.select[int(go->player.Pos.y) / BLOCKSIZE][int(go->player.Pos.x) / BLOCKSIZE + 1] = true;
	go->player.select[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE - 1] = true;
	go->player.select[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE] = true;
	go->player.select[int(go->player.Pos.y) / BLOCKSIZE + 1][int(go->player.Pos.x) / BLOCKSIZE + 1] = true;
}


//マップチップとの当たり判定
//void PlayerCollisionMapChip(GameObject* go) {
//
//}

//プレイヤーの描画
void PlayerAnimation(GameObject* go) {

	// プレイヤーのアニメーションの更新処理
	if (go->player.frameCount < 119) {
		go->player.frameCount++;
	} else {
		go->player.frameCount = 0;
	}

	if (go->player.frameCount < 59) {
		go->player.animCount = go->player.frameCount / 6;
	}

	// 予測線のアニメーションの更新処理
	if (go->player.predicitionBlockFrameCount < 59) {
		go->player.predicitionBlockFrameCount++;
	} else {
		go->player.predicitionBlockFrameCount = 0;
	}

	go->player.predicitionBlockAnimCount = go->player.predicitionBlockFrameCount / 6;

}

//プレイヤーの描画
void PlayerDraw(GameObject* go) {

	// 予測線の描画
	Novice::DrawQuad(
		//左上
		int(go->player.DrawLeftTop.x - go->player.width),
		int(go->player.DrawLeftTop.y - go->player.height),

		//右上
		int(go->player.DrawRightTop.x + go->player.width),
		int(go->player.DrawRightTop.y - go->player.height),

		//左下
		int(go->player.DrawLeftBottom.x - go->player.width),
		int(go->player.DrawLeftBottom.y + go->player.height),

		//右下
		int(go->player.DrawRightBottom.x + go->player.width),
		int(go->player.DrawRightBottom.y + go->player.height),

		//画像上の座標
		0 + 128 * go->player.predicitionBlockAnimCount, 0,

		//横幅、縦幅
		128, 128,

		//テクスチャハンドル
		go->player.predicitionBlockgraphHandle,

		//色
		WHITE
	);

	// 相棒がクリアしていなければ
	if (!go->buddy.IsClear) {

		// プレイヤーの描画
		Novice::DrawQuad(
			//左上
			int(go->player.DrawLeftTop.x),
			int(go->player.DrawLeftTop.y),

			//右上
			int(go->player.DrawRightTop.x),
			int(go->player.DrawRightTop.y),

			//左下
			int(go->player.DrawLeftBottom.x),
			int(go->player.DrawLeftBottom.y),

			//右下
			int(go->player.DrawRightBottom.x),
			int(go->player.DrawRightBottom.y),

			//画像上の座標
			0 + 64 * go->player.animCount, 64 * (go->player.direction - 2),

			//横幅、縦幅
			64, 64,

			//テクスチャハンドル
			go->player.image,

			//色
			go->player.color
		);

	} else {

		// プレイヤーの描画
		Novice::DrawQuad(
			//左上
			int(go->player.DrawLeftTop.x),
			int(go->player.DrawLeftTop.y),

			//右上
			int(go->player.DrawRightTop.x),
			int(go->player.DrawRightTop.y),

			//左下
			int(go->player.DrawLeftBottom.x),
			int(go->player.DrawLeftBottom.y),

			//右下
			int(go->player.DrawRightBottom.x),
			int(go->player.DrawRightBottom.y),

			//画像上の座標
			0 + 64 * go->player.animCount, 64 * (go->player.direction - 2),

			//横幅、縦幅
			64, 64,

			//テクスチャハンドル
			go->player.clearedImage,

			//色
			go->player.color
		);

	}

}