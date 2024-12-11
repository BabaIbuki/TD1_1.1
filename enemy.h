#include"structer.h"

//最初に読み込む敵の初期化の関数
void EnemyInitialize(GameObject* go);

//ゲームプレイ中の初期化
//void PlayerGameInitialize(GameObject* go);

//敵の動きの関数
void EnemyMove(GameObject* go, Audio* audio);

//リトライ時のちょっとした初期化関数
void EnemyMoveGameInitialize(GameObject* go);

//色を付ける・回収する関数
//void ColorSystem(GameObject* go, Key* key);

//予測8マスを作る
//void Predicition8Block(GameObject* go);

//マップチップとの当たり判定
//void PlayerCollisionMapChip(GameObject* go);

//敵の描画
void EnemyDraw(GameObject* go);

