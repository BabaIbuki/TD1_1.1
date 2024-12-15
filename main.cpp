//ソースファイルの読み込み
#include <Novice.h>

//ヘッダーファイルの読み込み（アルファベット順）
#include"buddy.h"
#include"enemy.h"
#include"enum.h"
#include"define.h"
//#include "initialize.h"
#include"star.h"
#include"structer.h"
#include "title.h"
#include"gimmick.h"
#include"Player.h"
#include"stage.h"
#include"common.h"
#include"system.h"
#include"ClearScene.h"
#include"Audio.h"
#include"effect.h"
#include "UI.h"
#include"stageselect.h"


//テスト

const char kWindowTitle[] = "1106_迷友";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WindowWidth, WindowHeight);

	//構造体の実体化
	GameObject* gameobject = new GameObject;
	AllEffect* alleffect = new AllEffect;
	Key* key = new Key;
	System* system = new System;
	Audio* audio = new Audio;

	//構造体のアドレスを格納する変数の宣言
	//GameObject* p_gameobject = &gameobject;
	//AllEffect* p_alleffect = &alleffect;
	//Key* p_key = &key;
	//System* p_system = &system;
	//Audio* p_audio = &audio;


	//初期化関数
	PlayerInitialize(gameobject);
	BuddyInitialize(gameobject);
	//StarInitialize(p_gameobject);
	EnemyInitialize(gameobject);
	StageInitialize(gameobject);
	SystemInitialize(system);
	Effectinitialize(alleffect);

	StageSelectInitialize(system);

	DeathEffectInitialze(alleffect);
	TitleInitialize(gameobject, system);
	UIInitialize(system);
	SceneChangeInitialize(system);


	//ステージ情報の関数
	teststage(gameobject);

	//クリア画面の変数初期化
	ClearSceneInitialize(system);

	//音関連の読み込み
	LoadAudio(audio);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(key->preKeys, key->keys, 256);
		Novice::GetHitKeyStateAll(key->keys);

		switch (system->scene) {
		case Title:

			// タイトルの処理の関数
			TitleScene(key, system);

			// タイトルのステージの初期化
			TitleStage(gameobject);

			//四点の座標を取得
			for (int i = 0; i < VerBlockNum; i++) {
				for (int j = 0; j < HolBlockNum; j++) {
					SetFourVertexes(&gameobject->MapChip[i][j]);
				}
			}

			/*===========================================
						相棒の更新処理
			===========================================*/

			//四点の座標を取得
			SetFourVertexes(&gameobject->buddy);

			//相棒の動きの関数
			BuddyMove(gameobject, system);
			BuddyAnimation(gameobject);

			/*===========================================
						タイトルの音の処理
			===========================================*/
			TitleAudio(audio, key);

			// タイトルの描画処理
			TitleDraw(system, gameobject);

			// 相棒の描画
			BuddyDraw(gameobject);



			break;

		case StageSelect:

			StageselectUpdate(system, key, audio, gameobject);
			DrawStageSelect(system, gameobject);
			/*===========================================
						ステージセレクトの音の処理
			===========================================*/

			StageSelectAudio(audio, key);


			break;

		case Play:


			/*===========================================
						ゲーム中の音の処理
			===========================================*/
			//if (!p_gameobject->buddy.IsClear) {
			GameAudio(audio, key);
			//}
			/*else {
				ClearAudio(p_audio, p_key);
			}*/

			/*===========================================
						ステージの更新処理
			===========================================*/

			//Initialize(p_gameobject,p_key);

			/*===========================================
						プレイヤーの更新処理
			===========================================*/

			//ゲームプレイ中の初期化
			//PlayerGameInitialize(p_gameobject);

			//四点の座標を取得
			SetFourVertexes(&gameobject->player);

			//プレイヤーの動きの関数
			PlayerMove(gameobject, key);

			//色を付ける・回収する関数
			ColorSystem(gameobject, key, audio);

			//予測8マスを作る
			Predicition8Block(gameobject);

			// アニメーションの関数
			PlayerAnimation(gameobject);

			/*===========================================
						相棒の更新処理
			===========================================*/

			//四点の座標を取得
			SetFourVertexes(&gameobject->buddy);

			//相棒の動きの関数
			BuddyMove(gameobject, system);
			BuddyAnimation(gameobject);

			/*===========================================
						敵の更新処理
			===========================================*/

			for (int i = 0; i < 10; ++i) {

				//四点の座標を取得
				SetFourVertexes(&gameobject->enemy[i]);

			}

			//相棒の動きの関数
			EnemyMove(gameobject, audio);

			/*===========================================
						星の更新処理
			===========================================*/
			//StarMove(gameobject);
			StarGet(gameobject, audio);

			/*===========================================
						ワープボックスの更新処理
			===========================================*/
			WarpBox(gameobject);

			/*===========================================
						ゴールの更新処理
			===========================================*/
			GoalMove(gameobject);

			/*===========================================
						ステージの更新処理
			===========================================*/

			//上の関数をまとめる関数
			//StageGenerate(gameobject,system);

			//四点の座標を取得
			for (int i = 0; i < VerBlockNum; i++) {
				for (int j = 0; j < HolBlockNum; j++) {
					SetFourVertexes(&gameobject->MapChip[i][j]);
				}
			}

			BlockAnimation(gameobject, key);


			ClearScene(gameobject, key, system, audio);


			/*===========================================
						UIの更新処理
			===========================================*/
			PlayUI(system, gameobject, key);


			/*===========================================
						エフェクトの更新処理
			===========================================*/
			CCEffect(alleffect, gameobject);

			DeathEffect(alleffect, gameobject);


			/*===========================================
						Rキーでリスタート
			===========================================*/
			//Restart(gameobject, p_key, system);

			if (key->keys[DIK_Q]) {
				system->scene = StageSelect;
			}


			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///


			/*===========================================
						ステージの描画処理
			===========================================*/
			StageDraw(gameobject);

			/*===========================================
						プレイヤーの描画処理
			===========================================*/
			PlayerDraw(gameobject);
			PlayUIDraw(system);

			/*===========================================
						星の描画処理
			===========================================*/
			//StarDraw(gameobject);

			/*===========================================
						相棒の描画処理
			===========================================*/
			BuddyDraw(gameobject);

			/*===========================================
						敵の描画処理
			===========================================*/
			EnemyDraw(gameobject);

			/*===========================================
						エフェクトの描画処理
			===========================================*/
			DrawCCEffect(alleffect);

			//EffectDebugPrintf(p_alleffect);

			DeathEffectDraw(alleffect);

			/*===========================================
						クリア画面の描画処理
			===========================================*/
			ClearSceneDraw(gameobject, system);


			break;
		}

		//シーン遷移
		RestartDraw(system);
		SceneChangeFunction(system);

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (key->preKeys[DIK_ESCAPE] == 0 && key->keys[DIK_ESCAPE] != 0) {
			delete gameobject;
			delete alleffect;
			delete key;
			delete system;
			delete audio;
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
