//ソースファイルの読み込み
#include<Novice.h>

//ヘッダーファイルの読み込み
#include"structer.h"
#include"stage.h"
#include"common.h"
#include"effect.h"
#include"enum.h"

//最初に読み込むステージ情報初期化の関数
void StageInitialize(GameObject* go) {
	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Pos.x = j * BLOCKSIZE + BLOCKSIZE / 2.0f;
			go->MapChip[i][j].Pos.y = i * BLOCKSIZE + BLOCKSIZE / 2.0f;

			go->MapChip[i][j].width = BLOCKSIZE;
			go->MapChip[i][j].height = BLOCKSIZE;

			go->MapChip[i][j].IsPaint = false;


			go->MapChip[i][j].CanPaint = true;

			go->MapChip[i][j].degree = 0.0f;

			go->MapChip[i][j].IncreaseFlag = true;
			go->MapChip[i][j].DecreaseFlag = false;
			go->MapChip[i][j].ShakeNum = 0;
			go->MapChip[i][j].ShakeWidth = 20.0f;

			// 星ブロックの描画用変数の初期化
			go->MapChip[i][j].star.animCount = 0;
			go->MapChip[i][j].star.frameCount = 0;
			go->MapChip[i][j].star.isGet = false;

			// ワープボックスの描画用変数の初期化
			go->MapChip[i][j].wbg.animCount = 0;
			go->MapChip[i][j].wbg.frameCount = 0;

			// ゴールの描画用変数の初期化
			go->MapChip[i][j].goal.animCount = 0;
			go->MapChip[i][j].goal.frameCount = 0;

			go->MapChip[i][j].color = WHITE;

			//エフェクト関連の変数の初期化
			go->MapChip[i][j].IsEffectGenarated = false;
			go->MapChip[i][j].GenarateEffectNum = 0;
		}
	}
	go->MapChip[0][0].image = Novice::LoadTexture("./MyResources./Block.png");
	go->MapChip[0][1].image = Novice::LoadTexture("./MyResources./Star.png");
	go->MapChip[0][1].star.gotEffectImage = Novice::LoadTexture("./MyResources./StarGotEffect.png");
	go->MapChip[0][2].image = Novice::LoadTexture("./MyResources./WarpBox.png");
	go->MapChip[0][4].image = Novice::LoadTexture("./MyResources./WarpingBlock.png");
	go->MapChip[0][3].image = Novice::LoadTexture("./MyResources./GoalPortal.png");
	go->MapChip[0][5].image = Novice::LoadTexture("./MyResources./Block8.png");
}

//ステージ情報の関数
void teststage(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,4,3,3,3,3,3,5,8,8,2,2,2,2,2,2,2,2,1,
		1,3,3,3,3,3,3,3,8,8,2,2,2,2,2,2,2,2,1,
		1,3,3,3,3,3,3,3,8,8,2,2,2,2,7,2,2,2,1,
		1,3,3,3,3,3,3,3,8,8,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,6,2,2,2,2,2,4,2,2,2,8,3,3,3,3,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,8,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,8,2,2,2,2,1,
		1,4,2,2,2,2,2,2,2,2,2,2,2,8,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 5 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 5 * BLOCKSIZE + BLOCKSIZE / 2;

	// 相棒の座標
	go->buddy.Pos.x = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の座標
	go->enemy[0].Pos.x = 15 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].IsAlive = true;


}

void stage1(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,1,1,
		1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,
		1,1,4,2,2,2,2,2,2,5,2,2,2,2,2,2,4,1,1,
		1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,
		1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,
		1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 7 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

	// 相棒の座標
	go->buddy.Pos.x = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 8 * BLOCKSIZE + BLOCKSIZE / 2;

}


void stage2(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,1,
		1,1,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,1,
		1,1,1,1,1,1,1,1,1,1,1,8,8,8,1,1,1,1,1,
		1,1,2,2,2,4,2,2,2,2,2,3,3,3,4,2,2,1,1,
		1,1,2,2,2,2,2,2,2,2,2,3,3,3,2,2,5,1,1,
		1,1,2,2,2,2,2,2,2,4,2,3,3,3,2,2,2,1,1,
		1,1,1,1,1,1,1,1,1,1,1,8,8,8,1,1,1,1,1,
		1,1,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,1,
		1,1,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 4 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 8 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 6 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

}

void stage3(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,5,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,3,4,3,3,3,1,
		1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,1,
		1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,1,
		1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,1,
		1,2,2,2,2,2,2,2,2,3,4,3,3,3,3,3,3,3,1,
		1,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,1,
		1,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,4,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 5 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 1 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

}

