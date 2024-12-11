#pragma once
#include"structer.h"

//初期化関数
void SystemInitialize(System* system);

//リセット関数
//void Restart(GameObject* go, Key* key, System* system);

void RestartDraw(System* system);

//シーン遷移
void SceneChangeInitialize(System* system);

void SceneChangeFunction(System* system);

