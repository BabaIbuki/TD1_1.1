
//ヘッダーファイルの読み込み
#include"structer.h"

//ここから下に各ギミックの関数を宣言

// 星をゲットする関数
void StarGet(GameObject* go, Audio* audio) {

	// 星が取られていなければ
	if (!go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].star.isGet) {

		// 相棒が星に触れたら星を回収する
		if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 4) {

			// 星の取得数を増やす
			go->buddy.starGetCount++;

			// 星が取られたフラグを立てる
			go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].star.isGet = true;

			// アニメーション用のフレームカウントをリセット
			go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].star.frameCount = 0;

			Novice::PlayAudio(audio->se.getStar, false, 1.0f);

		}

	}

	for (int i = 0; i < VerBlockNum; ++i) {
		for (int j = 0; j < HolBlockNum; ++j) {

			// ブロックが星なら
			if (go->MapChip[i][j].Map == 4) {

				// 取られていなければ
				if (!go->MapChip[i][j].star.isGet) {

					// アニメーションの更新処理
					if (go->MapChip[i][j].star.frameCount < 59) {
						go->MapChip[i][j].star.frameCount++;
					} else {
						go->MapChip[i][j].star.frameCount = 0;
					}

					go->MapChip[i][j].star.animCount = go->MapChip[i][j].star.frameCount / 6;

				} else {

					if (go->MapChip[i][j].star.frameCount < 29) {
						go->MapChip[i][j].star.frameCount++;
					} else {

						// マップ番号を変更
						go->MapChip[i][j].Map = 2;
						go->MapChip[i][j].IsPaint = false;

					}

					go->MapChip[i][j].star.animCount = go->MapChip[i][j].star.frameCount / 5;

				}

			}

		}
	}

}


