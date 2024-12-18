#include<Novice.h>
#include"structer.h"
#include"common.h"
#include "Audio.h"
#include "stage.h"
#include "buddy.h"
#include "enemy.h"
#include <corecrt_math.h>

//初期化関数
void StageSelectInitialize(System* system) {

	//選択
	system->stageselect.select = 1;

	//線形補完周りの変数
	system->stageselect.t = 0.0f;

	//ステージ画像の変数の初期化
	for (int i = 0; i < StageNum; i++) {

		//座標
		system->stageselect.siobj[i].Pos.x = float((WindowWidth / 2) + WindowWidth * i);
		system->stageselect.siobj[i].Pos.y = float((WindowHeight / 2) + 170.0f);

		system->stageselect.siobj[i].PrePos.x = system->stageselect.siobj[i].Pos.x;

		system->stageselect.siobj[i].width = 190 * 3;
		system->stageselect.siobj[i].height = 120 * 3;

		//線形補完の前後の点
		system->stageselect.siobj[i].FrontPoint = system->stageselect.siobj[i].PrePos.x - /*((system->stageselect.select - 1) **/ WindowWidth;
		system->stageselect.siobj[i].BackPoint = system->stageselect.siobj[i].PrePos.x + /*((system->stageselect.select + 1) **/ WindowWidth;
	}

	//線形補完で動かす時間
	system->stageselect.time = 2.0f;

	system->stageselect.DecreaseFlag = false;
	system->stageselect.IncreaseFlag = false;

	//画像の取り込み
	system->stageselect.siobj[0].image = Novice::LoadTexture("./MyResources./stage./stage1New.png");
	system->stageselect.siobj[1].image = Novice::LoadTexture("./MyResources./stage./stage2.png");
	system->stageselect.siobj[2].image = Novice::LoadTexture("./MyResources./stage./stage3New.png");
	system->stageselect.siobj[3].image = Novice::LoadTexture("./MyResources./stage./stage4New.png");
	system->stageselect.siobj[4].image = Novice::LoadTexture("./MyResources./stage./stage5.png");
	system->stageselect.siobj[5].image = Novice::LoadTexture("./MyResources./stage./stage6.png");
	system->stageselect.siobj[6].image = Novice::LoadTexture("./MyResources./stage./stage7New.png");
	system->stageselect.siobj[7].image = Novice::LoadTexture("./MyResources./stage./stage8New.png");
	system->stageselect.siobj[8].image = Novice::LoadTexture("./MyResources./stage./stage9New.png");
	system->stageselect.siobj[9].image = Novice::LoadTexture("./MyResources./stage./stage10.png");
	system->stageselect.siobj[10].image = Novice::LoadTexture("./MyResources./stage./stage11New.png");
	system->stageselect.siobj[11].image = Novice::LoadTexture("./MyResources./stage./stage12New.png");
	system->stageselect.siobj[12].image = Novice::LoadTexture("./MyResources./stage./stage13New.png");
	system->stageselect.siobj[13].image = Novice::LoadTexture("./MyResources./stage./stage14New.png");
	system->stageselect.siobj[14].image = Novice::LoadTexture("./MyResources./stage./stage15.png");


	//ステージ画像の下敷き画像の変数の初期化
	for (int i = 0; i < StageNum; i++) {
		system->stageselect.sibobj[i].width = 420.0f;
		system->stageselect.sibobj[i].height = 260.0f;
	}

	//画像の取り込み
	system->stageselect.sibobj[0].image = Novice::LoadTexture("./MyResources./stage./StageBack.png");

	//背景の変数初期化
	system->stageselect.bg.Pos.x = WindowWidth / 2;
	system->stageselect.bg.Pos.y = WindowHeight / 2;

	system->stageselect.bg.width = WindowWidth;
	system->stageselect.bg.height = WindowHeight;

	system->stageselect.bg.Scroll = 0.0f;

	system->stageselect.bg.speed = 0.5f;

	//画像の取り込み
	system->stageselect.bg.image = Novice::LoadTexture("./MyResources./stage./BackGround.png");


	//PushＪ UI
	system->stageselect.psj.Pos.x = 1050.0f;

	system->stageselect.psj.width = 200.0f;
	system->stageselect.psj.height = 64.0f;

	system->stageselect.psj.degree = 0.0f;
	system->stageselect.psj.theta = 0.0f;

	system->stageselect.psj.color = WHITE;

	system->stageselect.psj.image = Novice::LoadTexture("./MyResources./ClearDecideUI.png");


	//画面上部の黒
	system->stageselect.bbg[0].Pos.x = float(WindowWidth / 2.0f);
	system->stageselect.bbg[1].Pos.x = float(WindowWidth / 2.0f);

	system->stageselect.bbg[0].Pos.y = 120.0f;
	system->stageselect.bbg[1].Pos.y = 100.0f;

	system->stageselect.bbg[0].width = WindowWidth;
	system->stageselect.bbg[0].height = 200;

	system->stageselect.bbg[1].width = WindowWidth;
	system->stageselect.bbg[1].height = 200;

	system->stageselect.bbg[0].color = BLACK;
	system->stageselect.bbg[1].color = 0x3ea6abff;

	system->stageselect.bbg[0].image = Novice::LoadTexture("./MyResources./ClearBackUI.png");
	system->stageselect.bbg[1].image = Novice::LoadTexture("./MyResources./ClearBackUI.png");


	//「stage」画像と数の画像	
	for (int i = 0; i < StageNum; i++) {
		system->stageselect.si[i].Pos.y = 330.0f;
		system->stageselect.sn[i].Pos.y = 330.0f;

		system->stageselect.si[i].width = 200.0f;
		system->stageselect.si[i].height = 100.0f;

		system->stageselect.sn[i].width = 64.0f;
		system->stageselect.sn[i].height = 64.0f;

		system->stageselect.si[i].degree = 120.0f;
		system->stageselect.si[i].theta = 0.0f;

	}
	system->stageselect.si[0].image = Novice::LoadTexture("./MyResources./STAGE.png");
	system->stageselect.sn[0].image = Novice::LoadTexture("./MyResources./Num.png");


	//星の画像
	for (int i = 0; i < StageNum; i++) {

		system->stageselect.starimage[i].Pos.y = 105.0f;

		system->stageselect.starimage[i].width = (128.0f * 4.0f);
		system->stageselect.starimage[i].height = 128.0f;

		system->stageselect.starimage[0].image = Novice::LoadTexture("./MyResources./GetStar.png");

	}

	//クリアしたかどうかの画像
	system->stageselect.ci.image = Novice::LoadTexture("./MyResources./clear.png");

	system->stageselect.ci.Pos.y = 380.0f;
	system->stageselect.ci.Pos.x = 950.0f;

	system->stageselect.ci.width = 300.0f;
	system->stageselect.ci.height = 100.0f;

	system->stageselect.ci.DrawWidth = 300.0f;
	system->stageselect.ci.DrawHeight = 100.0f;

	//角度
	system->stageselect.ci.theta = (10.0f / 180.0f) * 3.1415f;
}