void stage4(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,2,1,
		1,2,2,2,2,2,1,1,2,4,2,1,1,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,4,2,5,2,4,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,1,1,2,2,2,1,1,2,2,2,2,2,1,
		1,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 5 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

}

void stage5(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,3,3,3,2,4,2,3,3,3,2,2,2,3,3,3,1,1,
		1,1,3,3,3,2,2,2,3,3,3,2,2,2,3,3,3,1,1,
		1,1,3,3,3,2,2,2,3,3,3,2,2,2,3,3,3,1,1,
		1,1,2,2,2,3,3,3,2,2,2,3,3,3,2,2,2,1,1,
		1,1,2,2,2,3,3,3,2,4,2,3,3,3,2,5,2,1,1,
		1,1,2,2,2,3,3,3,2,2,2,3,3,3,2,2,2,1,1,
		1,1,3,3,3,2,2,2,3,3,3,2,4,2,3,3,3,1,1,
		1,1,3,3,3,2,2,2,3,3,3,2,2,2,3,3,3,1,1,
		1,1,3,3,3,2,2,2,3,3,3,2,2,2,3,3,3,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 7 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 5 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 4 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 6 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}
}

void stage6(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,3,3,2,2,2,2,2,3,3,3,4,2,2,2,2,3,3,1,
		1,3,3,2,2,2,2,2,3,3,3,2,2,2,2,2,3,3,1,
		1,3,3,2,2,2,2,2,3,3,3,2,2,2,2,2,3,3,1,
		1,3,3,2,2,2,2,2,3,3,3,2,2,2,2,2,3,3,1,
		1,3,3,2,2,2,2,2,3,3,3,2,2,2,2,2,3,3,1,
		1,3,3,2,2,2,2,2,3,3,3,2,2,2,5,2,3,3,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 5 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 4 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 8 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

	// 敵の座標
	go->enemy[0].Pos.x = 12 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].Pos.y = 8 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].IsAlive = true;

}

void stage7(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,5,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 5 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

	// 敵の座標
	go->enemy[0].Pos.x = 17 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].Pos.y = 5 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].gravity = RIGHT;
	go->enemy[0].IsAlive = true;

	go->enemy[1].Pos.x = 4 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[1].Pos.y = 1 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[1].gravity = UP;
	go->enemy[1].IsAlive = true;

}

void stage8(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,3,3,3,2,4,2,3,3,3,2,2,2,3,3,3,1,1,
		1,1,3,3,3,2,2,2,3,3,3,2,2,2,3,3,3,1,1,
		1,1,3,3,3,2,2,2,3,3,3,2,2,2,3,3,3,1,1,
		1,1,2,2,2,3,3,3,2,2,2,3,3,3,2,2,2,1,1,
		1,1,2,2,2,3,3,3,2,4,2,3,3,3,2,5,2,1,1,
		1,1,2,2,2,3,3,3,2,2,2,3,3,3,2,2,2,1,1,
		1,1,3,3,3,2,2,2,3,3,3,2,4,2,3,3,3,1,1,
		1,1,3,3,3,2,2,2,3,3,3,2,2,2,3,3,3,1,1,
		1,1,3,3,3,2,2,2,3,3,3,2,2,2,3,3,3,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 7 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 5 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 4 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 6 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

	// 敵の座標
	go->enemy[0].Pos.x = 5 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].Pos.y = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].IsAlive = true;

	//go->enemy[1].Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	//go->enemy[1].Pos.y = 6 * BLOCKSIZE + BLOCKSIZE / 2;
	//go->enemy[1].IsAlive = true;

	go->enemy[2].Pos.x = 13 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[2].Pos.y = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[2].IsAlive = true;

}



void stage9(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,2,2,2,2,2,2,5,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,
		1,2,2,2,3,3,3,2,2,2,2,2,3,3,3,4,2,2,1,
		1,2,2,2,3,3,3,2,2,2,2,2,3,3,3,2,2,2,1,
		1,2,2,4,3,3,3,2,2,2,2,2,3,3,3,2,2,2,1,
		1,3,3,3,1,1,1,1,1,1,1,1,1,1,1,3,3,3,1,
		1,3,3,3,2,2,2,2,3,3,3,2,2,2,2,3,3,3,1,
		1,3,3,3,2,2,2,2,3,3,3,2,2,2,2,3,3,3,1,
		1,3,3,3,2,2,2,2,3,4,3,2,2,2,2,3,3,3,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 4 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 6 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

	// 敵の座標
	go->enemy[0].Pos.x = 1 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].Pos.y = 1 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].gravity = UP;

	go->enemy[1].Pos.x = 14 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[1].Pos.y = 8 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[1].gravity = UP;

	for (int i = 0; i < 2; ++i) {
		go->enemy[i].IsAlive = true;
	}

}

