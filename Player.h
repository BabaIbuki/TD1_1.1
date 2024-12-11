#pragma once

//ヘッダーファイルの読み込み
#include"structer.h"

//最初に読み込むプレイヤーの初期化の関数
void PlayerInitialize(GameObject* go);

//ゲームプレイ中の初期化
//void PlayerGameInitialize(GameObject* go);

//プレイヤーの動きの関数
void PlayerMove(GameObject* go,Key* key);

//色を付ける・回収する関数
void ColorSystem(GameObject* go, Key* key, Audio* audio);

//予測8マスを作る
void Predicition8Block(GameObject* go);

//マップチップとの当たり判定
//void PlayerCollisionMapChip(GameObject* go);

//プレイヤーの描画
void PlayerAnimation(GameObject* go);

//プレイヤーの描画
void PlayerDraw(GameObject* go);