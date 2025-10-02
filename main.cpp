#include "DxLib.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // DXライブラリの初期化
    if (DxLib_Init() == -1) {
        return -1;
    }

    // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    // プレイヤーの座標
    int playerX = 320;
    int playerY = 240;

    while (ProcessMessage() == 0) {
        ClearDrawScreen();

        DrawString(playerX, playerY, "P", GetColor(255, 255, 255));

        ScreenFlip(); // 裏画面と表画面を入れ替え
    }

    DxLib_End();
    return 0;
}