void stage10(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,3,3,3,3,3,4,6,8,8,8,3,2,2,5,2,2,3,1,
		1,3,3,3,3,3,2,2,8,8,8,3,2,2,2,2,2,3,1,
		1,3,3,3,3,3,3,3,8,8,8,3,2,2,2,2,2,3,1,
		1,3,3,3,3,3,3,3,8,8,8,3,2,2,2,2,2,3,1,
		1,3,3,4,3,3,3,3,8,8,8,3,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,3,8,8,8,3,3,3,3,3,4,3,1,
		1,3,2,2,2,2,2,3,8,8,8,3,3,3,3,3,3,3,1,
		1,3,2,2,2,2,2,3,8,8,8,3,3,3,3,3,3,3,1,
		1,3,2,2,2,2,2,3,8,8,8,2,2,3,3,3,3,3,1,
		1,3,2,2,2,2,2,3,8,8,8,7,2,3,3,3,3,3,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 5 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 4 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

}

void stage11(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,3,3,3,3,2,3,3,3,3,4,3,3,3,3,3,3,3,1,
		1,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,2,3,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,3,2,3,3,5,3,3,3,3,3,3,1,
		1,3,3,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,3,3,3,3,2,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,3,3,2,3,3,3,3,3,3,3,3,3,3,3,2,3,3,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 5 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 6 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 6 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

	// 敵の座標
	go->enemy[0].Pos.x = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;

	go->enemy[1].Pos.x = 5 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[1].Pos.y = 1 * BLOCKSIZE + BLOCKSIZE / 2;

	go->enemy[2].Pos.x = 8 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[2].Pos.y = 5 * BLOCKSIZE + BLOCKSIZE / 2;

	//go->enemy[3].Pos.x = 11 * BLOCKSIZE + BLOCKSIZE / 2;
	//go->enemy[3].Pos.y = 2 * BLOCKSIZE + BLOCKSIZE / 2;

	go->enemy[3].Pos.x = 11 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[3].Pos.y = 7 * BLOCKSIZE + BLOCKSIZE / 2;

	//go->enemy[5].Pos.x = 14 * BLOCKSIZE + BLOCKSIZE / 2;
	//go->enemy[5].Pos.y = 6 * BLOCKSIZE + BLOCKSIZE / 2;

	go->enemy[4].Pos.x = 15 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[4].Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;

	go->enemy[5].Pos.x = 16 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[5].Pos.y = 2 * BLOCKSIZE + BLOCKSIZE / 2;

	for (int i = 0; i < 6; ++i) {
		go->enemy[i].IsAlive = true;
	}


}

void stage12(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,2,2,2,2,1,2,5,2,1,2,2,3,3,2,2,1,
		1,2,2,2,2,2,2,1,2,2,2,1,2,2,3,3,2,2,1,
		1,3,3,3,3,2,2,1,2,7,2,1,2,2,3,3,2,2,1,
		1,3,3,3,3,2,2,1,1,1,1,1,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,4,2,2,2,2,2,6,2,2,2,2,2,4,2,2,1,
		1,2,2,2,2,2,2,2,2,4,2,2,2,2,3,3,3,3,1,
		1,2,2,3,3,2,2,3,3,3,3,3,2,2,3,3,3,3,1,
		1,2,2,3,3,2,2,3,2,2,2,3,2,2,2,2,2,2,1,
		1,2,2,3,3,2,2,3,2,2,2,3,2,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 7 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

}

void stage13(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,4,8,3,3,3,3,8,2,2,2,2,3,3,3,3,3,3,1,
		1,3,8,3,8,3,3,2,2,5,2,2,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,2,2,2,2,2,8,3,3,3,8,3,1,
		1,3,3,3,3,8,8,8,8,8,8,8,8,8,3,3,3,3,1,
		1,3,3,3,3,2,2,2,2,2,2,2,2,2,3,3,3,3,1,
		1,3,3,3,3,2,2,2,2,2,2,2,2,2,3,3,3,3,1,
		1,3,3,3,3,8,8,8,8,8,8,8,8,8,3,3,3,3,1,
		1,3,8,3,3,3,3,3,3,4,3,8,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,8,3,8,3,1,
		1,3,3,3,3,8,3,3,3,3,3,3,3,3,3,3,8,4,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 10 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 6 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 6 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 6 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

	// 敵の座標
	go->enemy[0].Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].Pos.y = 8 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].IsAlive = true;

}

