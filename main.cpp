#include"DxLib.h"
#include"Neko.h"
#include"FieldAlly.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // ウィンドウモードで起動
    ChangeWindowMode(TRUE);
    // 画面サイズを設定
    SetGraphMode(800, 600, 32);

    // DXライブラリの初期化
    if (DxLib_Init() == -1) {
        return -1;
    }

    // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    Neko neko;
    FieldAlly fieldAlly(&neko);
    fieldAlly.setPosition(400, 300);


    while (ProcessMessage() == 0) {
        //ClearDrawScreen();これだと黒背景になる

        int bgColor = GetColor(50, 50, 100); // 濃い青っぽい背景
        DrawBox(0, 0, 800, 600, bgColor, TRUE);

        fieldAlly.move();

        auto [x, y] = fieldAlly.getPosition();



        DrawString(x, y, "猫", GetColor(255, 255, 255));

        ScreenFlip(); // 裏画面と表画面を入れ替え
    }

    DxLib_End();
    return 0;
}