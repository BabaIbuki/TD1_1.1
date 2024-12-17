#pragma once
//ヘッダーファイルの読み込み
#include<Novice.h>
#include"define.h"
#include"enum.h"

/*============================================
				基本クラス
============================================*/

struct Vector2 {
	float x;
	float y;
};

struct IntVector2 {
	int x;
	int y;
};

struct Matrix2x2 {
	float m[2][2];
};

//オブジェクトが持つ基本的な情報をまとめた構造体
struct ObjectBaseInfo {
	/*  座標・移動　に関する変数  */
	Vector2 Pos;
	Vector2 PrePos;
	Vector2 Vector;
	Vector2 Velocity;
	Vector2 Acceleration;
	float speed;
	float width;
	float height;
	int MoveFlag;
	int MoveCoolTime;
	int respawnTimer;

	/*  描画　に関する変数  */
	int IsAir;
	float UpperHalfAlteration;
	float BesideAlteration;
	int AnimationTimer;
	float DrawWidth;
	float DrawHeight;
	int color;
	int image;
	float theta;
	float degree;
};

//オブジェクトの四つ角の情報を持った構造体
struct FourVertexs {

	/*  マップチップとの当たり判定  */
	IntVector2 RightTop;
	IntVector2 RightBottom;
	IntVector2 LeftTop;
	IntVector2 LeftBottom;

	/*  描画用  */
	Vector2 DrawRightTop;
	Vector2 DrawRightBottom;
	Vector2 DrawLeftTop;
	Vector2 DrawLeftBottom;

	/*　回転用　*/
	Vector2 RotateRightTop;
	Vector2 RotateRightBottom;
	Vector2 RotateLeftTop;
	Vector2 RotateLeftBottom;

	/*  バッファ回転用  */
	Vector2 BufRotateRightTop;
	Vector2 BufRotateRightBottom;
	Vector2 BufRotateLeftTop;
	Vector2 BufRotateLeftBottom;
};

/*============================================
		　基本クラスをまとめる構造体
============================================*/
struct AllBaseInfo : ObjectBaseInfo, FourVertexs {
};


/*============================================
		　ギミックの構造体
============================================*/

// 星の構造体
struct StarBlock {
	int frameCount;
	int animCount;
	int isGet;
	int gotEffectImage;
};

// ワープボックスの構造体
struct WarpBoxGimmick {
	int frameCount;
	int animCount;
};

// ゴールの構造体
struct GoalPortal {
	int frameCount;
	int animCount;
};


/*============================================
		　エフェクトの構造体
============================================*/

//色を変えた時のエフェクト
struct ChangeColor : AllBaseInfo{

	//エフェクトの寿命
	int ActiveTimer;

	//そのエフェクトが生きているか
	int IsActive;
	
	//乱数でのベクトルの取得のための変数（ＲはRandom　の頭文字）
	float Rdegree;
	float Rtheta;
};

struct BuddyDeath : AllBaseInfo {

	//エフェクトの寿命
	int ActiveTimer;

	//そのエフェクトが生きているか
	int IsActive;

	//乱数でのベクトルの取得のための変数（ＲはRandom　の頭文字）
	float Rdegree;
	float Rtheta;

	//方向
	float speed;
	Vector2 vector;
	Vector2 velocity;

	//座標
	Vector2 Pos;



};

/*============================================
				派生クラス
============================================*/


struct Player : AllBaseInfo {
	//地面に接しているか
	int IsGround;
	int IsAlive;
	int predicitionBlockgraphHandle;
	int frameCount;
	int animCount;
	int clearedImage;
	int predicitionBlockFrameCount;
	int predicitionBlockAnimCount;
	int select[VerBlockNum][HolBlockNum];
	Direction direction;
};

struct Buddy : AllBaseInfo {
	//地面に接しているか
	int IsGround;
	int IsAlive;
	int gravity;
	int IsClear;
	int starGetCount;
	int MaxStarCount[15];
	int warpCoolTime;
	int onWarpBlock6;
	int onWarpBlock7;
	int IsWarp;
	int frameCount;
	int animCount;
	int graphHandleFalling;
	int graphHandleNum;
	int select[VerBlockNum][HolBlockNum];
};

struct Star : AllBaseInfo {
	int IsAlive;
	int frameCount;
	int animCount;
	int select[VerBlockNum][HolBlockNum];
};


struct Enemy : AllBaseInfo {
	//地面に接しているか
	int IsGround;
	int IsAlive;
	int gravity;
	int frameCount;
	int animCount;
	int select[VerBlockNum][HolBlockNum];
};