void stage14(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,2,2,2,2,2,2,8,2,2,2,2,2,2,2,2,1,
		1,2,4,2,2,2,2,2,2,8,2,4,2,2,2,2,5,2,1,
		1,2,2,2,2,2,2,2,2,8,2,2,2,2,2,2,2,2,1,
		1,8,8,8,8,2,2,2,2,8,2,2,2,2,8,8,8,8,1,
		1,2,2,2,2,2,2,2,2,8,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,8,2,2,2,2,2,2,4,2,1,
		1,2,2,2,2,8,8,8,8,8,8,8,8,8,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,8,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,8,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,6,8,7,2,2,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 6 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 2 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 1 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 3 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

	// 敵の座標
	go->enemy[0].Pos.x = 17 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].Pos.y = 2 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].IsAlive = true;

	go->enemy[1].Pos.x = 2 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[1].Pos.y = 8 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[1].IsAlive = true;

}

void stage15(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,2,3,3,3,1,2,2,2,3,3,3,3,3,2,2,1,
		1,2,2,2,3,3,3,1,2,2,2,3,3,3,3,3,2,2,1,
		1,2,2,4,3,3,3,1,2,2,2,3,3,3,3,3,4,2,1,
		1,1,1,1,3,3,3,1,3,3,3,1,2,2,2,1,3,3,1,
		1,2,2,6,2,2,2,2,3,3,3,1,2,2,2,1,3,3,1,
		1,2,2,2,2,2,2,2,3,3,3,1,2,5,2,1,3,3,1,
		1,2,2,2,2,2,2,2,3,3,3,1,1,1,1,1,3,3,1,
		1,2,2,1,1,1,2,2,3,3,3,8,7,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,3,3,3,8,2,2,4,2,2,2,1,
		1,2,2,2,2,2,2,2,3,3,3,8,2,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			go->MapChip[i][j].Map = map[i][j];

			// マップ番号が3ならIsPaintをtrueにする
			if (go->MapChip[i][j].Map == 3) {
				go->MapChip[i][j].IsPaint = true;
			} else {
				go->MapChip[i][j].IsPaint = false;
			}

			// 星の取得状況をリセット
			if (go->MapChip[i][j].Map == 4) {
				go->MapChip[i][j].star.isGet = false;
			}

		}
	}

	// プレイヤーの座標
	go->player.Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->player.Pos.y = 6 * BLOCKSIZE + BLOCKSIZE / 2;

	go->player.virtualPos = go->player.Pos;
	go->player.PrePos = go->player.Pos;
	go->player.MoveCoolTime = 0;
	go->player.MoveFlag = false;

	// 相棒の座標
	go->buddy.Pos.x = 9 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 3 * BLOCKSIZE + BLOCKSIZE / 2;

	// 敵の初期化
	for (int i = 0; i < 10; ++i) {
		go->enemy[i].IsAlive = true;
		go->enemy[i].Pos.x = 0.0f;
		go->enemy[i].Pos.y = 0.0f;
	}

	// 敵の座標
	go->enemy[0].Pos.x = 1 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].Pos.y = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[0].IsAlive = true;

	// 敵の座標
	go->enemy[1].Pos.x = 6 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[1].Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[1].IsAlive = true;

	// 敵の座標
	go->enemy[2].Pos.x = 12 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[2].Pos.y = 4 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[2].IsAlive = true;
	go->enemy[2].gravity = LEFT;


	// 敵の座標
	go->enemy[3].Pos.x = 16 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[3].Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;
	go->enemy[3].IsAlive = true;

}


void StageGenerate(GameObject* go, System* system) {
	if (system->stageselect.select == 1) {
		stage1(go);
	} else if (system->stageselect.select == 2) {
		stage2(go);
	} else if (system->stageselect.select == 3) {
		stage3(go);
	} else if (system->stageselect.select == 4) {
		stage4(go);
	} else if (system->stageselect.select == 5) {
		stage5(go);
	} else if (system->stageselect.select == 6) {
		stage6(go);
	} else if (system->stageselect.select == 7) {
		stage7(go);
	} else if (system->stageselect.select == 8) {
		stage8(go);
	} else if (system->stageselect.select == 9) {
		stage9(go);
	} else if (system->stageselect.select == 10) {
		stage10(go);
	} else if (system->stageselect.select == 11) {
		stage11(go);
	} else if (system->stageselect.select == 12) {
		stage12(go);
	} else if (system->stageselect.select == 13) {
		stage13(go);
	} else if (system->stageselect.select == 14) {
		stage14(go);
	} else if (system->stageselect.select == 15) {
		stage15(go);
	}
}


