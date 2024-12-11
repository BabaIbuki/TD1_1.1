#include <Novice.h>
#include"structer.h"


void LoadAudio(Audio* audio) {

	audio->playHandle[0] = -1;
	audio->playHandle[1] = -1;
	audio->playHandle[2] = -1;
	audio->playHandle[3] = -1;

	//BGM読み込み
	audio->bgm.Title = Novice::LoadAudio("./Audio/BGM/MusMus-BGM-006.mp3");
	audio->bgm.StageSelect = Novice::LoadAudio("./Audio/BGM/MusMus-BGM-080.mp3");
	audio->bgm.Game = Novice::LoadAudio("./Audio/BGM/MusMus-BGM-097.mp3");
	audio->bgm.volume = 0.2f;

	//SE読み込み
	audio->se.select = Novice::LoadAudio("./Audio/SE/select.mp3");
	audio->se.decide = Novice::LoadAudio("./Audio/SE/decide.mp3");
	audio->se.inversion = Novice::LoadAudio("./Audio/SE/inversion.mp3");
	audio->se.death = Novice::LoadAudio("./Audio/SE/death.mp3");
	audio->se.clear = Novice::LoadAudio("./Audio/SE/Phrase03-1.mp3");
	audio->se.getStar = Novice::LoadAudio("./Audio/SE/getStar.mp3");

}

void TitleAudio(Audio* audio, Key* key) {

	//BGM流します
	if (!Novice::IsPlayingAudio(audio->playHandle[0]) || audio->playHandle[0] == -1) {
		audio->playHandle[0] = Novice::PlayAudio(audio->bgm.Title, true, 1.0f);
	}

	if (key->keys[DIK_J] && !key->preKeys[DIK_J]) {
		Novice::PlayAudio(audio->se.decide, false, 1.0f);
	}
}



void StageSelectAudio(Audio* audio, Key* key) {

	//タイトルのBGM消します
	Novice::StopAudio(audio->playHandle[0]);
	//ゲーム中のBGM消します
	Novice::StopAudio(audio->playHandle[2]);

	//ステージセレクトのBGM流します
	if (!Novice::IsPlayingAudio(audio->playHandle[1]) || audio->playHandle[1] == -1) {
		audio->playHandle[1] = Novice::PlayAudio(audio->bgm.StageSelect, true, 1.0f);
	}


	if (key->keys[DIK_A] && !key->preKeys[DIK_A]) {

	}
	else if (key->keys[DIK_D] && !key->preKeys[DIK_D]) {

	}

	if (key->keys[DIK_J] && !key->preKeys[DIK_J]) {

	}
}

void GameAudio(Audio* audio, Key* key) {

	//ステージセレクトのBGM消します
	Novice::StopAudio(audio->playHandle[1]);

	//ゲーム中のBGM流します
	if (!Novice::IsPlayingAudio(audio->playHandle[2]) || audio->playHandle[2] == -1) {
		audio->playHandle[2] = Novice::PlayAudio(audio->bgm.Game, true, 1.0f);
	}

	if (key->keys[DIK_J] && !key->preKeys[DIK_J]) {
		//Novice::PlayAudio(audio->se.inversion, false, 1.0f);
	}

}