struct Block : AllBaseInfo {
	//マップ番号
	int  Map;

	//塗られているかのフラグ変数
	int CanPaint;
	int IsPaint;

	//ブロックのアニメーションのための変数達
	int IncreaseFlag;
	int DecreaseFlag;
	int ShakeNum;
	float ShakeWidth;

	//エフェクトの生成のためのフラグ
	int IsEffectGenarated;

	//エフェクトを生成した数を記録する変数
	int GenarateEffectNum;

	//以下ギミックの宣言と変数追加
	StarBlock star;
	WarpBoxGimmick wbg;
	GoalPortal goal;
	float SizeBuffer;

};

//シェイク用構造体
struct SHAKE {
	Vector2 Pos;
	int flag;
	int time;

};

/*============================================
		　派生クラスをまとめる構造体
============================================*/

//オブジェクトをまとめた構造体
struct GameObject {
	Player player;
	Buddy buddy;
	Star star[3];
	Enemy enemy[10];
	Block MapChip[VerBlockNum][HolBlockNum];
	SHAKE shake;
};

//すべてのエフェクトをまとめた構造体
struct AllEffect {
	ChangeColor cc[CCEffectNum];
	BuddyDeath bd[BDEffectNum];
};

/*============================================
			　 その他の構造体
============================================*/
struct Key {
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
};

struct BGM {
	int Title;
	int StageSelect;
	int Game;
	int Clear;
	float volume;
};

struct SE {
	int select;
	int decide;
	int inversion;
	int death;
	int clear;
	int getStar;
};

struct Audio {
	BGM bgm;
	SE se;
	int playHandle[4];
};


struct UI {
	Vector2 PlayUI_Pos;
	int PlayUI_image;
	int NotMovingTimer;
	float DrawHight;
	float DrawWidth;
};


//ステージセレクトのステージ画像が持つ情報(StageSelectObject の略)
struct SSObj : AllBaseInfo {
	float FrontPoint;
	float BackPoint;

};

struct SceneChange {
	int changeFlag;
	Vector2 Pos[4];
	int image;
	int Restart;
	int RestartImage;
	int backColor;
};

//ステージセレクトのステージ画像が持つ情報(StageImageObject の略)
struct SIObj : AllBaseInfo {
	float FrontPoint;
	float BackPoint;
};

//ステージ画像の下敷きの画像が持つ情報
struct SIBObj : AllBaseInfo {
};

//背景が持つ情報
struct BG : AllBaseInfo {
	float Scroll;
};

//PUSH J　のUI
struct PSJ : AllBaseInfo {
};

//画面上部の黒画像（Black Back Ground）
struct BBG : AllBaseInfo {
};

//「stage」の画像(Stage Image)
struct SI : AllBaseInfo {
};

//ステージ番号の表示（Stage Num）
struct SN : AllBaseInfo {

};

//星の画像
struct StarImage :AllBaseInfo {

};

//「clear!」画像
struct ClearImage :AllBaseInfo {

};

struct STAGESELECT {
	//選択している番号
	int select;

	//線形補完で動かす点t(この点は出ねえよぉおお！！！？！？！？)
	float t;

	//線形補完で動かす時間
	float time;

	int IncreaseFlag;
	int DecreaseFlag;

	//画像が持つ情報
	SSObj ssobj[StageNum];
	SIObj siobj[StageNum];
	SIBObj sibobj[StageNum];
	SI si[StageNum];
	SN sn[StageNum];
	BG bg;
	PSJ psj;
	BBG bbg[2];
	StarImage starimage[StageNum];
	ClearImage ci;


};


struct System {
	//ステージがクリアされているかどうか
	int IsClear[StageNum + 1];

	//シーン管理用の変数
	int scene;
	int NextScene;

	// タイトルの変数
	int titleImage;
	int titleUIImage;

	//クリア後の処理に使う変数たち
	int clearscene;
	int selectMenu;
	int clearframe;
	Vector2 ClearUI_Pos[6];
	int ClearUI_image[6];
	int selectFrame[3];
	int ClearUIColor;
	int ClearSceneSelectCoolTime;
	int ClearSceneSelect;

	UI ui;

	//ステージセレクト画面で使用する変数

	STAGESELECT stageselect;

	SceneChange sc;
};

//イージングクラス
class EASE {
public:
	static double InOutQuad(double change, double base, double duration, double time) {
		time /= duration / 2;
		if (time < 1) return change / 2 * time * time + base;
		return -change / 2 * ((--time) * (time - 2) - 1) + base;
	};
};