// 最初からあったデバッグ用マップのコピー
/*
int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
*/

// 2個めのデバッグ用マップのコピー
/*
int map[VerBlockNum][HolBlockNum] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,0,
		0,0,2,1,1,1,1,1,1,0,1,1,1,1,1,1,2,0,0,
		0,0,2,1,2,2,2,2,2,0,2,2,2,2,2,1,2,0,0,
		0,0,2,1,2,0,0,0,0,0,0,0,0,0,2,1,2,0,0,
		0,0,2,1,2,0,0,0,0,0,0,0,0,0,2,1,2,0,0,
		0,0,2,1,2,2,2,2,2,0,2,2,2,2,2,1,2,0,0,
		0,0,2,1,1,1,1,1,1,0,1,1,1,1,1,1,2,0,0,
		0,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
*/

// 3個めのデバッグ用マップのコピー
/*
int map[VerBlockNum][HolBlockNum] = {
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,2,1,2,2,2,2,0,2,2,2,2,0,2,0,0,0,
		0,0,0,2,2,2,2,0,2,0,2,0,2,2,2,2,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,2,1,0,2,1,2,0,0,2,2,0,1,2,0,0,0,
		0,0,0,2,2,0,2,2,0,0,2,1,2,0,2,2,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,2,2,2,2,0,2,0,2,0,2,2,2,2,0,0,0,
		0,0,0,2,0,2,2,2,2,0,2,2,2,2,1,2,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};
*/

// 4個めのデバッグ用マップのコピー
/*
int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,2,0,1,
		1,0,0,0,0,0,2,0,0,0,0,0,2,0,2,2,0,0,1,
		1,0,0,0,2,2,0,2,0,0,0,0,0,2,0,0,0,0,1,
		1,0,0,2,0,2,0,0,0,0,0,0,0,0,2,0,2,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};
*/

// 5個めのデバッグ用マップのコピー
/*
int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,
		1,2,0,2,0,2,2,2,2,1,1,2,2,2,0,2,0,2,1,
		1,2,0,1,2,1,1,1,1,1,1,1,1,1,2,1,0,2,1,
		1,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,1,
		1,2,0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,2,1,
		1,2,0,0,0,0,0,0,2,0,2,0,0,0,0,0,0,2,1,
		1,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};
*/

// 連動ブロックのコース1
/*
int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,2,3,2,2,3,3,2,1,1,1,1,1,
		1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
		1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1,
		1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,
		1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,
		1,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,1,
		1,1,1,1,1,1,1,1,2,2,3,2,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};
*/

// 連動ブロックのコース2
/*
int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
		1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
		1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,
		1,4,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,4,1,
		1,1,1,0,0,0,0,1,2,1,4,1,0,0,0,0,0,2,1,
		1,2,0,0,0,0,0,5,2,1,2,5,0,0,0,0,1,1,1,
		1,4,0,0,0,0,0,1,2,1,2,1,0,0,0,0,0,2,1,
		1,2,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,2,1,
		1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,
		1,1,1,0,0,0,0,0,0,0,0,0,0,0,2,3,2,3,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};
*/

// 相棒追加後のステージ案1
/*
int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,3,3,3,3,3,3,3,3,3,3,2,2,2,2,5,1,
		1,2,2,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,1,
		1,3,3,3,3,3,3,3,3,7,3,3,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,
		1,3,3,3,3,3,3,2,2,2,2,2,2,3,3,3,3,3,1,
		1,3,3,3,3,3,3,2,2,2,4,2,2,3,3,3,3,3,1,
		1,3,3,3,3,3,3,2,2,2,2,2,2,3,3,3,3,3,1,
		1,3,6,3,3,3,3,2,2,2,2,2,2,3,3,3,2,2,1,
		1,3,3,3,3,3,3,2,2,2,2,2,2,3,3,3,2,4,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};
*/


//ステージ情報を書き換える関数
//void StageGenerate(GameObject* go, System* system) {

	//テストプレイ用


//}

//ゲームプレイ中の初期化
//void StageGameInitialize(GameObject* go) {
//
//}

