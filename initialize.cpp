//ソースファイルの読み込み
#include <Novice.h>

//ヘッダーファイルの読み込み（アルファベット順）
#include"buddy.h"
#include"enemy.h"
#include"enum.h"
#include"define.h"
#include"structer.h"
#include"gimmick.h"
#include"Player.h"
#include"stage.h"
#include"common.h"
#include"system.h"


void Initialize(GameObject*go,System* system,Key* key) {

	// Rキーが押されたら
	if (key->keys[DIK_R] && !key->preKeys[DIK_R]) {

		if (!go->buddy.IsClear) {

			// ステージの状態をリセット

			// ステージ
			StageInitialize(go);

			// プレイヤー
			PlayerInitialize(go);

			// 相棒
			BuddyInitialize(go);

			// 敵
			EnemyInitialize(go);

			StageGenerate(go, system);

		}

	}

}