// ワープするギミックの関数
void WarpBox(GameObject* go) {

	// 相棒がワープブロックに触れていたら
	if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 6) {

		// 7番のワープブロックに乗っていなければ
		if (!go->buddy.onWarpBlock7) {

			// ワープブロックに乗っているフラグを立てる
			go->buddy.onWarpBlock6 = true;

			// クールタイムが0以下で
			if (go->buddy.warpCoolTime <= 0) {

				// ワープ中でなければ
				if (!go->buddy.IsWarp) {

					// ワープ状態にする
					go->buddy.IsWarp = true;

					// クールタイムを設定
					go->buddy.warpCoolTime = 120;

					for (int i = 0; i < VerBlockNum; ++i) {
						for (int j = 0; j < HolBlockNum; ++j) {

							if (go->MapChip[i][j].Map == 6) {

								go->MapChip[i][j].wbg.frameCount = 0;

							}

						}
					}

				}

			}

		}

	}

	// 相棒がワープブロックに触れていたら
	if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 7) {

		// 6番のワープブロックに乗っていなければ
		if (!go->buddy.onWarpBlock6) {

			// ワープブロックに乗っているフラグを立てる
			go->buddy.onWarpBlock7 = true;

			// クールタイムが0以下で
			if (go->buddy.warpCoolTime <= 0) {

				// ワープ中でなければ
				if (!go->buddy.IsWarp) {

					// ワープ状態にする
					go->buddy.IsWarp = true;

					// クールタイムを設定
					go->buddy.warpCoolTime = 120;

					for (int i = 0; i < VerBlockNum; ++i) {
						for (int j = 0; j < HolBlockNum; ++j) {

							if (go->MapChip[i][j].Map == 7) {

								go->MapChip[i][j].wbg.frameCount = 0;

							}

						}
					}

				}

			}

		}

	}

	/*
	// 相棒がワープブロックに触れていたら
	if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 6) {

		// クールタイムが0以下で
		if (go->buddy.warpCoolTime <= 0) {

			// ワープ中でなければ
			if (!go->buddy.IsWarp) {

				// ワープ状態にする
				go->buddy.IsWarp = true;

				// クールタイムを設定
				go->buddy.warpCoolTime = 120;

				// 7番のワープブロックに乗っていなければ
				if (!go->buddy.onWarpBlock7) {

					// ワープブロックに乗っているフラグを立てる
					go->buddy.onWarpBlock6 = true;

				}

			}

		}

	}

	// 相棒がワープブロックに触れていたら
	if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 7) {

		// クールタイムが0以下で
		if (go->buddy.warpCoolTime <= 0) {

			// ワープ中でなければ
			if (!go->buddy.IsWarp) {

				// ワープ状態にする
				go->buddy.IsWarp = true;

				// クールタイムを設定
				go->buddy.warpCoolTime = 120;

				// 6番のワープブロックに乗っていなければ
				if (!go->buddy.onWarpBlock6) {

					// ワープブロックに乗っているフラグを立てる
					go->buddy.onWarpBlock7 = true;

				}

			}

		}

	}
	*/

	if (go->buddy.onWarpBlock6) {

		// 相棒がワープ中で
		if (go->buddy.IsWarp) {

			// クールタイムが60以上なら
			if (go->buddy.warpCoolTime > 60) {

				// 相棒がワープブロックに触れていたら
				if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 6) {

					for (int i = 0; i < VerBlockNum; ++i) {
						for (int j = 0; j < HolBlockNum; ++j) {

							if (go->MapChip[i][j].Map == 6) {

								go->buddy.Pos.y = static_cast<float>(i * BLOCKSIZE + BLOCKSIZE / 2);
								go->buddy.Pos.x = static_cast<float>(j * BLOCKSIZE + BLOCKSIZE / 2);

							}

						}
					}

				}

			}

		} else {

			// 相棒がワープブロックに触れていたら
			if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 6) {

				for (int i = 0; i < VerBlockNum; ++i) {
					for (int j = 0; j < HolBlockNum; ++j) {

						if (go->MapChip[i][j].Map == 7) {

							// 相棒をワープさせる
							go->buddy.Pos.y = static_cast<float>(i * BLOCKSIZE + BLOCKSIZE / 2);
							go->buddy.Pos.x = static_cast<float>(j * BLOCKSIZE + BLOCKSIZE / 2);

						}

					}
				}

			}

		}

	} else if (go->buddy.onWarpBlock7) {

		// 相棒がワープ中で
		if (go->buddy.IsWarp) {

			// クールタイムが60以上なら
			if (go->buddy.warpCoolTime > 60) {

				// 相棒がワープブロックに触れていたら
				if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 7) {

					for (int i = 0; i < VerBlockNum; ++i) {
						for (int j = 0; j < HolBlockNum; ++j) {

							if (go->MapChip[i][j].Map == 7) {

								go->buddy.Pos.y = static_cast<float>(i * BLOCKSIZE + BLOCKSIZE / 2);
								go->buddy.Pos.x = static_cast<float>(j * BLOCKSIZE + BLOCKSIZE / 2);

							}

						}
					}

				}

			}

		} else {

			// 相棒がワープブロックに触れていたら
			if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 7) {

				for (int i = 0; i < VerBlockNum; ++i) {
					for (int j = 0; j < HolBlockNum; ++j) {

						if (go->MapChip[i][j].Map == 6) {

							// 相棒をワープさせる
							go->buddy.Pos.y = static_cast<float>(i * BLOCKSIZE + BLOCKSIZE / 2);
							go->buddy.Pos.x = static_cast<float>(j * BLOCKSIZE + BLOCKSIZE / 2);

						}

					}
				}

			}

		}

	}

	// ワープのクールタイムの計算
	if (go->buddy.warpCoolTime > 0) {
		go->buddy.warpCoolTime--;
		
		// クールタイムが60以下ならワープ後にする
		if (go->buddy.warpCoolTime <= 60) {
			go->buddy.IsWarp = false;
		}

	} else {

		// ワープブロックと重なっていなければ
		if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map != 6
			&& go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map != 7) {

			go->buddy.onWarpBlock6 = false;
			go->buddy.onWarpBlock7 = false;

		}

	}

	for (int i = 0; i < VerBlockNum; ++i) {
		for (int j = 0; j < HolBlockNum; ++j) {

			// ブロックがワープボックスなら
			if (go->MapChip[i][j].Map == 6 || go->MapChip[i][j].Map == 7) {

				if (go->buddy.warpCoolTime <= 0) {

					// アニメーションの更新処理
					if (go->MapChip[i][j].wbg.frameCount < 119) {
						go->MapChip[i][j].wbg.frameCount++;
					} else {
						go->MapChip[i][j].wbg.frameCount = 0;
					}

					go->MapChip[i][j].wbg.animCount = go->MapChip[i][j].wbg.frameCount / 10;

				} else {

					// アニメーションの更新処理
					if (go->MapChip[0][0].wbg.frameCount < 119) {
						go->MapChip[0][0].wbg.frameCount++;
					} else {
						go->MapChip[0][0].wbg.frameCount = 0;
					}

					go->MapChip[i][j].wbg.animCount = go->MapChip[0][0].wbg.frameCount / 20;

				}

			}

		}
	}

	/*
	// 相棒がワープホールに触れていたら
	if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 6) {

		// クールタイムが0以下なら
		if (go->buddy.warpCoolTime <= 0) {

			// ワープ可能状態なら
			if (go->buddy.canWarp) {

				for (int i = 0; i < VerBlockNum; ++i) {
					for (int j = 0; j < HolBlockNum; ++j) {

						if (go->MapChip[i][j].Map == 7) {

							// 相棒をワープさせる
							go->buddy.Pos.y = static_cast<float>(i * BLOCKSIZE + BLOCKSIZE / 2);
							go->buddy.Pos.x = static_cast<float>(j * BLOCKSIZE + BLOCKSIZE / 2);

							go->buddy.warpCoolTime = 60;
							go->MapChip[i][j].wbg.frameCount = 0;

						}

					}
				}

			}

		}

	}

	// 相棒がワープホールに触れていたら
	if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 7) {

		// クールタイムが0以下なら
		if (go->buddy.warpCoolTime <= 0) {

			// ワープ可能状態なら
			if (go->buddy.canWarp) {

				for (int i = 0; i < VerBlockNum; ++i) {
					for (int j = 0; j < HolBlockNum; ++j) {

						if (go->MapChip[i][j].Map == 6) {

							// 相棒をワープさせる
							go->buddy.Pos.y = static_cast<float>(i * BLOCKSIZE + BLOCKSIZE / 2);
							go->buddy.Pos.x = static_cast<float>(j * BLOCKSIZE + BLOCKSIZE / 2);

							go->buddy.warpCoolTime = 60;
							go->MapChip[i][j].wbg.frameCount = 0;

						}

					}
				}

			}

		}
	}

	for (int i = 0; i < VerBlockNum; ++i) {
		for (int j = 0; j < HolBlockNum; ++j) {

			// ブロックがワープボックスなら
			if (go->MapChip[i][j].Map == 6 || go->MapChip[i][j].Map == 7) {

				if (go->buddy.warpCoolTime <= 0) {

					// アニメーションの更新処理
					if (go->MapChip[i][j].wbg.frameCount < 119) {
						go->MapChip[i][j].wbg.frameCount++;
					} else {
						go->MapChip[i][j].wbg.frameCount = 0;
					}

					go->MapChip[i][j].wbg.animCount = go->MapChip[i][j].wbg.frameCount / 10;

				} else {

					// アニメーションの更新処理
					if (go->MapChip[0][0].wbg.frameCount < 119) {
						go->MapChip[0][0].wbg.frameCount++;
					} else {
						go->MapChip[0][0].wbg.frameCount = 0;
					}

					go->MapChip[i][j].wbg.animCount = go->MapChip[0][0].wbg.frameCount / 20;

				}

			}

		}
	}
	*/

}

// ゴールの関数
void GoalMove(GameObject* go) {

	// 相棒が星に触れたら星を回収する
	if (go->MapChip[static_cast<int>(go->buddy.Pos.y) / BLOCKSIZE][static_cast<int>(go->buddy.Pos.x) / BLOCKSIZE].Map == 5) {

		go->buddy.IsClear=true;

	}

	for (int i = 0; i < VerBlockNum; ++i) {
		for (int j = 0; j < HolBlockNum; ++j) {

			// ブロックがゴールなら
			if (go->MapChip[i][j].Map == 5) {

				// アニメーションの更新処理
				if (go->MapChip[i][j].goal.frameCount < 29) {
					go->MapChip[i][j].goal.frameCount++;
				} else {
					go->MapChip[i][j].goal.frameCount = 0;
				}

				go->MapChip[i][j].goal.animCount = go->MapChip[i][j].goal.frameCount / 5;

			}

		}
	}

}

//ギミックをまとめる関数（mainに呼び出すのはこの関数）
void AllGimmick(GameObject* go) {
	
	//呼び出す関数の制御
	for (int y = 0; y < VerBlockNum; y++) {
		for (int x = 0; x < HolBlockNum; x++) {


			go->player.color;
		}
	}
}