#include<Novice.h>
#include"structer.h"
#include"common.h"
#include<math.h>
#include<time.h>
#include<corecrt_math_defines.h>

//初期化関数
void Effectinitialize(AllEffect* ae) {

	for (int i = 0; i < CCEffectNum; i++) {
		//座標
		ae->cc[i].Pos = {};

		//大きさ
		ae->cc[i].width = 0.0f;
		ae->cc[i].height = 0.0f;

		//動き関連
		ae->cc[i].Acceleration.x = 0.0f;
		ae->cc[i].Acceleration.y = 0.1f;

		ae->cc[i].Velocity = {};
		ae->cc[i].speed = 0.0f;

		//フラグ関連
		ae->cc[i].IsActive = false;
		ae->cc[i].ActiveTimer = 60;

		//色
		ae->cc[i].color = WHITE;
	}

	//画像の読み込み
	ae->cc[0].image = Novice::LoadTexture("./MyResources./effect.png");
}

void DeathEffectInitialze(AllEffect* ae) {

	for (int i = 0; i < BDEffectNum; i++) {
		ae->bd[i].IsActive = false;
		ae->bd[i].ActiveTimer = 60;
		//エフェクトの角度
		ae->bd[i].Rdegree = float(rand() % 360);

		//エフェクトの角度
		ae->bd[i].Rtheta = ((ae->bd[i].Rdegree / 180.0f) * float(M_PI));

		//エフェクトの速さ
		ae->bd[i].speed = float(rand() % 15 + 20);

		//ベクトルの作成
		ae->bd[i].vector.x = cosf(ae->bd->Rdegree);
		ae->bd[i].vector.y = sinf(ae->bd->Rdegree);

		//速度の作成
		ae->bd[i].velocity.x = ae->bd[i].vector.x * ae->bd[i].speed;
		ae->bd[i].velocity.y = ae->bd[i].vector.y * ae->bd[i].speed;

		ae->bd[i].Pos = {};

		ae->bd[i].width = 8;
		ae->bd[i].height = 8;

		ae->bd[i].LeftTop.x = int(ae->bd[i].Pos.x - ae->bd[i].width / 2) / BLOCKSIZE;
		ae->bd[i].LeftTop.y = int(ae->bd[i].Pos.y - ae->bd[i].height / 2) / BLOCKSIZE;
		ae->bd[i].LeftBottom.x = int(ae->bd[i].Pos.x - ae->bd[i].width / 2) / BLOCKSIZE;
		ae->bd[i].LeftBottom.y = int(ae->bd[i].Pos.y + ae->bd[i].height / 2 - 1) / BLOCKSIZE;
		ae->bd[i].RightTop.x = int(ae->bd[i].Pos.x + ae->bd[i].width / 2 - 1) / BLOCKSIZE;
		ae->bd[i].RightTop.y = int(ae->bd[i].Pos.y - ae->bd[i].height / 2) / BLOCKSIZE;
		ae->bd[i].RightBottom.x = int(ae->bd[i].Pos.x + ae->bd[i].width / 2 - 1) / BLOCKSIZE;
		ae->bd[i].RightBottom.y = int(ae->bd[i].Pos.y + ae->bd[i].height / 2 - 1) / BLOCKSIZE;

	}

	//画像の読み込み
	ae->bd[0].image = Novice::LoadTexture("./MyResources./BuddyDeathEffect.png");

}