//更新処理
//ステージ画像の動きを管理する関数
void StageImageMovement(System* system) {

	for (int i = 0; i < StageNum; i++) {

		//線形補完前後２点を作る

		if (system->stageselect.select != 1 && system->stageselect.select != 15) {
			system->stageselect.siobj[i].FrontPoint = system->stageselect.siobj[i].PrePos.x - /*((system->stageselect.select - 1) **/ WindowWidth;
			system->stageselect.siobj[i].BackPoint = system->stageselect.siobj[i].PrePos.x + /*((system->stageselect.select + 1) **/ WindowWidth;
		}
		else if (system->stageselect.select == 1) {
			system->stageselect.siobj[i].FrontPoint = system->stageselect.siobj[i].PrePos.x + (WindowWidth * 14);
			system->stageselect.siobj[i].BackPoint = system->stageselect.siobj[i].PrePos.x + /*((system->stageselect.select + 1) **/ WindowWidth;
		}
		else {
			system->stageselect.siobj[i].FrontPoint = system->stageselect.siobj[i].PrePos.x - /*((system->stageselect.select - 1) **/ WindowWidth;
			system->stageselect.siobj[i].BackPoint = system->stageselect.siobj[i].PrePos.x - (WindowWidth * 14);
		}
	}

	if (system->stageselect.DecreaseFlag) {
		//いっこ前の点
		for (int i = 0; i < StageNum; i++) {
			system->stageselect.siobj[i].Pos.x = ((1.0f - system->stageselect.t) * system->stageselect.siobj[i].PrePos.x) + (system->stageselect.t * system->stageselect.siobj[i].FrontPoint);
		}

		if (system->stageselect.t >= 1.0f) {
			for (int i = 0; i < StageNum; i++) {

				system->stageselect.siobj[i].Pos.x = system->stageselect.siobj[i].FrontPoint;
				system->stageselect.siobj[i].PrePos.x = system->stageselect.siobj[i].Pos.x;
			}
			system->stageselect.t = 0.0f;
			system->stageselect.time = 2.0f;
			system->stageselect.DecreaseFlag = false;
		}
	}

	if (system->stageselect.IncreaseFlag) {
		//いっこ後の点
		for (int i = 0; i < StageNum; i++) {
			system->stageselect.siobj[i].Pos.x = ((1.0f - system->stageselect.t) * system->stageselect.siobj[i].PrePos.x) + (system->stageselect.t * system->stageselect.siobj[i].BackPoint);
		}

		if (system->stageselect.t >= 1.0f) {
			for (int i = 0; i < StageNum; i++) {

				system->stageselect.siobj[i].Pos.x = system->stageselect.siobj[i].BackPoint;
				system->stageselect.siobj[i].PrePos.x = system->stageselect.siobj[i].Pos.x;
			}
			system->stageselect.t = 0.0f;
			system->stageselect.time = 2.0f;
			system->stageselect.IncreaseFlag = false;
		}
	}


	//ｔを増やす
	if (system->stageselect.DecreaseFlag || system->stageselect.IncreaseFlag) {
		system->stageselect.time += 2.6f;
		system->stageselect.t += 1.0f / system->stageselect.time;
	}


}


