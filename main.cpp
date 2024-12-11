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
	GameObject gameobject;
	AllEffect alleffect;
	Key key;
	System system;
	Audio audio;

	//構造体のアドレスを格納する変数の宣言
	GameObject* p_gameobject = &gameobject;
	AllEffect* p_alleffect = &alleffect;
	Key* p_key = &key;
	System* p_system = &system;
	Audio* p_audio = &audio;


	//初期化関数
	PlayerInitialize(p_gameobject);
	BuddyInitialize(p_gameobject);
	//StarInitialize(p_gameobject);
	EnemyInitialize(p_gameobject);
	StageInitialize(p_gameobject);
	SystemInitialize(p_system);
	Effectinitialize(p_alleffect);

	StageSelectInitialize(p_system);

	DeathEffectInitialze(p_alleffect);
	TitleInitialize(p_gameobject,p_system);
	UIInitialize(p_system);
	SceneChangeInitialize(p_system);


	//ステージ情報の関数
	teststage(p_gameobject);

	//クリア画面の変数初期化
	ClearSceneInitialize(p_system);

	//音関連の読み込み
	LoadAudio(p_audio);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(key.preKeys, key.keys, 256);
		Novice::GetHitKeyStateAll(key.keys);

		switch (system.scene) {
		case Title:

			// タイトルの処理の関数
			TitleScene(p_key, p_system);

			// タイトルのステージの初期化
			TitleStage(p_gameobject);

			//四点の座標を取得
			for (int i = 0; i < VerBlockNum; i++) {
				for (int j = 0; j < HolBlockNum; j++) {
					SetFourVertexes(&p_gameobject->MapChip[i][j]);
				}
			}

			/*===========================================
						相棒の更新処理
			===========================================*/

			//四点の座標を取得
			SetFourVertexes(&p_gameobject->buddy);

			//相棒の動きの関数
			BuddyMove(p_gameobject, p_system);
			BuddyAnimation(p_gameobject);

			/*===========================================
						タイトルの音の処理
			===========================================*/
			TitleAudio(p_audio, p_key);

			// タイトルの描画処理
			TitleDraw(p_system,p_gameobject);

			// 相棒の描画
			BuddyDraw(p_gameobject);

			

			break;

		case StageSelect:

			StageselectUpdate(p_system, p_key, p_audio, p_gameobject);
			DrawStageSelect(p_system, p_gameobject);
			/*===========================================
						ステージセレクトの音の処理
			===========================================*/

			StageSelectAudio(p_audio, p_key);


			break;

		case Play:


			/*===========================================
						ゲーム中の音の処理
			===========================================*/
			//if (!p_gameobject->buddy.IsClear) {
				GameAudio(p_audio, p_key);
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
			SetFourVertexes(&p_gameobject->player);

			//プレイヤーの動きの関数
			PlayerMove(p_gameobject, p_key);

			//色を付ける・回収する関数
			ColorSystem(p_gameobject, p_key, p_audio);

			//予測8マスを作る
			Predicition8Block(p_gameobject);

			// アニメーションの関数
			PlayerAnimation(p_gameobject);

			/*===========================================
						相棒の更新処理
			===========================================*/

			//四点の座標を取得
			SetFourVertexes(&p_gameobject->buddy);

			//相棒の動きの関数
			BuddyMove(p_gameobject, p_system);
			BuddyAnimation(p_gameobject);

			/*===========================================
						敵の更新処理
			===========================================*/

			for (int i = 0; i<10; ++i) {

				//四点の座標を取得
				SetFourVertexes(&p_gameobject->enemy[i]);

			}

			//相棒の動きの関数
			EnemyMove(p_gameobject, p_audio);

			/*===========================================
						星の更新処理
			===========================================*/
			//StarMove(p_gameobject);
			StarGet(p_gameobject, p_audio);

			/*===========================================
						ワープボックスの更新処理
			===========================================*/
			WarpBox(p_gameobject);

			/*===========================================
						ゴールの更新処理
			===========================================*/
			GoalMove(p_gameobject);

			/*===========================================
						ステージの更新処理
			===========================================*/

			//上の関数をまとめる関数
			//StageGenerate(p_gameobject,p_system);

			//四点の座標を取得
			for (int i = 0; i < VerBlockNum; i++) {
				for (int j = 0; j < HolBlockNum; j++) {
					SetFourVertexes(&p_gameobject->MapChip[i][j]);
				}
			}

			BlockAnimation(p_gameobject,p_key);


			ClearScene(p_gameobject, p_key, p_system,p_audio);


			/*===========================================
						UIの更新処理
			===========================================*/
			PlayUI(p_system, p_gameobject, p_key);


			/*===========================================
						エフェクトの更新処理
			===========================================*/
			CCEffect(p_alleffect, p_gameobject);

			DeathEffect(p_alleffect, p_gameobject);


			/*===========================================
						Rキーでリスタート
			===========================================*/
			//Restart(p_gameobject, p_key, p_system);


			///
			/// ↑更新処理ここまで
			///

			///
			/// ↓描画処理ここから
			///


			/*===========================================
						ステージの描画処理
			===========================================*/
			StageDraw(p_gameobject);

			/*===========================================
						プレイヤーの描画処理
			===========================================*/
			PlayerDraw(p_gameobject);
			PlayUIDraw(p_system);

			/*===========================================
						星の描画処理
			===========================================*/
			//StarDraw(p_gameobject);

			/*===========================================
						相棒の描画処理
			===========================================*/
			BuddyDraw(p_gameobject);

			/*===========================================
						敵の描画処理
			===========================================*/
			EnemyDraw(p_gameobject);

			/*===========================================
						エフェクトの描画処理
			===========================================*/
        	DrawCCEffect(p_alleffect);

			//EffectDebugPrintf(p_alleffect);

			DeathEffectDraw(p_alleffect);

			/*===========================================
						クリア画面の描画処理
			===========================================*/
			ClearSceneDraw(p_gameobject, p_system);


			break;
		}

		//シーン遷移
		RestartDraw(p_system);
		SceneChangeFunction(p_system);

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (key.preKeys[DIK_ESCAPE] == 0 && key.keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
