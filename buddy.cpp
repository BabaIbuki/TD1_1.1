//ソースファイルの読み込み
#include<Novice.h>

//ヘッダーファイルの読み込み
#include"structer.h"
#include"common.h"
#include"enum.h"
#include <corecrt_math_defines.h>
#include "stage.h"
#include "enemy.h"


//最初に読み込む相棒の初期化の関数
void BuddyInitialize(GameObject* go) {

	//座標の初期化
	//go->player.Pos.x = BLOCKSIZE + BLOCKSIZE / 2;
	//go->player.Pos.y = BLOCKSIZE * 3 + BLOCKSIZE / 2;

	go->buddy.Pos.x = 5 * BLOCKSIZE + BLOCKSIZE / 2;
	go->buddy.Pos.y = 10 * BLOCKSIZE + BLOCKSIZE / 2;

	go->buddy.Velocity.x = 0.0f;
	go->buddy.Velocity.y = 0.0f;

	go->buddy.Acceleration.x = 0.5f;
	go->buddy.Acceleration.y = 0.5f;

	go->buddy.speed = 2.0f;

	//サイズの初期化
	go->buddy.width = BLOCKSIZE;
	go->buddy.height = BLOCKSIZE;

	//アニメーションの変数
	go->buddy.IsAir = false;
	go->buddy.DrawWidth = BLOCKSIZE;
	go->buddy.DrawHeight = BLOCKSIZE;
	go->buddy.AnimationTimer = 0;
	go->buddy.UpperHalfAlteration = -2;
	go->buddy.BesideAlteration = -2;

	//回転用の変数初期化
	go->buddy.degree = -360.0f;
	go->buddy.theta = go->buddy.degree * (float(M_PI) / 180.0f);

	//プレイヤーの描画時の四角の座標計算
	DrawFourVertexes(&go->buddy);
	MakeRotatePos(&go->buddy);


	//画像関連
	go->buddy.image = Novice::LoadTexture("./MyResources./Buddy.png");
	go->buddy.graphHandleFalling = Novice::LoadTexture("./MyResources./BuddyFalling.png");
	go->buddy.color = WHITE;

	// 相棒の重力の向き
	go->buddy.gravity = DOWN;

	//go->buddy.IsGround = false;

	go->buddy.IsClear = false;

	go->buddy.IsAlive = true;

	go->buddy.respawnTimer = 60;

	// 手に入れた星の数の変数の初期化
	go->buddy.starGetCount = 0;
	for (int i = 0; i < 15; i++) {
		go->buddy.MaxStarCount[i] = 0;
	}
	// ワープボックスの使用クールタイム
	go->buddy.warpCoolTime = 0;

	// ワープ中どうかのフラグ
	go->buddy.IsWarp = false;

	// 何番のワープブロックにいるかの変数
	go->buddy.onWarpBlock6 = false;
	go->buddy.onWarpBlock7 = false;

	// 相棒のアニメーションに使う変数
	go->buddy.frameCount = 0;
	go->buddy.animCount = 0;

	// 落下時のアニメーションの変数
	go->buddy.graphHandleNum = 0;

}

void BuddyGameInitialize(GameObject* go) {

	go->buddy.Velocity.x = 0.0f;
	go->buddy.Velocity.y = 0.0f;

	go->buddy.Acceleration.x = 0.5f;
	go->buddy.Acceleration.y = 0.5f;

	//回転用の変数初期化
	go->buddy.degree = -360.0f;
	go->buddy.theta = go->buddy.degree * (float(M_PI) / 180.0f);

	//プレイヤーの描画時の四角の座標計算
	DrawFourVertexes(&go->buddy);
	MakeRotatePos(&go->buddy);

	go->buddy.IsAir = false;
	go->buddy.DrawWidth = BLOCKSIZE;
	go->buddy.DrawHeight = BLOCKSIZE;
	go->buddy.AnimationTimer = 0;
	go->buddy.UpperHalfAlteration = -2;
	go->buddy.BesideAlteration = -2;

	// 相棒の重力の向き
	go->buddy.gravity = DOWN;

	//go->buddy.IsGround = false;

	go->buddy.IsClear = false;

	go->buddy.IsAlive = true;

	go->buddy.respawnTimer = 60;

	// 手に入れた星の数の変数の初期化
	go->buddy.starGetCount = 0;

	// ワープボックスの使用クールタイム
	go->buddy.warpCoolTime = 0;

	// ワープ中どうかのフラグ
	go->buddy.IsWarp = false;

	// 何番のワープブロックにいるかの変数
	go->buddy.onWarpBlock6 = false;
	go->buddy.onWarpBlock7 = false;

	// 落下時のアニメーションの変数
	go->buddy.graphHandleNum = 0;

}

