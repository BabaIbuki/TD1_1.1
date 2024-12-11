#pragma once
#include"structer.h"

//汎用性の高い関数の宣言をここで行う

//回転行列の作成関数
Matrix2x2 MakeRotateMatrix(AllBaseInfo* obj);
void DrawFourVertexes(AllBaseInfo* obj);

//ベクトルと行列の積
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix);

//回転座標の作成関数
void MakeRotatePos(AllBaseInfo* obj);

//オブジェクトの四つ角を設定する関数
void SetFourVertexes(AllBaseInfo* obj);

//ギミックのONOFFを調べる関数
int GimmikActive(GameObject* go, int x, int y);