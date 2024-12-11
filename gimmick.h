#pragma once

//ヘッダーファイルの読み込み
#include"structer.h"

/*============================================================
             ここから下に各ギミックの関数を宣言
 ============================================================ */

// 星の関数
void StarGet(GameObject* go, Audio* audio);

 // ワープするギミックの関数
void WarpBox(GameObject* go);

// ゴールの関数
void GoalMove(GameObject* go);

 // ファイアバーのギミックの関数

 // 相棒の進行方向を反転させるギミックの関数



//時間経過で色が抜けるギミックの関数
//void TimelimitBlock(GameObject* go);