//ステージの描画
void StageDraw(GameObject* go) {

	// ステージ背景の描画処理
	Novice::DrawBox(0, 0, WindowWidth, WindowHeight, 0.0f, 0x808080FF, kFillModeSolid);

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {

			if (go->MapChip[i][j].Map == 1) {
				Novice::DrawQuad(
					//左上
					int(go->MapChip[i][j].DrawLeftTop.x),
					int(go->MapChip[i][j].DrawLeftTop.y),

					//右上
					int(go->MapChip[i][j].DrawRightTop.x),
					int(go->MapChip[i][j].DrawRightTop.y),

					//左下
					int(go->MapChip[i][j].DrawLeftBottom.x),
					int(go->MapChip[i][j].DrawLeftBottom.y),

					//右下
					int(go->MapChip[i][j].DrawRightBottom.x),
					int(go->MapChip[i][j].DrawRightBottom.y),

					//画像上の座標
					64, 0,

					//横幅、縦幅
					64, 64,

					//テクスチャハンドル
					go->MapChip[0][0].image,

					//色
					go->MapChip[0][0].color
				);

			} else if (go->MapChip[i][j].Map == 2 || go->MapChip[i][j].Map == 3) {

				Novice::DrawQuad(
					//左上
					int(go->MapChip[i][j].Pos.x + go->MapChip[i][j].BufRotateLeftTop.x),
					int(go->MapChip[i][j].Pos.y + go->MapChip[i][j].BufRotateLeftTop.y),

					//右上
					int(go->MapChip[i][j].Pos.x + go->MapChip[i][j].BufRotateRightTop.x),
					int(go->MapChip[i][j].Pos.y + go->MapChip[i][j].BufRotateRightTop.y),

					//左下
					int(go->MapChip[i][j].Pos.x + go->MapChip[i][j].BufRotateLeftBottom.x),
					int(go->MapChip[i][j].Pos.y + go->MapChip[i][j].BufRotateLeftBottom.y),

					//右下
					int(go->MapChip[i][j].Pos.x + go->MapChip[i][j].BufRotateRightBottom.x),
					int(go->MapChip[i][j].Pos.y + go->MapChip[i][j].BufRotateRightBottom.y),

					//画像上の座標
					64 * go->MapChip[i][j].Map, 0,

					//横幅、縦幅
					64, 64,

					//テクスチャハンドル
					go->MapChip[0][0].image,

					//色
					go->MapChip[0][0].color
				);

			} else if (go->MapChip[i][j].Map == 4) {

				// 星が取られていなければ
				if (!go->MapChip[i][j].star.isGet) {

					Novice::DrawQuad(
						//左上
						int(go->MapChip[i][j].DrawLeftTop.x),
						int(go->MapChip[i][j].DrawLeftTop.y),

						//右上
						int(go->MapChip[i][j].DrawRightTop.x),
						int(go->MapChip[i][j].DrawRightTop.y),

						//左下
						int(go->MapChip[i][j].DrawLeftBottom.x),
						int(go->MapChip[i][j].DrawLeftBottom.y),

						//右下
						int(go->MapChip[i][j].DrawRightBottom.x),
						int(go->MapChip[i][j].DrawRightBottom.y),

						//画像上の座標
						64 * go->MapChip[i][j].star.animCount, 0,

						//横幅、縦幅
						64, 64,

						//テクスチャハンドル
						go->MapChip[0][1].image,

						//色
						go->MapChip[0][0].color
					);

				} else {

					// フレームカウントが60未満なら
					if (go->MapChip[i][j].star.frameCount < 59) {

						Novice::DrawQuad(
							//左上
							int(go->MapChip[i][j].DrawLeftTop.x - BLOCKSIZE / 2),
							int(go->MapChip[i][j].DrawLeftTop.y - BLOCKSIZE / 2),

							//右上
							int(go->MapChip[i][j].DrawRightTop.x + BLOCKSIZE / 2),
							int(go->MapChip[i][j].DrawRightTop.y - BLOCKSIZE / 2),

							//左下
							int(go->MapChip[i][j].DrawLeftBottom.x - BLOCKSIZE / 2),
							int(go->MapChip[i][j].DrawLeftBottom.y + BLOCKSIZE / 2),

							//右下
							int(go->MapChip[i][j].DrawRightBottom.x + BLOCKSIZE / 2),
							int(go->MapChip[i][j].DrawRightBottom.y + BLOCKSIZE / 2),

							//画像上の座標
							128 * go->MapChip[i][j].star.animCount, 0,

							//横幅、縦幅
							128, 128,

							//テクスチャハンドル
							go->MapChip[0][1].star.gotEffectImage,

							//色
							go->MapChip[0][0].color
						);

					}

				}

			} else if (go->MapChip[i][j].Map == 5) {

				Novice::DrawQuad(
					//左上
					int(go->MapChip[i][j].DrawLeftTop.x),
					int(go->MapChip[i][j].DrawLeftTop.y),

					//右上
					int(go->MapChip[i][j].DrawRightTop.x),
					int(go->MapChip[i][j].DrawRightTop.y),

					//左下
					int(go->MapChip[i][j].DrawLeftBottom.x),
					int(go->MapChip[i][j].DrawLeftBottom.y),

					//右下
					int(go->MapChip[i][j].DrawRightBottom.x),
					int(go->MapChip[i][j].DrawRightBottom.y),

					//画像上の座標
					64 * go->MapChip[i][j].goal.animCount, 0,

					//横幅、縦幅
					64, 64,

					//テクスチャハンドル
					go->MapChip[0][3].image,

					//色
					go->MapChip[0][0].color
				);

			} else if (go->MapChip[i][j].Map == 6 || go->MapChip[i][j].Map == 7) {

				if (go->buddy.warpCoolTime <= 0) {

					Novice::DrawQuad(
						//左上
						int(go->MapChip[i][j].DrawLeftTop.x),
						int(go->MapChip[i][j].DrawLeftTop.y),

						//右上
						int(go->MapChip[i][j].DrawRightTop.x),
						int(go->MapChip[i][j].DrawRightTop.y),

						//左下
						int(go->MapChip[i][j].DrawLeftBottom.x),
						int(go->MapChip[i][j].DrawLeftBottom.y),

						//右下
						int(go->MapChip[i][j].DrawRightBottom.x),
						int(go->MapChip[i][j].DrawRightBottom.y),

						//画像上の座標
						64 * go->MapChip[i][j].wbg.animCount, 0,

						//横幅、縦幅
						64, 64,

						//テクスチャハンドル
						go->MapChip[0][2].image,

						//色
						go->MapChip[0][0].color
					);

				} else {

					Novice::DrawQuad(
						//左上
						int(go->MapChip[i][j].DrawLeftTop.x),
						int(go->MapChip[i][j].DrawLeftTop.y),

						//右上
						int(go->MapChip[i][j].DrawRightTop.x),
						int(go->MapChip[i][j].DrawRightTop.y),

						//左下
						int(go->MapChip[i][j].DrawLeftBottom.x),
						int(go->MapChip[i][j].DrawLeftBottom.y),

						//右下
						int(go->MapChip[i][j].DrawRightBottom.x),
						int(go->MapChip[i][j].DrawRightBottom.y),

						//画像上の座標
						64 * go->MapChip[i][j].wbg.animCount, 0,

						//横幅、縦幅
						64, 64,

						//テクスチャハンドル
						go->MapChip[0][4].image,

						//色
						go->MapChip[0][0].color
					);

				}

			} else if (go->MapChip[i][j].Map == 8) {

				Novice::DrawQuad(
					//左上
					int(go->MapChip[i][j].DrawLeftTop.x),
					int(go->MapChip[i][j].DrawLeftTop.y),

					//右上
					int(go->MapChip[i][j].DrawRightTop.x),
					int(go->MapChip[i][j].DrawRightTop.y),

					//左下
					int(go->MapChip[i][j].DrawLeftBottom.x),
					int(go->MapChip[i][j].DrawLeftBottom.y),

					//右下
					int(go->MapChip[i][j].DrawRightBottom.x),
					int(go->MapChip[i][j].DrawRightBottom.y),

					//画像上の座標
					0, 0,

					//横幅、縦幅
					64, 64,

					//テクスチャハンドル
					go->MapChip[0][5].image,

					//色
					go->MapChip[0][0].color
				);

			}

		}
	}
}

