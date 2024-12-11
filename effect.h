#pragma once
#include"structer.h"

//初期化関数
void Effectinitialize(AllEffect* ae);

//色を変えた時のエフェクト====================================================

//エフェクト生成関数
void CCEffectGenerate(AllEffect* ae,GameObject* go,int y,int x);

//エフェクトの動きを管理する関数
void CCEffectMovement(AllEffect* ae);

//上二つの関数をまとめる関数
void CCEffect(AllEffect* ae, GameObject* go);

//描画関数
void DrawCCEffect(AllEffect* ae);

//エフェクトのデバッグ表示
void EffectDebugPrintf(AllEffect* ae);


//死んだ処理
void DeathEffectInitialze(AllEffect* ae);

void DeathEffect(AllEffect* ae, GameObject* go);

void DeathEffectDraw(AllEffect* ae);

//============================================================================

