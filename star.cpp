//ソースファイルの読み込み
#include<Novice.h>

//ヘッダーファイルの読み込み
#include"structer.h"
#include"common.h"
#include"enum.h"


//最初に読み込む相棒の初期化の関数
void StarInitialize(GameObject* go) {

	for (int i = 0; i < 3; ++i) {

		go->star[i].Pos.x = 0 * BLOCKSIZE + BLOCKSIZE / 2;
		go->star[i].Pos.y = 0 * BLOCKSIZE + BLOCKSIZE / 2;

		//サイズの初期化
		go->star[i].width = BLOCKSIZE;
		go->star[i].height = BLOCKSIZE;

		//画像関連
		go->star[0].image = Novice::LoadTexture("./MyResources./Star.png");
		go->star[0].color = WHITE;

		go->star[i].IsAlive = true;

		// 相棒のアニメーションに使う変数
		go->star[i].frameCount = 0;
		go->star[i].animCount = 0;

	}

	go->star[0].Pos.x = 1 * BLOCKSIZE + BLOCKSIZE / 2;
	go->star[0].Pos.y = 2 * BLOCKSIZE + BLOCKSIZE / 2;

	go->star[1].Pos.x = 6 * BLOCKSIZE + BLOCKSIZE / 2;
	go->star[1].Pos.y = 7 * BLOCKSIZE + BLOCKSIZE / 2;

	go->star[2].Pos.x = 17 * BLOCKSIZE + BLOCKSIZE / 2;
	go->star[2].Pos.y = 8 * BLOCKSIZE + BLOCKSIZE / 2;

}

//ゲームプレイ中の初期化
//void PlayerGameInitialize(GameObject* go) {
//
//}

//相棒の動きの関数（マップチップとの当たり判定も込みの可能性もあり）
void StarMove(GameObject* go) {

	for (int i = 0; i < 3; ++i) {

		// 星が取られていなければ
		if (go->star[i].IsAlive) {

			// 4頂点の判定を取る
			go->star[i].LeftTop.x = int(go->star[i].Pos.x - go->star[i].width / 2) / BLOCKSIZE;
			go->star[i].LeftTop.y = int(go->star[i].Pos.y - go->star[i].height / 2) / BLOCKSIZE;
			go->star[i].LeftBottom.x = int(go->star[i].Pos.x - go->star[i].width / 2) / BLOCKSIZE;
			go->star[i].LeftBottom.y = int(go->star[i].Pos.y + go->star[i].height / 2 - 1) / BLOCKSIZE;
			go->star[i].RightTop.x = int(go->star[i].Pos.x + go->star[i].width / 2 - 1) / BLOCKSIZE;
			go->star[i].RightTop.y = int(go->star[i].Pos.y - go->star[i].height / 2) / BLOCKSIZE;
			go->star[i].RightBottom.x = int(go->star[i].Pos.x + go->star[i].width / 2 - 1) / BLOCKSIZE;
			go->star[i].RightBottom.y = int(go->star[i].Pos.y + go->star[i].height / 2 - 1) / BLOCKSIZE;

			// 相棒が触れたら星の取得数を増やす
			if (go->buddy.Pos.x + go->buddy.width / 2.0f > go->star[i].Pos.x - go->star[i].width / 2.0f && go->buddy.Pos.x - go->buddy.width / 2.0f < go->star[i].Pos.x + go->star[i].width / 2.0f) {
				if (go->buddy.Pos.y + go->buddy.height / 2.0f > go->star[i].Pos.y - go->star[i].height / 2.0f && go->buddy.Pos.y - go->buddy.height / 2.0f < go->star[i].Pos.y + go->star[i].height / 2.0f) {

					go->star[i].IsAlive = false;
					go->buddy.starGetCount++;

				}
			}

		}

		// 相棒のアニメーションの処理
		if (go->star[i].frameCount < 59) {
			go->star[i].frameCount++;
		} else {
			go->star[i].frameCount = 0;
		}

		go->star[i].animCount = go->star[i].frameCount / 6;

	}

}


//相棒の描画
void StarDraw(GameObject* go) {

	for (int i = 0; i< 3; ++i) {

		// 星が取られていなくて
		if (go->star[i].IsAlive) {

			Novice::DrawQuad(
				//左上
				int(go->star[i].DrawLeftTop.x),
				int(go->star[i].DrawLeftTop.y),

				//右上
				int(go->star[i].DrawRightTop.x),
				int(go->star[i].DrawRightTop.y),

				//左下
				int(go->star[i].DrawLeftBottom.x),
				int(go->star[i].DrawLeftBottom.y),

				//右下
				int(go->star[i].DrawRightBottom.x),
				int(go->star[i].DrawRightBottom.y),

				//画像上の座標
				0 + 64 * go->star[i].animCount, 0,

				//横幅、縦幅
				64, 64,

				//テクスチャハンドル
				go->star[0].image,

				//色
				go->star[0].color
			);


			Novice::ScreenPrintf(16, 16 + 16 * i, "Star[%d] : isAlive %d Pos : X %0.1f  Y %0.1f  AnimCount %d", i,go->star[i].IsAlive,go->star[i].Pos.x,go->star[i].Pos.y,go->star[i].animCount);

		}

	}

}