//相棒の動きの関数（マップチップとの当たり判定も込みの可能性もあり）
void BuddyMove(GameObject* go, System* system) {

	// 相棒が生きていて
	if (go->buddy.IsAlive) {

		// クリアしていなければ
		if (!go->buddy.IsClear) {

			if (go->buddy.gravity == UP) {
				go->buddy.Acceleration.y = -0.5f;
				go->buddy.Pos.y += go->buddy.Velocity.y;
				go->buddy.Velocity.y += go->buddy.Acceleration.y;
				//すり抜けんな！すり抜けんな！すり抜けんな！現世(こっち)で遊ぼう１２３４
				if (go->buddy.Velocity.y < -10.0f) {
					go->buddy.Velocity.y = -10.0f;
				}
				go->buddy.Pos.y += go->buddy.Velocity.y;
			}
			else if (go->buddy.gravity == DOWN) {
				//重力処理！君に決めた！！！
				go->buddy.Acceleration.y = 0.5f;
				go->buddy.Pos.y += go->buddy.Velocity.y;
				go->buddy.Velocity.y += go->buddy.Acceleration.y;
				//すり抜けんな！すり抜けんな！すり抜けんな！現世(こっち)で遊ぼう１２３４
				if (go->buddy.Velocity.y > 10.0f) {
					go->buddy.Velocity.y = 10.0f;
				}
				go->buddy.Pos.y += go->buddy.Velocity.y;
			}
			else if (go->buddy.gravity == LEFT) {
				go->buddy.Acceleration.y = 0.0f;
				go->buddy.Velocity.y = 0.0f;
				// 相棒を進ませる
				go->buddy.Pos.y += go->buddy.speed;
			}
			else if (go->buddy.gravity == RIGHT) {
				go->buddy.Acceleration.y = 0.0f;
				go->buddy.Velocity.y = 0.0f;
				// 相棒を進ませる
				go->buddy.Pos.y -= go->buddy.speed;
			}

			go->buddy.LeftTop.x = int(go->buddy.Pos.x - go->buddy.width / 2) / BLOCKSIZE;
			go->buddy.LeftTop.y = int(go->buddy.Pos.y - go->buddy.height / 2) / BLOCKSIZE;
			go->buddy.LeftBottom.x = int(go->buddy.Pos.x - go->buddy.width / 2) / BLOCKSIZE;
			go->buddy.LeftBottom.y = int(go->buddy.Pos.y + go->buddy.height / 2 - 1) / BLOCKSIZE;
			go->buddy.RightTop.x = int(go->buddy.Pos.x + go->buddy.width / 2 - 1) / BLOCKSIZE;
			go->buddy.RightTop.y = int(go->buddy.Pos.y - go->buddy.height / 2) / BLOCKSIZE;
			go->buddy.RightBottom.x = int(go->buddy.Pos.x + go->buddy.width / 2 - 1) / BLOCKSIZE;
			go->buddy.RightBottom.y = int(go->buddy.Pos.y + go->buddy.height / 2 - 1) / BLOCKSIZE;

			//上下の判定を取って戻す
			if (go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 1 || go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 1
				|| go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 3 || go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 3
				|| go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 8 || go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 8) {
				go->buddy.Pos.y = float((go->buddy.LeftTop.y + 1) * BLOCKSIZE + go->buddy.height / 2);
				go->buddy.Velocity.y = 0.0f;

				if (go->buddy.gravity == UP) {
					go->buddy.IsGround = true;
				}

				if (go->MapChip[int((go->buddy.Pos.y) / BLOCKSIZE) - 1][int(go->buddy.Pos.x) / BLOCKSIZE].Map != 2
					&& go->MapChip[int((go->buddy.Pos.y) / BLOCKSIZE) + 1][int(go->buddy.Pos.x) / BLOCKSIZE].Map != 2
					&& go->MapChip[int(go->buddy.Pos.y) / BLOCKSIZE][int((go->buddy.Pos.x) / BLOCKSIZE) - 1].Map != 2
					&& go->MapChip[int(go->buddy.Pos.y) / BLOCKSIZE][int((go->buddy.Pos.x) / BLOCKSIZE) + 1].Map != 2) {
				}
				else {
					if (go->buddy.gravity == RIGHT) {
						if (go->buddy.IsGround) {
							go->buddy.gravity = UP;
						}
					}
				}
			}
			else {
				if (go->buddy.gravity == UP) {
					go->buddy.IsGround = false;
				}
			}

			if (go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 1 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 1
				|| go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 3 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 3
				|| go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 8 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 8) {
				go->buddy.Pos.y = float((go->buddy.LeftBottom.y) * BLOCKSIZE - go->buddy.height / 2);
				go->buddy.Velocity.y = 0.0f;

				if (go->buddy.gravity == DOWN) {
					go->buddy.IsGround = true;
				}

				if (go->MapChip[int((go->buddy.Pos.y) / BLOCKSIZE) - 1][int(go->buddy.Pos.x) / BLOCKSIZE].Map != 2
					&& go->MapChip[int((go->buddy.Pos.y) / BLOCKSIZE) + 1][int(go->buddy.Pos.x) / BLOCKSIZE].Map != 2
					&& go->MapChip[int(go->buddy.Pos.y) / BLOCKSIZE][int((go->buddy.Pos.x) / BLOCKSIZE) - 1].Map != 2
					&& go->MapChip[int(go->buddy.Pos.y) / BLOCKSIZE][int((go->buddy.Pos.x) / BLOCKSIZE) + 1].Map != 2) {
				}
				else {
					if (go->buddy.gravity == LEFT) {
						if (go->buddy.IsGround) {
							go->buddy.gravity = DOWN;
						}
					}
				}
			}
			else {
				if (go->buddy.gravity == DOWN) {
					go->buddy.IsGround = false;
				}
			}

			if (go->buddy.gravity == LEFT) {
				//重力処理！君に決めた！！！
				go->buddy.Acceleration.x = -0.5f;
				go->buddy.Velocity.x += go->buddy.Acceleration.x;
				//すり抜けんな！すり抜けんな！すり抜けんな！現世(こっち)で遊ぼう１２３４
				if (go->buddy.Velocity.x < -10.0f) {
					go->buddy.Velocity.x = -10.0f;
				}
				go->buddy.Pos.x += go->buddy.Velocity.x;
			}
			else if (go->buddy.gravity == RIGHT) {
				//重力処理！君に決めた！！！
				go->buddy.Acceleration.x = 0.5f;
				go->buddy.Velocity.x += go->buddy.Acceleration.x;
				go->buddy.Pos.x += go->buddy.Velocity.x;
				//すり抜けんな！すり抜けんな！すり抜けんな！現世(こっち)で遊ぼう１２３４
				if (go->buddy.Velocity.x > 10.0f) {
					go->buddy.Velocity.x = 10.0f;
				}
			}
			else if (go->buddy.gravity == UP) {
				go->buddy.Acceleration.x = 0.0f;
				go->buddy.Velocity.x = 0.0f;
				go->buddy.Pos.x -= go->buddy.speed;
			}
			else if (go->buddy.gravity == DOWN) {
				go->buddy.Acceleration.x = 0.0f;
				go->buddy.Velocity.x = 0.0f;
				go->buddy.Pos.x += go->buddy.speed;
			}

			go->buddy.LeftTop.x = int(go->buddy.Pos.x - go->buddy.width / 2) / BLOCKSIZE;
			go->buddy.LeftTop.y = int(go->buddy.Pos.y - go->buddy.height / 2) / BLOCKSIZE;
			go->buddy.LeftBottom.x = int(go->buddy.Pos.x - go->buddy.width / 2) / BLOCKSIZE;
			go->buddy.LeftBottom.y = int(go->buddy.Pos.y + go->buddy.height / 2 - 1) / BLOCKSIZE;
			go->buddy.RightTop.x = int(go->buddy.Pos.x + go->buddy.width / 2 - 1) / BLOCKSIZE;
			go->buddy.RightTop.y = int(go->buddy.Pos.y - go->buddy.height / 2) / BLOCKSIZE;
			go->buddy.RightBottom.x = int(go->buddy.Pos.x + go->buddy.width / 2 - 1) / BLOCKSIZE;
			go->buddy.RightBottom.y = int(go->buddy.Pos.y + go->buddy.height / 2 - 1) / BLOCKSIZE;

			//左右の判定を取って戻す
			if (go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 1 || go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 1
				|| go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 3 || go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 3
				|| go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 8 || go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 8) {
				go->buddy.Pos.x = float((go->buddy.LeftBottom.x + 1) * BLOCKSIZE + go->buddy.width / 2);
				go->buddy.Velocity.x = 0.0f;

				if (go->buddy.gravity == LEFT) {
					go->buddy.IsGround = true;
				}

				if (go->MapChip[int((go->buddy.Pos.y) / BLOCKSIZE) - 1][int(go->buddy.Pos.x) / BLOCKSIZE].Map != 2
					&& go->MapChip[int((go->buddy.Pos.y) / BLOCKSIZE) + 1][int(go->buddy.Pos.x) / BLOCKSIZE].Map != 2
					&& go->MapChip[int(go->buddy.Pos.y) / BLOCKSIZE][int((go->buddy.Pos.x) / BLOCKSIZE) - 1].Map != 2
					&& go->MapChip[int(go->buddy.Pos.y) / BLOCKSIZE][int((go->buddy.Pos.x) / BLOCKSIZE) + 1].Map != 2) {
				}
				else {
					if (go->buddy.gravity == UP) {
						if (go->buddy.IsGround) {
							go->buddy.gravity = LEFT;
						}
					}
				}
			}
			else {
				if (go->buddy.gravity == LEFT) {
					go->buddy.IsGround = false;
				}
			}

			if (go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 1 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 1
				|| go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 3 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 3
				|| go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 8 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 8) {
				go->buddy.Pos.x = float((go->buddy.RightBottom.x) * BLOCKSIZE - go->buddy.width / 2);
				go->buddy.Velocity.x = 0.0f;

				if (go->buddy.gravity == RIGHT) {
					go->buddy.IsGround = true;
				}

				if (go->MapChip[int((go->buddy.Pos.y) / BLOCKSIZE) - 1][int(go->buddy.Pos.x) / BLOCKSIZE].Map != 2
					&& go->MapChip[int((go->buddy.Pos.y) / BLOCKSIZE) + 1][int(go->buddy.Pos.x) / BLOCKSIZE].Map != 2
					&& go->MapChip[int(go->buddy.Pos.y) / BLOCKSIZE][int((go->buddy.Pos.x) / BLOCKSIZE) - 1].Map != 2
					&& go->MapChip[int(go->buddy.Pos.y) / BLOCKSIZE][int((go->buddy.Pos.x) / BLOCKSIZE) + 1].Map != 2) {
				}
				else {
					if (go->buddy.gravity == DOWN) {
						if (go->buddy.IsGround) {
							go->buddy.gravity = RIGHT;
						}
					}
				}
			}
			else {
				if (go->buddy.gravity == RIGHT) {
					go->buddy.IsGround = false;
				}
			}

			// ゴールに触れたらクリアフラグを立てる
			if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 5) {

				go->buddy.IsClear = true;

			}

		}

	}

	// 相棒のアニメーションの処理
	if (go->buddy.frameCount < 119) {
		go->buddy.frameCount++;
	}
	else {
		go->buddy.frameCount = 0;
	}

	go->buddy.animCount = go->buddy.frameCount / 10;

	// 落下中に相棒が下をのぞくようにする

	// 重力の向きが下ならば
	if (go->buddy.gravity == DOWN) {

		// 重力加速度が2.0f未満なら
		if (go->buddy.Velocity.y < 2.0f) {

			go->buddy.graphHandleNum = 0;

		}
		else if (go->buddy.Velocity.y >= 2.0f && go->buddy.Velocity.y < 5.0f) {

			go->buddy.graphHandleNum = 1;

		}
		else if (go->buddy.Velocity.y >= 5.0f) {

			go->buddy.graphHandleNum = 2;

		}

	}
	else if (go->buddy.gravity == RIGHT) {

		// 重力加速度が2.0f未満なら
		if (go->buddy.Velocity.x < 2.0f) {

			go->buddy.graphHandleNum = 0;

		}
		else if (go->buddy.Velocity.x >= 2.0f && go->buddy.Velocity.x < 5.0f) {

			go->buddy.graphHandleNum = 1;

		}
		else if (go->buddy.Velocity.x >= 5.0f) {

			go->buddy.graphHandleNum = 2;

		}

	}
	else if (go->buddy.gravity == UP) {

		// 重力加速度が-2.0fより大きければ
		if (go->buddy.Velocity.y > -2.0f) {

			go->buddy.graphHandleNum = 0;

		}
		else if (go->buddy.Velocity.y <= -2.0f && go->buddy.Velocity.y > -5.0f) {

			go->buddy.graphHandleNum = 1;

		}
		else if (go->buddy.Velocity.y <= -5.0f) {

			go->buddy.graphHandleNum = 2;

		}

	}
	else if (go->buddy.gravity == LEFT) {

		// 重力加速度が-2.0fより大きければ
		if (go->buddy.Velocity.x > -2.0f) {

			go->buddy.graphHandleNum = 0;

		}
		else if (go->buddy.Velocity.x <= -2.0f && go->buddy.Velocity.x > -5.0f) {

			go->buddy.graphHandleNum = 1;

		}
		else if (go->buddy.Velocity.x <= -5.0f) {

			go->buddy.graphHandleNum = 2;

		}

	}

	if (!go->buddy.IsAlive) {
		go->buddy.respawnTimer--;
		if (go->buddy.respawnTimer <= 0) {
			system->sc.backColor = 0xffffffff;
			BuddyGameInitialize(go);
			EnemyMoveGameInitialize(go);
			StageGenerate(go, system);
		}
	}

}


