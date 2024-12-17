#pragma once

//ヘッダーファイルの読み込み
#include"structer.h"

//最初に読み込むステージ情報の初期化の関数
void StageInitialize(GameObject* go);

//ゲームプレイ中の初期化
//void StageGameInitialize(GameObject* go);


//ステージ情報の関数
void teststage(GameObject* go);

// 各ステージの情報の関数
void stage1(GameObject* go);
void stage2(GameObject* go);
void stage3(GameObject* go);
void stage4(GameObject* go);
void stage5(GameObject* go);
void stage6(GameObject* go);
void stage7(GameObject* go);
void stage8(GameObject* go);
void stage9(GameObject* go);
void stage10(GameObject* go);
void stage11(GameObject* go);
void stage12(GameObject* go);
void stage13(GameObject* go);
void stage14(GameObject* go);
void stage15(GameObject* go);

//上の関数をまとめる関数
void StageGenerate(GameObject* go, System* system);

//ステージの描画
void StageDraw(GameObject* go);

//ブロックのアニメーション（選択したとき）の角度を制御する関数
void BlockAnimationAngleControl(GameObject* go, int y, int x);

void NewBlockAnimetion(GameObject* go, int y, int x);


//キー入力でアニメーションの情報リセット
void InitializeBlockAnimation(GameObject* go, Key* key, int y, int x);

//ブロックのアニメーション関数
void BlockAnimation(GameObject* go, Key* key);