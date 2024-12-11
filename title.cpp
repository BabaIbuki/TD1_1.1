#include <Novice.h>
#include"structer.h"
#include"enum.h"


// タイトルを初期化する関数
void TitleInitialize(GameObject* go, System* system) {

	// タイトルの画像の変数
	system->titleImage = Novice::LoadTexture("./MyResources/Title.png");

	// 相棒の位置の初期化
	go->buddy.Pos.x = 3 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;

	// ブロックの画像の変数
	go->MapChip[0][0].image = Novice::LoadTexture("./MyResources./Block.png");

	// 操作方法の画像の変数
	system->titleUIImage = Novice::LoadTexture("./MyResources/TitleUI.png");

}

// タイトルの処理の関数
void TitleScene(Key* key, System* system) {

	// Jキーが押されていたら
	if (key->keys[DIK_J] != 0 && key->preKeys[DIK_J] == 0) {
		// シーンを切り替える
		system->sc.changeFlag = true;

	}
	if (system->sc.changeFlag && system->sc.Pos[3].x == 0.0f) {
		system->scene = StageSelect;
		system->sc.changeFlag = false;
	}

}

// タイトルのステージ情報の関数
void TitleStage(GameObject* go) {
	int map[VerBlockNum][HolBlockNum] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,1,
		1,2,2,3,2,2,2,2,2,2,2,2,2,2,2,3,2,2,1,
		1,2,2,3,2,2,2,2,2,2,2,2,2,2,2,3,2,2,1,
		1,2,2,3,2,2,2,2,2,2,2,2,2,2,2,3,2,2,1,
		1,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
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
			}

		}
	}
}

// タイトルの描画の関数
void TitleDraw(System* system, GameObject* go) {

	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {

			if (go->MapChip[i][j].Map == 1 || go->MapChip[i][j].Map == 2 || go->MapChip[i][j].Map == 3) {

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
					64 * go->MapChip[i][j].Map, 0,

					//横幅、縦幅
					64, 64,

					//テクスチャハンドル
					go->MapChip[0][0].image,

					//色
					go->MapChip[0][0].color
				);

			}
		}
	}

	// タイトルの文字の画像を描画
	Novice::DrawQuad(
		//左上
		4 * BLOCKSIZE,
		3 * BLOCKSIZE,

		//右上
		15 * BLOCKSIZE,
		3 * BLOCKSIZE,

		//左下
		4 * BLOCKSIZE,
		6 * BLOCKSIZE,

		//右下
		15 * BLOCKSIZE,
		6 * BLOCKSIZE,

		//画像上の座標
		0, 0,

		//横幅、縦幅
		704, 192,

		//テクスチャハンドル
		system->titleImage,

		//色
		WHITE

	);

	// タイトルのUIの画像を描画
	Novice::DrawQuad(
		//左上
		5 * BLOCKSIZE,
		8 * BLOCKSIZE,

		//右上
		14 * BLOCKSIZE,
		8 * BLOCKSIZE,

		//左下
		5 * BLOCKSIZE,
		9 * BLOCKSIZE,

		//右下
		14 * BLOCKSIZE,
		9 * BLOCKSIZE,

		//画像上の座標
		0, 0,

		//横幅、縦幅
		640, 64,

		//テクスチャハンドル
		system->titleUIImage,

		//色
		WHITE

	);

}