//ステージ画像の下敷きの動きを管理する関数
void StageImageBackImageMovement(System* system) {
	for (int i = 0; i < StageNum; i++) {

		//座標を一致させる
		system->stageselect.sibobj[i].Pos = system->stageselect.siobj[i].Pos;

		//四つ角を設定する
		SetFourVertexes(&system->stageselect.sibobj[i]);
	}
}


//背景の更新処理
void BackGoundMovement(System* system) {

	//四つ角を設定する
	SetFourVertexes(&system->stageselect.bg);
	SetFourVertexes(&system->stageselect.bbg[0]);
	SetFourVertexes(&system->stageselect.bbg[1]);


	//スクロール値を変える
	system->stageselect.bg.Scroll += system->stageselect.bg.speed;

	//スクロールが一定値になったら0にする
	if (system->stageselect.bg.Scroll >= 419) {
		system->stageselect.bg.Scroll = 0.0f;
	}
}

//「stage」画像と数字の画像
void StageNumMovement(System* system) {

	for (int i = 0; i < StageNum; i++) {
		SetFourVertexes(&system->stageselect.si[i]);
		SetFourVertexes(&system->stageselect.sn[i]);


		//座標を設定
		system->stageselect.si[i].Pos.x = system->stageselect.sibobj[i].Pos.x - 40.0f;
		system->stageselect.sn[i].Pos.x = system->stageselect.sibobj[i].Pos.x + 100.0f;


		//角度を増やす
		system->stageselect.si[i].degree += 2;

		//角度の変換
		system->stageselect.si[i].theta = (3.1415f / 180.0f) * system->stageselect.si[i].degree;

		//上下にゆっくりと動かす
		system->stageselect.si[i].Pos.y = sinf(system->stageselect.si[i].theta) * 15 + 300;
		system->stageselect.sn[i].Pos.y = sinf(system->stageselect.si[i].theta) * 15 + 300;

	}
}