void DeathEffect(AllEffect* ae, GameObject* go) {

	//乱数値の取得
	srand((unsigned)time(NULL));

	if (!go->buddy.IsAlive) {
		for (int i = 0; i < BDEffectNum; i++) {
			if (!ae->bd[i].IsActive) {
				//プレイヤーが死んだらエフェクトに命を吹き込む！
				ae->bd[i].IsActive = true;

				//お前の寿命は5秒だせいぜい楽しむといい
				ae->bd[i].ActiveTimer = 60;

				//エフェクトの角度を取得
				ae->bd[i].Rdegree = float(rand() % -180+180);

				//エフェクトの角度の変換
				ae->bd[i].Rtheta = ((ae->bd[i].Rdegree / 180.0f) * float(M_PI));

				//エフェクトの速さを取得
				ae->bd[i].speed = float(rand() % 5 + 5);

				//ベクトルの作成
				ae->bd[i].vector.x = cosf(ae->bd[i].Rtheta);
				ae->bd[i].vector.y = sinf(ae->bd[i].Rtheta);

				//速度の作成
				ae->bd[i].velocity.x = ae->bd[i].vector.x * ae->bd[i].speed;
				ae->bd[i].velocity.y = ae->bd[i].vector.y * ae->bd[i].speed;

				ae->bd[i].Pos = go->buddy.Pos;

				

			}
		}
	}

	for (int i = 0; i < BDEffectNum; i++) {

		if (ae->bd[i].IsActive) {

			//アクティブになったら寿命を減らす
			ae->bd[i].ActiveTimer--;

			//エフェクトを動かす
			ae->bd[i].Pos.x += ae->bd[i].velocity.x;

			/*ae->bd[i].LeftTop.x = int(ae->bd[i].Pos.x - ae->bd[i].width / 2) / BLOCKSIZE;
			ae->bd[i].LeftTop.y = int(ae->bd[i].Pos.y - ae->bd[i].height / 2) / BLOCKSIZE;
			ae->bd[i].LeftBottom.x = int(ae->bd[i].Pos.x - ae->bd[i].width / 2) / BLOCKSIZE;
			ae->bd[i].LeftBottom.y = int(ae->bd[i].Pos.y + ae->bd[i].height / 2 - 1) / BLOCKSIZE;
			ae->bd[i].RightTop.x = int(ae->bd[i].Pos.x + ae->bd[i].width / 2 - 1) / BLOCKSIZE;
			ae->bd[i].RightTop.y = int(ae->bd[i].Pos.y - ae->bd[i].height / 2) / BLOCKSIZE;
			ae->bd[i].RightBottom.x = int(ae->bd[i].Pos.x + ae->bd[i].width / 2 - 1) / BLOCKSIZE;
			ae->bd[i].RightBottom.y = int(ae->bd[i].Pos.y + ae->bd[i].height / 2 - 1) / BLOCKSIZE;

			if (go->MapChip[ae->bd[i].LeftTop.y][ae->bd[i].LeftTop.x].Map != 0 || go->MapChip[ae->bd[i].LeftBottom.y][ae->bd[i].LeftBottom.x].Map != 0) {
				ae->bd[i].Pos.x = float((ae->bd[i].LeftBottom.x + 1) * BLOCKSIZE + ae->bd[i].width / 2);
			}
			if (go->MapChip[ae->bd[i].RightTop.y][ae->bd[i].RightTop.x].Map != 0 || go->MapChip[ae->bd[i].RightBottom.y][ae->bd[i].RightBottom.x].Map != 0) {
				ae->bd[i].Pos.x = float((ae->bd[i].RightBottom.x) * BLOCKSIZE - ae->bd[i].width / 2);
			}*/

			ae->bd[i].Pos.y += ae->bd[i].velocity.y;

			ae->bd[i].velocity.y += 0.5f;

		}

		//寿命
		if (ae->bd[i].ActiveTimer <= 0) {
			ae->bd[i].IsActive = false;
		}

	}

}

//プレイヤー死亡時のエフェクトの描画処理の関数
void DeathEffectDraw(AllEffect* ae) {

	for (int i = 0; i < 15; i++) {
		if (ae->bd[i].IsActive) {
			Novice::DrawQuad(
				//左上
				int(ae->bd[i].Pos.x - 4),
				int(ae->bd[i].Pos.y - 4),

				//右上
				int(ae->bd[i].Pos.x + 4),
				int(ae->bd[i].Pos.y - 4),

				//左下
				int(ae->bd[i].Pos.x - 4),
				int(ae->bd[i].Pos.y + 4),

				//右下
				int(ae->bd[i].Pos.x + 4),
				int(ae->bd[i].Pos.y + 4),

				//画像上の座標
				0, 0,

				//横幅、縦幅
				16, 16,

				//テクスチャハンドル
				ae->bd[0].image,

				//色
				WHITE
			);
		}
	}

}


