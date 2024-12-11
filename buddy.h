#include"structer.h"

//最初に読み込む相棒の初期化の関数
void BuddyInitialize(GameObject* go);

//ゲームプレイ中の初期化
//void PlayerGameInitialize(GameObject* go);

//相棒の動きの関数
void BuddyMove(GameObject* go, System* system);
void BuddyAnimation(GameObject* go);

//リトライ時のちょっとした初期化関数
void BuddyGameInitialize(GameObject* go);

//色を付ける・回収する関数
//void ColorSystem(GameObject* go, Key* key);

//予測8マスを作る
//void Predicition8Block(GameObject* go);

//マップチップとの当たり判定
//void PlayerCollisionMapChip(GameObject* go);

//相棒の描画
void BuddyDraw(GameObject* go);