//ブロックのアニメーション（選択したとき）の角度を制御する関数

void BlockAnimationAngleControl(GameObject* go, int y, int x) {

	//振れ幅の変更処理
	go->MapChip[y][x].ShakeWidth = go->MapChip[y][x].ShakeWidth - (go->MapChip[y][x].ShakeNum * 4);

	//フラグの管理
	if (go->MapChip[y][x].degree < -(go->MapChip[y][x].ShakeWidth)) {
		go->MapChip[y][x].IncreaseFlag = true;
		go->MapChip[y][x].DecreaseFlag = false;
	}
	if (go->MapChip[y][x].degree > go->MapChip[y][x].ShakeWidth) {
		go->MapChip[y][x].DecreaseFlag = true;
		go->MapChip[y][x].IncreaseFlag = false;
		go->MapChip[y][x].ShakeNum++;
	}

	//角度の増減
	if (go->MapChip[y][x].Map == 2 || go->MapChip[y][x].Map == 3) {

		if (go->player.select[y][x] && go->MapChip[y][x].ShakeNum <= 4) {
			if (go->MapChip[y][x].IncreaseFlag) {
				go->MapChip[y][x].degree += 4;
			}

			if (go->MapChip[y][x].DecreaseFlag) {
				go->MapChip[y][x].degree -= 4;
			}
		} else {
			go->MapChip[y][x].degree = 0.0f;
		}
	} else {
		go->MapChip[y][x].degree = 0.0f;
		go->MapChip[y][x].theta = 0.0f;
	}

	//角度の変換
	go->MapChip[y][x].theta = (go->MapChip[y][x].degree / 180.0f) * 3.1415f;


}