//エフェクト生成関数
void CCEffectGenerate(AllEffect* ae, GameObject* go, int y, int x) {

	//乱数値の取得
	srand((unsigned)time(NULL));



	//エフェクトの生成を1フレーム処理で生成
	if (go->MapChip[y][x].Map == 2 && go->player.select[y][x]) {

		for (int i = 0; i < CCEffectNum; i++) {

			//生成数が上限になるまでループ
			while (1) {

				//線形探索で使用されていないものからフラグを立てる
				if (!ae->cc[i].IsActive) {

					//座標を獲得
					ae->cc[i].Pos = go->MapChip[y][x].Pos;

					//角度の取得
					ae->cc[i].Rdegree = float(rand() % 180);

					//速さを取得
					ae->cc[i].speed = float(rand() % 5 + 5);

					//角度の変換
					ae->cc[i].Rtheta = (ae->cc[i].Rdegree / 180.0f) * 3.1415f;

					//ベクトルの作成
					ae->cc[i].Vector.x = cosf(ae->cc[i].Rtheta);
					ae->cc[i].Vector.y = sinf(ae->cc[i].Rtheta);

					//速度の作成
					ae->cc[i].Velocity.x = ae->cc[i].Vector.x * ae->cc[i].speed;
					ae->cc[i].Velocity.y = ae->cc[i].Vector.y * ae->cc[i].speed;

					//最後にフラグを立てる
					ae->cc[i].IsActive = true;

					break;
				}

				//生成したエフェクトをカウント
				go->MapChip[y][x].GenarateEffectNum++;
				if (go->MapChip[y][x].GenarateEffectNum >= 20) {
					go->MapChip[y][x].IsEffectGenarated = true;
					break;
				}
			}

			if (go->MapChip[y][x].IsEffectGenarated) {
				break;
			}

		}


	}
}
//エフェクトの動きを管理する関数
void CCEffectMovement(AllEffect* ae){

	for (int i = 0; i < CCEffectNum; i++) {
		if (ae->cc[i].IsActive) {

			//寿命を減らす
			ae->cc[i].ActiveTimer--;

			//上にふわっとさせたい
			ae->cc[i].Velocity.y -= ae->cc[i].Acceleration.y;

			//動かす
			ae->cc[i].Pos.x += ae->cc[i].Velocity.x;
			ae->cc[i].Pos.y += ae->cc[i].Velocity.y;

			//回転用の角度の増減
			ae->cc[i].degree++;

			//回転用の角度の変換
			ae->cc[i].theta = (ae->cc[i].degree / 180.0f) * 3.1415f;

			//透明度を上げる
			//ae->cc[i].color -= 0x00000004;

			//寿命が尽きたらフラグを折る
			if (ae->cc[i].ActiveTimer <= 0) {
				ae->cc[i].IsActive = false;

				//タイマーのリセット
				ae->cc[i].ActiveTimer = 60;
			}

			//四つ角の情報の更新
			SetFourVertexes(&ae->cc[i]);

			//回転させる
			MakeRotatePos(&ae->cc[i]);
		}

	}
}

//上二つの関数をまとめる関数
void CCEffect(AllEffect* ae, GameObject* go) {

	//エフェクトの生成
	for (int i = 0; i < VerBlockNum; i++) {
		for (int j = 0; j < HolBlockNum; j++) {
			CCEffectGenerate(ae, go, i, j);
		}
	}

	//エフェクトの動き
	CCEffectMovement(ae);
}

void DrawCCEffect(AllEffect* ae) {

	for (int i = 0; i < CCEffectNum; i++) {

		Novice::DrawQuad(
			//左上
			int(ae->cc[i].Pos.x + ae->cc[i].BufRotateLeftTop.x),
			int(ae->cc[i].Pos.y + ae->cc[i].BufRotateLeftTop.y),

			//右上
			int(ae->cc[i].Pos.x + ae->cc[i].BufRotateRightTop.x),
			int(ae->cc[i].Pos.y + ae->cc[i].BufRotateRightTop.y),

			//左下
			int(ae->cc[i].Pos.x + ae->cc[i].BufRotateLeftBottom.x),
			int(ae->cc[i].Pos.y + ae->cc[i].BufRotateLeftBottom.y),

			//右下
			int(ae->cc[i].Pos.x + ae->cc[i].BufRotateRightBottom.x),
			int(ae->cc[i].Pos.y + ae->cc[i].BufRotateRightBottom.y),

			//画像上の座標
			0, 0,

			//横幅、縦幅
			32, 32,

			//テクスチャハンドル
			ae->cc[0].image,
			//色
			ae->cc[i].color
		);
	}
}

//エフェクトのデバッグ表示
void EffectDebugPrintf(AllEffect* ae) {
	Novice::ScreenPrintf(50,50,"IsActive:%d", ae->cc[100].IsActive);

	Novice::ScreenPrintf(50, 100, "PosX:%f", ae->cc[100].Pos.x);
	Novice::ScreenPrintf(50, 120, "PosY:%f", ae->cc[100].Pos.y);


}