//星の画像の動きの関数
void StarImageMovement(System* system) {
	for (int i = 0; i < StageNum; i++) {
		system->stageselect.starimage[i].Pos.x = system->stageselect.siobj[i].Pos.x;

		SetFourVertexes(&system->stageselect.starimage[i]);
	}
}

//UIの動きをまとめた関数（StageSelect UI）
void SSUIMovement(System* system) {
	SetFourVertexes(&system->stageselect.psj);

	//角度を増やす
	system->stageselect.psj.degree += 2;

	//角度の変換
	system->stageselect.psj.theta = (3.1415f / 180.0f) * system->stageselect.psj.degree;

	//上下にゆっくりと動かす
	system->stageselect.psj.Pos.y = sinf(system->stageselect.psj.theta) * 15 + 650;

}

//「clear」画像
void ClearImageFun(System* system) {
	//SetFourVertexes(&system->stageselect.ci);
	DrawFourVertexes(&system->stageselect.ci);
	MakeRotatePos(&system->stageselect.ci);

	system->stageselect.ci.degree += 2;

	//拡縮する
	system->stageselect.ci.DrawWidth = sinf((system->stageselect.ci.degree / 180.0f) * 3.1415f) * 50 + 300.0f;
	system->stageselect.ci.DrawHeight = sinf((system->stageselect.ci.degree / 180.0f) * 3.1415f) * 50 + 105.0f;

}

//セレクトを変えるだけ
void StageselectUpdate(System* system, Key* key, Audio* audio, GameObject* go) {

	for (int i = 0; i < StageNum; i++) {
		SetFourVertexes(&system->stageselect.siobj[i]);
	}

	StageImageMovement(system);

	StageImageBackImageMovement(system);

	BackGoundMovement(system);

	SSUIMovement(system);

	StageNumMovement(system);

	StarImageMovement(system);

	ClearImageFun(system);

	int MaxNum = StageNum;

	if (system->stageselect.t == 0.0f) {

		if (key->keys[DIK_A]) {
			if (system->stageselect.select == 1) {
				system->stageselect.select = MaxNum;
				//SE
				Novice::PlayAudio(audio->se.select, false, 1.0f);
			}
			else {
				system->stageselect.select--;
				//SE
				Novice::PlayAudio(audio->se.select, false, 1.0f);
			}
			//system->stageselect.DecreaseFlag = true;
			system->stageselect.IncreaseFlag = true;
		}

		if (key->keys[DIK_D]) {
			if (system->stageselect.select == MaxNum) {
				system->stageselect.select = 1;
				//SE
				Novice::PlayAudio(audio->se.select, false, 1.0f);
			}
			else {
				system->stageselect.select++;
				//SE
				Novice::PlayAudio(audio->se.select, false, 1.0f);
			}
			//system->stageselect.IncreaseFlag =false;
			system->stageselect.DecreaseFlag = true;

		}
	}


	if (key->keys[DIK_J] && !key->preKeys[DIK_J]) {
		// シーンを切り替える
		system->sc.changeFlag = true;
		//SE
		Novice::PlayAudio(audio->se.decide, false, 1.0f);
	}
	if (system->sc.changeFlag && system->sc.Pos[3].x == 0.0f) {
		BuddyGameInitialize(go);
		EnemyMoveGameInitialize(go);
		StageGenerate(go, system);
		system->scene++;
		system->sc.changeFlag = false;
	}
	if (key->keys[DIK_J]) {
		system->stageselect.psj.color = 0x333333ff;
	}
	else {
		system->stageselect.psj.color = WHITE;
	}



}