//相棒のアニメーションの関数
void BuddyAnimation(GameObject* go) {

	//俺「どんな形になっても...元の形に直してみせるから...」
	//キャラ「いぶきぃぃぃぃぃぃぃィぃィぃあぁあああぁああぁあぁ」
	if (go->buddy.DrawHeight / 2 <= 24) {
		go->buddy.UpperHalfAlteration = 2;
	} else if (go->buddy.DrawHeight / 2 >= 32) {
		go->buddy.UpperHalfAlteration = -2;
	}

	if (go->buddy.DrawWidth > 64) {
		go->buddy.DrawWidth += go->buddy.BesideAlteration;
	}

	//ブロックに下辺がついてるかついてないかでアニメーション変わってくるんだよねぇ
		//重力の向きによって下辺の考え方が変わるから注意注意。写楽なまちでぇダンシング！！！
	if (go->buddy.gravity == DOWN) {
		//必要なマップ番号をッ❤取得しながらッ❤床に接地しているかッ❤調べたい。そうしたい！！！
		go->buddy.LeftBottom.x = int(go->buddy.Pos.x - go->buddy.width / 2) / BLOCKSIZE;
		go->buddy.LeftBottom.y = int(go->buddy.Pos.y + go->buddy.height / 2) / BLOCKSIZE;
		go->buddy.RightBottom.x = int(go->buddy.Pos.x + go->buddy.width / 2 - 1) / BLOCKSIZE;
		go->buddy.RightBottom.y = int(go->buddy.Pos.y + go->buddy.height / 2) / BLOCKSIZE;
		if (go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 1 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 1
			|| go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 3 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 3
			|| go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 8 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 8) {
			//着地したときぶっ潰す
			if (go->buddy.IsAir) {
				go->buddy.DrawHeight = 28;
				go->buddy.DrawWidth = 80;
				go->buddy.IsAir = 0;
				go->buddy.AnimationTimer = 1;
			}
		} else {
			//地面にいるフラグをここで折ったっていい
			go->buddy.IsAir = 1;
			//地面にいない時キャラの形をヲヲヲんねぇじ曲げるぅッッ！！！
			if (go->buddy.IsAir) {
				if (go->buddy.DrawHeight < 80) {
					go->buddy.DrawHeight += 2;
				}
				if (go->buddy.DrawWidth > 54) {
					go->buddy.DrawWidth -= 2;
				}
			}
		}
	} else if (go->buddy.gravity == UP) {
		//必要なマップ番号をッ❤取得しながらッ❤床に接地しているかッ❤調べたい。そうしたい！！！
		go->buddy.LeftTop.x = int(go->buddy.Pos.x - go->buddy.width / 2) / BLOCKSIZE;
		go->buddy.LeftTop.y = int(go->buddy.Pos.y - go->buddy.height / 2 - 1) / BLOCKSIZE;
		go->buddy.RightTop.x = int(go->buddy.Pos.x + go->buddy.width / 2 - 1) / BLOCKSIZE;
		go->buddy.RightTop.y = int(go->buddy.Pos.y - go->buddy.height / 2 - 1) / BLOCKSIZE;
		if (go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 1 || go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 1
			|| go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 3 || go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 3
			|| go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 8 || go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 8) {
			//着地したときぶっ潰す
			if (go->buddy.IsAir) {
				go->buddy.DrawHeight = 12;
				go->buddy.DrawWidth = 80;
				go->buddy.IsAir = 0;
				go->buddy.AnimationTimer = 1;
			}
		} else {
			//地面にいるフラグをここで折ったっていい
			go->buddy.IsAir = 1;
			//地面にいない時キャラの形をヲヲヲんねぇじ曲げるぅッッ！！！
			if (go->buddy.IsAir) {
				if (go->buddy.DrawHeight < 80) {
					go->buddy.DrawHeight += 2;
				}
				if (go->buddy.DrawWidth > 54) {
					go->buddy.DrawWidth -= 2;
				}
			}
		}
	} else if (go->buddy.gravity == LEFT) {
		//必要なマップ番号をッ❤取得しながらッ❤床に接地しているかッ❤調べたい。そうしたい！！！
		go->buddy.LeftTop.x = int(go->buddy.Pos.x - go->buddy.width / 2 - 1) / BLOCKSIZE;
		go->buddy.LeftTop.y = int(go->buddy.Pos.y - go->buddy.height / 2) / BLOCKSIZE;
		go->buddy.LeftBottom.x = int(go->buddy.Pos.x - go->buddy.width / 2 - 1) / BLOCKSIZE;
		go->buddy.LeftBottom.y = int(go->buddy.Pos.y + go->buddy.height / 2 - 1) / BLOCKSIZE;
		if (go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 1 || go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 1
			|| go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 3 || go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 3
			|| go->MapChip[go->buddy.LeftTop.y][go->buddy.LeftTop.x].Map == 8 || go->MapChip[go->buddy.LeftBottom.y][go->buddy.LeftBottom.x].Map == 8) {
			//着地したときぶっ潰す
			if (go->buddy.IsAir) {
				go->buddy.DrawHeight = 12;
				go->buddy.DrawWidth = 80;
				go->buddy.IsAir = 0;
				go->buddy.AnimationTimer = 1;
			}
		} else {
			//地面にいるフラグをここで折ったっていい
			go->buddy.IsAir = 1;
			//地面にいない時キャラの形をヲヲヲんねぇじ曲げるぅッッ！！！
			if (go->buddy.IsAir) {
				if (go->buddy.DrawHeight < 80) {
					go->buddy.DrawHeight += 2;
				}
				if (go->buddy.DrawWidth > 54) {
					go->buddy.DrawWidth -= 2;
				}
			}
		}
	} else if (go->buddy.gravity == RIGHT) {
		//必要なマップ番号をッ❤取得しながらッ❤床に接地しているかッ❤調べたい。そうしたい！！！
		go->buddy.RightTop.x = int(go->buddy.Pos.x + go->buddy.width / 2) / BLOCKSIZE;
		go->buddy.RightTop.y = int(go->buddy.Pos.y - go->buddy.height / 2) / BLOCKSIZE;
		go->buddy.RightBottom.x = int(go->buddy.Pos.x + go->buddy.width / 2) / BLOCKSIZE;
		go->buddy.RightBottom.y = int(go->buddy.Pos.y + go->buddy.height / 2 - 1) / BLOCKSIZE;
		if (go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 1 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 1
			|| go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 3 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 3
			|| go->MapChip[go->buddy.RightTop.y][go->buddy.RightTop.x].Map == 8 || go->MapChip[go->buddy.RightBottom.y][go->buddy.RightBottom.x].Map == 8) {
			//着地したときぶっ潰す
			if (go->buddy.IsAir) {
				go->buddy.DrawHeight = 12;
				go->buddy.DrawWidth = 80;
				go->buddy.IsAir = 0;
				go->buddy.AnimationTimer = 1;
			}
		} else {
			//地面にいるフラグをここで折ったっていい
			go->buddy.IsAir = 1;
			//地面にいない時キャラの形をヲヲヲんねぇじ曲げるぅッッ！！！
			if (go->buddy.IsAir) {
				if (go->buddy.DrawHeight < 80) {
					go->buddy.DrawHeight += 2;
				}
				if (go->buddy.DrawWidth > 54) {
					go->buddy.DrawWidth -= 2;
				}
			}
		}
	}

	//縦幅横幅の計算
	if (!go->buddy.IsAir) {

		go->buddy.DrawHeight += go->buddy.UpperHalfAlteration;

	}

	//プレーヤーの回転処理
	//計算しやすいようにディグリーに変換
	//死にかけのdegree
	//go->buddy.degree = go->buddy.theta * (180.0f / float(M_PI));
	//重力の向きによって角度を計算
	
	if (go->buddy.gravity == DOWN) {

		if (go->buddy.degree != -360.0f) {
			go->buddy.degree -= 15.0f;
		}

	} else if (go->buddy.gravity == RIGHT) {

		if (go->buddy.degree != -90.0f) {
			go->buddy.degree -= 15.0f;
		}

	} else if (go->buddy.gravity == UP) {

		if (go->buddy.degree != -180.0f) {
			go->buddy.degree -= 15.0f;
		}

	} else if (go->buddy.gravity == LEFT) {

		if (go->buddy.degree != -270.0f) {
			go->buddy.degree -= 15.0f;
		}

	}

	if (go->buddy.degree < -360.0f) {
		go->buddy.degree += 360.0f;
	}


	//thetaを使う
	//sinやcosなどの関数に渡す値はtheta
	// degreeを渡してはいけない
	// degreeを渡してはいけない
	// degreeを渡してはいけない
	go->buddy.theta = go->buddy.degree * (float(M_PI) / 180.0f);

	DrawFourVertexes(&go->buddy);
	MakeRotatePos(&go->buddy);

}