void NewBlockAnimetion(GameObject* go, int y, int x) {

	if (!go->buddy.IsClear) {

		//プレイヤーが選択しているブロックならば
		if (go->player.select[y][x]) {

			//角度を増減させるフラグが立っていなければ
			if (!go->MapChip[y][x].IncreaseFlag && !go->MapChip[y][x].DecreaseFlag) {

				go->MapChip[y][x].IncreaseFlag = true;
				go->MapChip[y][x].DecreaseFlag = false;
			}

			if (go->MapChip[y][x].ShakeNum <= 2) {

				if (go->MapChip[y][x].IncreaseFlag) {
					go->MapChip[y][x].degree += 4;

					if (go->MapChip[y][x].degree > 8.0f) {
						go->MapChip[y][x].DecreaseFlag = true;
						go->MapChip[y][x].IncreaseFlag = false;

					}
				}
				if (go->MapChip[y][x].DecreaseFlag) {
					go->MapChip[y][x].degree -= 4;

					if (go->MapChip[y][x].degree < -8.0f) {

						go->MapChip[y][x].DecreaseFlag = false;
						go->MapChip[y][x].IncreaseFlag = true;

						go->MapChip[y][x].ShakeNum++;
					}

				}
			}
			else {
				go->MapChip[y][x].IncreaseFlag = false;
				go->MapChip[y][x].DecreaseFlag = false;

				go->MapChip[y][x].degree = 0.0f;

			}
		}
		//選択されていなければフラグをすべて折る
		else {
			go->MapChip[y][x].IncreaseFlag = false;
			go->MapChip[y][x].DecreaseFlag = false;

			go->MapChip[y][x].degree = 0.0f;
		}
	}
	//クリアシーンになったら
	else {
		go->MapChip[y][x].IncreaseFlag = false;
		go->MapChip[y][x].DecreaseFlag = false;

		go->MapChip[y][x].degree = 0.0f;
		go->MapChip[y][x].theta = 0.0f;
	}

	//角度の変換
	go->MapChip[y][x].theta = (go->MapChip[y][x].degree / 180.0f) * 3.1415f;
}


/*
//キー入力でアニメーションの情報リセット
void InitializeBlockAnimation(GameObject* go, Key* key, int y, int x) {
	if (key->keys[DIK_W] || key->keys[DIK_A] || key->keys[DIK_S] || key->keys[DIK_D]) {
		for (int i = 0; i < VerBlockNum; i++) {
			for (int j = 0; j < HolBlockNum; j++) {


	//角度の変換
	go->MapChip[y][x].theta = (go->MapChip[y][x].degree / 180.0f) * 3.1415f;

}
*/


//キー入力でアニメーションの情報リセット
void InitializeBlockAnimation(GameObject* go, Key* key, int y, int x) {
	if (key->keys[DIK_W] || key->keys[DIK_A] || key->keys[DIK_S] || key->keys[DIK_D]) {
		for (int i = 0; i < VerBlockNum; i++) {
			for (int j = 0; j < HolBlockNum; j++) {

				go->MapChip[y][x].ShakeNum = 0;
				go->MapChip[y][x].degree = 0.0f;
				go->MapChip[y][x].theta = 0.0f;
			}
		}
	}
}


//ブロックのアニメーション関数
//回転で振動させる
void BlockAnimation(GameObject* go, Key* key) {

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {

			//選択されているブロック振動（回転）

				//角度の増減・変換
			//BlockAnimationAngleControl(go, i, j);

			if (go->MapChip[i][j].Map == 2 || go->MapChip[i][j].Map == 3) {
				NewBlockAnimetion(go, i, j);

				MakeRotatePos(&go->MapChip[i][j]);

				InitializeBlockAnimation(go, key, i, j);
			}
		}
	}
}