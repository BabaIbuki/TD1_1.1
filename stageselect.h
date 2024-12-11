#pragma once

#include"structer.h"

//初期化関数
void StageSelectInitialize(System* system);

//更新処理
void StageselectUpdate(System* system, Key* key, Audio* audio, GameObject* go);

//ステージ画像の動きを管理する関数
void StageImageMovement(System* system);

//ステージ画像の下敷きの動きを管理する関数
void StageImageBackImageMovement(System* system);

//「stage」画像と数字の画像
void StageNumMovement(System* system);

//背景の更新処理
void BackGoundMovement(System* system);

//UIの動きをまとめた関数（StageSelect UI）
void SSUIMovement(System* system);

//描画
void DrawStageSelect(System* system, GameObject* go);