//相棒の描画
void BuddyDraw(GameObject* go) {

	// 相棒が生きていて
	if (go->buddy.IsAlive) {

		// 相棒がクリアしていなければ
		if (!go->buddy.IsClear) {

			// ワープ中でなければ
			if (go->buddy.warpCoolTime <= 57) {

				// 落下中でなければ
				if (go->buddy.Velocity.x <= 0.5f && go->buddy.Velocity.x >= -0.5f && go->buddy.Velocity.y <= 0.5f && go->buddy.Velocity.y >= -0.5f) {

					Novice::DrawQuad(
						//左上
						int(go->buddy.Pos.x + go->buddy.BufRotateLeftTop.x),
						int(go->buddy.Pos.y + go->buddy.BufRotateLeftTop.y),

						//右上
						int(go->buddy.Pos.x + go->buddy.BufRotateRightTop.x),
						int(go->buddy.Pos.y + go->buddy.BufRotateRightTop.y),

						//左下
						int(go->buddy.Pos.x + go->buddy.BufRotateLeftBottom.x),
						int(go->buddy.Pos.y + go->buddy.BufRotateLeftBottom.y),

						//右下
						int(go->buddy.Pos.x + go->buddy.BufRotateRightBottom.x),
						int(go->buddy.Pos.y + go->buddy.BufRotateRightBottom.y),

						//画像上の座標
						0 + 64 * go->buddy.animCount, 0,

						//横幅、縦幅
						64, 64,

						//テクスチャハンドル
						go->buddy.image,

						//色
						go->buddy.color
					);

				} else {

					Novice::DrawQuad(
						//左上
						int(go->buddy.Pos.x + go->buddy.BufRotateLeftTop.x),
						int(go->buddy.Pos.y + go->buddy.BufRotateLeftTop.y),

						//右上
						int(go->buddy.Pos.x + go->buddy.BufRotateRightTop.x),
						int(go->buddy.Pos.y + go->buddy.BufRotateRightTop.y),

						//左下
						int(go->buddy.Pos.x + go->buddy.BufRotateLeftBottom.x),
						int(go->buddy.Pos.y + go->buddy.BufRotateLeftBottom.y),

						//右下
						int(go->buddy.Pos.x + go->buddy.BufRotateRightBottom.x),
						int(go->buddy.Pos.y + go->buddy.BufRotateRightBottom.y),

						//画像上の座標
						0 + 64 * go->buddy.graphHandleNum, 0,

						//横幅、縦幅
						64, 64,

						//テクスチャハンドル
						go->buddy.graphHandleFalling,

						//色
						go->buddy.color
					);

				}

			}

		}

	}

}