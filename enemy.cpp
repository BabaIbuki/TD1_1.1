//ソースファイルの読み込み
#include<Novice.h>

//ヘッダーファイルの読み込み
#include"structer.h"
#include"common.h"
#include"enum.h"
#include"Audio.h"

//最初に読み込む敵の初期化の関数
void EnemyInitialize(GameObject* go) {

	for (int i = 0; i < 10; ++i) {

		go->enemy[i].Pos.x = 0 * BLOCKSIZE + BLOCKSIZE / 2;
		go->enemy[i].Pos.y = 0 * BLOCKSIZE + BLOCKSIZE / 2;

		go->enemy[i].Velocity.x = 0.0f;
		go->enemy[i].Velocity.y = 0.0f;

		go->enemy[i].Acceleration.x = 0.5f;
		go->enemy[i].Acceleration.y = 0.5f;

		go->enemy[i].speed = 3.0f;

		//サイズの初期化
		go->enemy[i].width = BLOCKSIZE;
		go->enemy[i].height = BLOCKSIZE;

		// 敵の重力の向き
		go->enemy[i].gravity = DOWN;

		go->enemy[i].IsGround = false;

		go->enemy[i].IsAlive = false;

		// 敵のアニメーションに使う変数
		go->enemy[i].frameCount = 0;
		go->enemy[i].animCount = 0;

	}

	//画像関連
	go->enemy[0].image = Novice::LoadTexture("./MyResources./enemy.png");
	go->enemy[0].color = WHITE;

}

void EnemyMoveGameInitialize(GameObject* go) {

	for (int i = 0; i < 10; ++i) {

		go->enemy[i].Velocity.x = 0.0f;
		go->enemy[i].Velocity.y = 0.0f;

		go->enemy[i].Acceleration.x = 0.5f;
		go->enemy[i].Acceleration.y = 0.5f;

		go->enemy[i].speed = 3.0f;

		//サイズの初期化
		go->enemy[i].width = BLOCKSIZE;
		go->enemy[i].height = BLOCKSIZE;

		// 敵の重力の向き
		go->enemy[i].gravity = DOWN;

		go->enemy[i].IsGround = false;

		go->enemy[i].IsAlive = false;

		// 敵のアニメーションに使う変数
		go->enemy[i].frameCount = 0;
		go->enemy[i].animCount = 0;

	}

}