void DrawStageSelect(System* system, GameObject* go) {

	//背景の描画
	Novice::DrawQuad(
		//左上
		int(system->stageselect.bg.DrawLeftTop.x),
		int(system->stageselect.bg.DrawLeftTop.y),

		//右上
		int(system->stageselect.bg.DrawRightTop.x),
		int(system->stageselect.bg.DrawRightTop.y),

		//左下
		int(system->stageselect.bg.DrawLeftBottom.x),
		int(system->stageselect.bg.DrawLeftBottom.y),

		//右下
		int(system->stageselect.bg.DrawRightBottom.x),
		int(system->stageselect.bg.DrawRightBottom.y),

		//画像上の座標
		int(system->stageselect.bg.Scroll), int(system->stageselect.bg.Scroll),

		//横幅、縦幅
		int(system->stageselect.bg.width), int(system->stageselect.bg.height),

		//テクスチャハンドル
		system->stageselect.bg.image,

		//色
		WHITE
	);

	//画面上部の黒Box
	for (int i = 0; i < 2; i++) {
		Novice::DrawQuad(
			//左上
			int(system->stageselect.bbg[i].DrawLeftTop.x),
			int(system->stageselect.bbg[i].DrawLeftTop.y),

			//右上
			int(system->stageselect.bbg[i].DrawRightTop.x),
			int(system->stageselect.bbg[i].DrawRightTop.y),

			//左下
			int(system->stageselect.bbg[i].DrawLeftBottom.x),
			int(system->stageselect.bbg[i].DrawLeftBottom.y),

			//右下
			int(system->stageselect.bbg[i].DrawRightBottom.x),
			int(system->stageselect.bbg[i].DrawRightBottom.y),

			//画像上の座標
			0, 0,

			//横幅、縦幅
			int(system->stageselect.bbg[i].width), int(system->stageselect.bbg[i].height),

			//テクスチャハンドル
			system->stageselect.bbg[i].image,

			//色
			system->stageselect.bbg[i].color
		);
	}

	//Push J
	Novice::DrawQuad(
		//左上
		int(system->stageselect.psj.DrawLeftTop.x),
		int(system->stageselect.psj.DrawLeftTop.y),

		//右上
		int(system->stageselect.psj.DrawRightTop.x),
		int(system->stageselect.psj.DrawRightTop.y),

		//左下
		int(system->stageselect.psj.DrawLeftBottom.x),
		int(system->stageselect.psj.DrawLeftBottom.y),

		//右下
		int(system->stageselect.psj.DrawRightBottom.x),
		int(system->stageselect.psj.DrawRightBottom.y),

		//画像上の座標
		0, 0,

		//横幅、縦幅
		int(system->stageselect.psj.width), int(system->stageselect.psj.height),

		//テクスチャハンドル
		system->stageselect.psj.image,

		//色
		system->stageselect.psj.color
	);

	for (int i = 0; i < StageNum; i++) {





		Novice::DrawQuad(
			//左上
			int(system->stageselect.siobj[i].DrawLeftTop.x),
			int(system->stageselect.siobj[i].DrawLeftTop.y),

			//右上
			int(system->stageselect.siobj[i].DrawRightTop.x),
			int(system->stageselect.siobj[i].DrawRightTop.y),

			//左下
			int(system->stageselect.siobj[i].DrawLeftBottom.x),
			int(system->stageselect.siobj[i].DrawLeftBottom.y),

			//右下
			int(system->stageselect.siobj[i].DrawRightBottom.x),
			int(system->stageselect.siobj[i].DrawRightBottom.y),

			//画像上の座標
			0, 30,

			//横幅、縦幅
			1216, 768,

			//テクスチャハンドル
			system->stageselect.siobj[i].image,

			//色
			WHITE
		);


		//「stage」画像の描画
		Novice::DrawQuad(
			//左上
			int(system->stageselect.si[i].DrawLeftTop.x),
			int(system->stageselect.si[i].DrawLeftTop.y),

			//右上
			int(system->stageselect.si[i].DrawRightTop.x),
			int(system->stageselect.si[i].DrawRightTop.y),

			//左下
			int(system->stageselect.si[i].DrawLeftBottom.x),
			int(system->stageselect.si[i].DrawLeftBottom.y),

			//右下
			int(system->stageselect.si[i].DrawRightBottom.x),
			int(system->stageselect.si[i].DrawRightBottom.y),

			//画像上の座標
			0, 0,

			//横幅、縦幅
			400, 200,

			//テクスチャハンドル
			system->stageselect.si[0].image,

			//色
			WHITE
		);


		//数の画像の描画
		Novice::DrawQuad(
			//左上
			int(system->stageselect.sn[i].DrawLeftTop.x),
			int(system->stageselect.sn[i].DrawLeftTop.y),

			//右上
			int(system->stageselect.sn[i].DrawRightTop.x),
			int(system->stageselect.sn[i].DrawRightTop.y),

			//左下
			int(system->stageselect.sn[i].DrawLeftBottom.x),
			int(system->stageselect.sn[i].DrawLeftBottom.y),

			//右下
			int(system->stageselect.sn[i].DrawRightBottom.x),
			int(system->stageselect.sn[i].DrawRightBottom.y),

			//画像上の座標
			i * 64, 0,

			//横幅、縦幅
			64, 64,

			//テクスチャハンドル
			system->stageselect.sn[0].image,

			//色
			WHITE
		);

		//星の画像の描画
		Novice::DrawQuad(
			//左上
			int(system->stageselect.starimage[i].DrawLeftTop.x),
			int(system->stageselect.starimage[i].DrawLeftTop.y),

			//右上
			int(system->stageselect.starimage[i].DrawRightTop.x),
			int(system->stageselect.starimage[i].DrawRightTop.y),

			//左下
			int(system->stageselect.starimage[i].DrawLeftBottom.x),
			int(system->stageselect.starimage[i].DrawLeftBottom.y),

			//右下
			int(system->stageselect.starimage[i].DrawRightBottom.x),
			int(system->stageselect.starimage[i].DrawRightBottom.y),

			//画像上の座標
			(128 * 4) * go->buddy.MaxStarCount[i], 0,

			//横幅、縦幅
			128 * 4, 128,

			//テクスチャハンドル
			system->stageselect.starimage[0].image,

			//色
			WHITE
		);

		//「clear」画像の描画
		if (system->IsClear[system->stageselect.select] && system->stageselect.t == 0.0f && !system->stageselect.IncreaseFlag) {
			Novice::DrawQuad(
				int(system->stageselect.ci.Pos.x + system->stageselect.ci.BufRotateLeftTop.x),
				int(system->stageselect.ci.Pos.y + system->stageselect.ci.BufRotateLeftTop.y),

				//右上
				int(system->stageselect.ci.Pos.x + system->stageselect.ci.BufRotateRightTop.x),
				int(system->stageselect.ci.Pos.y + system->stageselect.ci.BufRotateRightTop.y),

				//左下
				int(system->stageselect.ci.Pos.x + system->stageselect.ci.BufRotateLeftBottom.x),
				int(system->stageselect.ci.Pos.y + system->stageselect.ci.BufRotateLeftBottom.y),

				//右下
				int(system->stageselect.ci.Pos.x + system->stageselect.ci.BufRotateRightBottom.x),
				int(system->stageselect.ci.Pos.y + system->stageselect.ci.BufRotateRightBottom.y),

				//画像上の座標
				0, 0,

				//横幅、縦幅
				300, 100,

				//テクスチャハンドル
				system->stageselect.ci.image,

				//色
				WHITE
			);
		}

	}

	//デバッグ
	//Novice::ScreenPrintf(20, 20, "system->stageselect.select :%d", system->stageselect.select);
	//Novice::ScreenPrintf(20, 40, "t :%f", system->stageselect.t);

	//Novice::ScreenPrintf(20, 80, "Increase :%d", system->stageselect.IncreaseFlag);
	//Novice::ScreenPrintf(20, 100, "Decrease :%d", system->stageselect.DecreaseFlag);
}
