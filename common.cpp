#include<Novice.h>
#include"structer.h"
#include<math.h>
#include <time.h>

//オブジェクトの四つ角を設定する関数
void SetFourVertexes(AllBaseInfo* obj) {

	//当たり判定用
	obj->LeftTop.x = int(obj->Pos.x - obj->width / 2.0f) / BLOCKSIZE;
	obj->LeftTop.y = int(obj->Pos.y - obj->height / 2.0f) / BLOCKSIZE;

	obj->LeftBottom.x = int(obj->Pos.x - obj->width / 2.0f) / BLOCKSIZE;
	obj->LeftBottom.y = int(obj->Pos.y + obj->height / 2.0f - 1) / BLOCKSIZE;

	obj->RightTop.x = int(obj->Pos.x + obj->width / 2.0f - 1) / BLOCKSIZE;
	obj->RightTop.y = int(obj->Pos.y - obj->height / 2.0f) / BLOCKSIZE;

	obj->RightBottom.x = int(obj->Pos.x + obj->width / 2.0f - 1) / BLOCKSIZE;
	obj->RightBottom.y = int(obj->Pos.y + obj->height / 2.0f - 1) / BLOCKSIZE;


	//描画用
	obj->DrawLeftTop.x = obj->Pos.x - obj->width / 2.0f;
	obj->DrawLeftTop.y = obj->Pos.y - obj->height / 2.0f;

	obj->DrawLeftBottom.x = obj->Pos.x - obj->width / 2.0f;
	obj->DrawLeftBottom.y = obj->Pos.y + obj->height / 2.0f;

	obj->DrawRightTop.x = obj->Pos.x + obj->width / 2.0f;
	obj->DrawRightTop.y = obj->Pos.y - obj->height / 2.0f;

	obj->DrawRightBottom.x = obj->Pos.x + obj->width / 2.0f;
	obj->DrawRightBottom.y = obj->Pos.y + obj->height / 2.0f;


	//回転用
	obj->RotateLeftTop.x =  - obj->width / 2.0f;
	obj->RotateLeftTop.y = - obj->height / 2.0f;

	obj->RotateLeftBottom.x =  - obj->width / 2.0f;
	obj->RotateLeftBottom.y =  + obj->height / 2.0f;

	obj->RotateRightTop.x =  + obj->width / 2.0f;
	obj->RotateRightTop.y =  - obj->height / 2.0f;

	obj->RotateRightBottom.x =  + obj->width / 2.0f;
	obj->RotateRightBottom.y =  + obj->height / 2.0f;

}

void DrawFourVertexes(AllBaseInfo* obj) {

	//描画用
	obj->DrawLeftTop.x = obj->Pos.x - obj->DrawWidth / 2.0f;
	obj->DrawLeftTop.y = obj->Pos.y - obj->DrawHeight / 2.0f;

	obj->DrawLeftBottom.x = obj->Pos.x - obj->DrawWidth / 2.0f;
	obj->DrawLeftBottom.y = obj->Pos.y + obj->height / 2.0f;

	obj->DrawRightTop.x = obj->Pos.x + obj->DrawWidth / 2.0f;
	obj->DrawRightTop.y = obj->Pos.y - obj->DrawHeight / 2.0f;

	obj->DrawRightBottom.x = obj->Pos.x + obj->DrawWidth / 2.0f;
	obj->DrawRightBottom.y = obj->Pos.y + obj->height / 2.0f;


	//回転用
	obj->RotateLeftTop.x = -obj->DrawWidth / 2.0f;
	obj->RotateLeftTop.y = -obj->DrawHeight / 2.0f;

	obj->RotateLeftBottom.x = -obj->DrawWidth / 2.0f;
	obj->RotateLeftBottom.y = +obj->height / 2.0f;

	obj->RotateRightTop.x = +obj->DrawWidth / 2.0f;
	obj->RotateRightTop.y = -obj->DrawHeight / 2.0f;

	obj->RotateRightBottom.x = +obj->DrawWidth / 2.0f;
	obj->RotateRightBottom.y = +obj->height / 2.0f;

}

//回転行列の作成関数
Matrix2x2 MakeRotateMatrix(AllBaseInfo* obj) {
	return{
		cosf(obj->theta),
		sinf(obj->theta),
		-sinf(obj->theta),
		cosf(obj->theta)
	};
}

//ベクトルと行列の積
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {
	return{
		vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0],
		vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1],
	};
}

//回転座標の作成関数
void MakeRotatePos(AllBaseInfo* obj) {
	obj->BufRotateLeftTop = Multiply(obj->RotateLeftTop, MakeRotateMatrix(obj));
	obj->BufRotateLeftBottom = Multiply(obj->RotateLeftBottom, MakeRotateMatrix(obj));
	obj->BufRotateRightTop = Multiply(obj->RotateRightTop, MakeRotateMatrix(obj));
	obj->BufRotateRightBottom = Multiply(obj->RotateRightBottom, MakeRotateMatrix(obj));
}

//ギミックのONOFFを管理する関数
int GimmikActive(GameObject* go,int x,int y) {

	int flag;

	if (go->MapChip[x][y].IsPaint) {
		flag = true;
	}
	else {
		flag = false;
	}

	return flag;
}

//シェイクを作る関数
void MakeShake(GameObject* go) {

	//乱数値の取得
	srand((unsigned)time(NULL));

	//相棒が死んだら
	if (!go->buddy.IsAlive) {
		go->shake.flag = true;
	}

	if (go->shake.flag) {

		//4フレに一回シェイクの値を更新
		if (go->shake.time % 4 == 0) {
			//シェイクの時間を減らす
			go->shake.time--;

			//シェイクする分の値を取得（徐々に振れ幅を小さく）
			go->shake.Pos.x = float(rand() % 5 + (go->shake.time / 2));
			go->shake.Pos.y = float(rand() % 5 + (go->shake.time / 2));
		}
	}

	//フラグを折る
	if (go->shake.time <= 0) {
		go->shake.flag = false;
	}

	//相方が生き返ったらタイマー初期化・一応フラグも折っておく
	if (!go->buddy.IsAlive) {
		go->shake.time = 15;
		go->shake.flag = false;

	}
}