//敵の動きの関数（マップチップとの当たり判定も込みの可能性もあり）
void EnemyMove(GameObject* go, Audio* audio) {

	for (int i = 0; i < 10; ++i) {

		// 敵が生きていたら
		if (go->enemy[i].IsAlive) {

			if (go->enemy[i].gravity == UP) {
				go->enemy[i].Acceleration.y = -0.5f;
				go->enemy[i].Pos.y += go->enemy[i].Velocity.y;
				go->enemy[i].Velocity.y += go->enemy[i].Acceleration.y;
				//すり抜けんな！すり抜けんな！すり抜けんな！現世(こっち)で遊ぼう１２３４
				if (go->enemy[i].Velocity.y < -10.0f) {
					go->enemy[i].Velocity.y = -10.0f;
				}
				go->enemy[i].Pos.y += go->enemy[i].Velocity.y;
			} else if (go->enemy[i].gravity == DOWN) {
				//重力処理！君に決めた！！！
				go->enemy[i].Acceleration.y = 0.5f;
				go->enemy[i].Pos.y += go->enemy[i].Velocity.y;
				go->enemy[i].Velocity.y += go->enemy[i].Acceleration.y;
				//すり抜けんな！すり抜けんな！すり抜けんな！現世(こっち)で遊ぼう１２３４
				if (go->enemy[i].Velocity.y > 10.0f) {
					go->enemy[i].Velocity.y = 10.0f;
				}
				go->enemy[i].Pos.y += go->enemy[i].Velocity.y;
			} else if (go->enemy[i].gravity == LEFT) {
				go->enemy[i].Acceleration.y = 0.0f;
				go->enemy[i].Velocity.y = 0.0f;
				// 敵を進ませる
				go->enemy[i].Pos.y += go->enemy[i].speed;
			} else if (go->enemy[i].gravity == RIGHT) {
				go->enemy[i].Acceleration.y = 0.0f;
				go->enemy[i].Velocity.y = 0.0f;
				// 敵を進ませる
				go->enemy[i].Pos.y -= go->enemy[i].speed;
			}

			go->enemy[i].LeftTop.x = int(go->enemy[i].Pos.x - go->enemy[i].width / 2) / BLOCKSIZE;
			go->enemy[i].LeftTop.y = int(go->enemy[i].Pos.y - go->enemy[i].height / 2) / BLOCKSIZE;
			go->enemy[i].LeftBottom.x = int(go->enemy[i].Pos.x - go->enemy[i].width / 2) / BLOCKSIZE;
			go->enemy[i].LeftBottom.y = int(go->enemy[i].Pos.y + go->enemy[i].height / 2 - 1) / BLOCKSIZE;
			go->enemy[i].RightTop.x = int(go->enemy[i].Pos.x + go->enemy[i].width / 2 - 1) / BLOCKSIZE;
			go->enemy[i].RightTop.y = int(go->enemy[i].Pos.y - go->enemy[i].height / 2) / BLOCKSIZE;
			go->enemy[i].RightBottom.x = int(go->enemy[i].Pos.x + go->enemy[i].width / 2 - 1) / BLOCKSIZE;
			go->enemy[i].RightBottom.y = int(go->enemy[i].Pos.y + go->enemy[i].height / 2 - 1) / BLOCKSIZE;

			//上下の判定を取って戻す
			if (go->MapChip[go->enemy[i].LeftTop.y][go->enemy[i].LeftTop.x].Map == 1 || go->MapChip[go->enemy[i].RightTop.y][go->enemy[i].RightTop.x].Map == 1
				|| go->MapChip[go->enemy[i].LeftTop.y][go->enemy[i].LeftTop.x].Map == 3 || go->MapChip[go->enemy[i].RightTop.y][go->enemy[i].RightTop.x].Map == 3
				|| go->MapChip[go->enemy[i].LeftTop.y][go->enemy[i].LeftTop.x].Map == 8 || go->MapChip[go->enemy[i].RightTop.y][go->enemy[i].RightTop.x].Map == 8) {
				go->enemy[i].Pos.y = float((go->enemy[i].LeftTop.y + 1) * BLOCKSIZE + go->enemy[i].height / 2);
				go->enemy[i].Velocity.y = 0.0f;

				if (go->enemy[i].gravity == UP) {
					go->enemy[i].IsGround = true;
				}


				if (go->enemy[i].gravity == RIGHT) {
					if (go->enemy[i].IsGround) {
						go->enemy[i].gravity = UP;
					}
				}
			} else {
				if (go->enemy[i].gravity == UP) {
					go->enemy[i].IsGround = false;
				}
			}

			if (go->MapChip[go->enemy[i].LeftBottom.y][go->enemy[i].LeftBottom.x].Map == 1 || go->MapChip[go->enemy[i].RightBottom.y][go->enemy[i].RightBottom.x].Map == 1
				|| go->MapChip[go->enemy[i].LeftBottom.y][go->enemy[i].LeftBottom.x].Map == 3 || go->MapChip[go->enemy[i].RightBottom.y][go->enemy[i].RightBottom.x].Map == 3
				|| go->MapChip[go->enemy[i].LeftBottom.y][go->enemy[i].LeftBottom.x].Map == 8 || go->MapChip[go->enemy[i].RightBottom.y][go->enemy[i].RightBottom.x].Map == 8) {
				go->enemy[i].Pos.y = float((go->enemy[i].LeftBottom.y) * BLOCKSIZE - go->enemy[i].height / 2);
				go->enemy[i].Velocity.y = 0.0f;

				if (go->enemy[i].gravity == DOWN) {
					go->enemy[i].IsGround = true;
				}

				if (go->enemy[i].gravity == LEFT) {
					if (go->enemy[i].IsGround) {
						go->enemy[i].gravity = DOWN;
					}
				}
			} else {
				if (go->enemy[i].gravity == DOWN) {
					go->enemy[i].IsGround = false;
				}
			}

			if (go->enemy[i].gravity == LEFT) {
				//重力処理！君に決めた！！！
				go->enemy[i].Acceleration.x = -0.5f;
				go->enemy[i].Velocity.x += go->enemy[i].Acceleration.x;
				//すり抜けんな！すり抜けんな！すり抜けんな！現世(こっち)で遊ぼう１２３４
				if (go->enemy[i].Velocity.x < -10.0f) {
					go->enemy[i].Velocity.x = -10.0f;
				}
				go->enemy[i].Pos.x += go->enemy[i].Velocity.x;
			} else if (go->enemy[i].gravity == RIGHT) {
				//重力処理！君に決めた！！！
				go->enemy[i].Acceleration.x = 0.5f;
				go->enemy[i].Velocity.x += go->enemy[i].Acceleration.x;
				go->enemy[i].Pos.x += go->enemy[i].Velocity.x;
				//すり抜けんな！すり抜けんな！すり抜けんな！現世(こっち)で遊ぼう１２３４
				if (go->enemy[i].Velocity.x > 10.0f) {
					go->enemy[i].Velocity.x = 10.0f;
				}
			} else if (go->enemy[i].gravity == UP) {
				go->enemy[i].Acceleration.x = 0.0f;
				go->enemy[i].Velocity.x = 0.0f;
				go->enemy[i].Pos.x -= go->enemy[i].speed;
			} else if (go->enemy[i].gravity == DOWN) {
				go->enemy[i].Acceleration.x = 0.0f;
				go->enemy[i].Velocity.x = 0.0f;
				go->enemy[i].Pos.x += go->enemy[i].speed;
			}

			go->enemy[i].LeftTop.x = int(go->enemy[i].Pos.x - go->enemy[i].width / 2) / BLOCKSIZE;
			go->enemy[i].LeftTop.y = int(go->enemy[i].Pos.y - go->enemy[i].height / 2) / BLOCKSIZE;
			go->enemy[i].LeftBottom.x = int(go->enemy[i].Pos.x - go->enemy[i].width / 2) / BLOCKSIZE;
			go->enemy[i].LeftBottom.y = int(go->enemy[i].Pos.y + go->enemy[i].height / 2 - 1) / BLOCKSIZE;
			go->enemy[i].RightTop.x = int(go->enemy[i].Pos.x + go->enemy[i].width / 2 - 1) / BLOCKSIZE;
			go->enemy[i].RightTop.y = int(go->enemy[i].Pos.y - go->enemy[i].height / 2) / BLOCKSIZE;
			go->enemy[i].RightBottom.x = int(go->enemy[i].Pos.x + go->enemy[i].width / 2 - 1) / BLOCKSIZE;
			go->enemy[i].RightBottom.y = int(go->enemy[i].Pos.y + go->enemy[i].height / 2 - 1) / BLOCKSIZE;

			//左右の判定を取って戻す
			if (go->MapChip[go->enemy[i].LeftTop.y][go->enemy[i].LeftTop.x].Map == 1 || go->MapChip[go->enemy[i].LeftBottom.y][go->enemy[i].LeftBottom.x].Map == 1
				|| go->MapChip[go->enemy[i].LeftTop.y][go->enemy[i].LeftTop.x].Map == 3 || go->MapChip[go->enemy[i].LeftBottom.y][go->enemy[i].LeftBottom.x].Map == 3
				|| go->MapChip[go->enemy[i].LeftTop.y][go->enemy[i].LeftTop.x].Map == 8 || go->MapChip[go->enemy[i].LeftBottom.y][go->enemy[i].LeftBottom.x].Map == 8) {
				go->enemy[i].Pos.x = float((go->enemy[i].LeftBottom.x + 1) * BLOCKSIZE + go->enemy[i].width / 2);
				go->enemy[i].Velocity.x = 0.0f;

				if (go->enemy[i].gravity == LEFT) {
					go->enemy[i].IsGround = true;
				}

				if (go->enemy[i].gravity == UP) {
					if (go->enemy[i].IsGround) {
						go->enemy[i].gravity = LEFT;
					}
				}
			} else {
				if (go->enemy[i].gravity == LEFT) {
					go->enemy[i].IsGround = false;
				}
			}

			if (go->MapChip[go->enemy[i].RightTop.y][go->enemy[i].RightTop.x].Map == 1 || go->MapChip[go->enemy[i].RightBottom.y][go->enemy[i].RightBottom.x].Map == 1
				|| go->MapChip[go->enemy[i].RightTop.y][go->enemy[i].RightTop.x].Map == 3 || go->MapChip[go->enemy[i].RightBottom.y][go->enemy[i].RightBottom.x].Map == 3
				|| go->MapChip[go->enemy[i].RightTop.y][go->enemy[i].RightTop.x].Map == 8 || go->MapChip[go->enemy[i].RightBottom.y][go->enemy[i].RightBottom.x].Map == 8) {
				go->enemy[i].Pos.x = float((go->enemy[i].RightBottom.x) * BLOCKSIZE - go->enemy[i].width / 2);
				go->enemy[i].Velocity.x = 0.0f;

				if (go->enemy[i].gravity == RIGHT) {
					go->enemy[i].IsGround = true;
				}

				if (go->enemy[i].gravity == DOWN) {
					if (go->enemy[i].IsGround) {
						go->enemy[i].gravity = RIGHT;
					}
				}
			} else {
				if (go->enemy[i].gravity == RIGHT) {
					go->enemy[i].IsGround = false;
				}
			}

			// 相棒がワープ中でなければ
			if (!go->buddy.IsWarp) {

				// 敵に当たったらミスにする
				if(!go->buddy.IsClear){
					if (go->buddy.IsAlive) {
						if (go->buddy.Pos.x + go->buddy.width / 2.0f > go->enemy[i].Pos.x - go->enemy[i].width / 2.0f && go->buddy.Pos.x - go->buddy.width / 2.0f < go->enemy[i].Pos.x + go->enemy[i].width / 2.0f) {
							if (go->buddy.Pos.y + go->buddy.height / 2.0f > go->enemy[i].Pos.y - go->enemy[i].height / 2.0f && go->buddy.Pos.y - go->buddy.height / 2.0f < go->enemy[i].Pos.y + go->enemy[i].height / 2.0f) {

								go->buddy.IsAlive = false;

								//SE
								Novice::PlayAudio(audio->se.death, false, 1.0f);

							}
						}
					}
				}

			}

			if (!go->buddy.IsAlive) {

			}

			// 敵のアニメーションの処理
			if (go->enemy[i].frameCount < 29) {
				go->enemy[i].frameCount++;
			} else {
				go->enemy[i].frameCount = 0;
			}

			go->enemy[i].animCount = go->enemy[i].frameCount / 5;

		}

	}

}


//敵の描画
void EnemyDraw(GameObject* go) {

	for (int i = 0; i < 10; ++i) {

		// 敵が生きていたら
		if (go->enemy[i].IsAlive) {

			Novice::DrawQuad(
				//左上
				int(go->enemy[i].DrawLeftTop.x),
				int(go->enemy[i].DrawLeftTop.y),

				//右上
				int(go->enemy[i].DrawRightTop.x),
				int(go->enemy[i].DrawRightTop.y),

				//左下
				int(go->enemy[i].DrawLeftBottom.x),
				int(go->enemy[i].DrawLeftBottom.y),

				//右下
				int(go->enemy[i].DrawRightBottom.x),
				int(go->enemy[i].DrawRightBottom.y),

				//画像上の座標
				0 + 64 * go->enemy[i].animCount, 0,

				//横幅、縦幅
				64, 64,

				//テクスチャハンドル
				go->enemy[0].image,

				//色
				go->enemy[0].color
			);

		}

	}

}