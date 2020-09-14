#include "DxLib.h"

#define GAME_WIDTH 960 //画面横の大きさ
#define GAME_HEIGHT 640 //画面縦の大きさ
#define GAME_COLOR 32 //画面のカラービット

#define GAME_WINDOW_BAR 0 //タイトルバーはデフォルト
#define GAME_WINDOW_NAME "DxLib_Movie" 


int handle = -1; //動画のハンドル

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE); //log.txtを出力しない
	ChangeWindowMode(TRUE); //ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR); //指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR); //タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME)); //ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE); //非アクティブでも実行する

	if (DxLib_Init() == -1) { return -1; } //DxLibの初期化処理

	

	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; } //メッセージ処理の結果がエラー表示の時、強制終了
		if (ClearDrawScreen() != 0) { break; } //画面を消去できなかった時、強制終了

		if (GetMovieStateToGraph(handle) == 0)
		{
			SeekMovieToGraph(handle, 0); //再生バーを最初からにする
			PlayMovieToGraph(handle); //動画を再生状態にする

			ChangeMovieVolumeToGraph(127, handle);//動画の音を調整する
		}
	

		DrawString(0, 0, "動画を再生しています…", GetColor(255, 255, 255));

		ScreenFlip(); //モニタのリフレッシュレートのはやさで裏画面を再描画
	}

	DxLib_End();

	

	return 0;
}
