#include"DxLib.h"
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

    //FieldAlly* neko = new FieldAlly("ねこ");
    FieldAlly ally("ねこ");
    ally.setPosition(400, 300);



    while (ProcessMessage() == 0) {
        //ClearDrawScreen();

        int bgColor = GetColor(50, 50, 100); // 濃い青っぽい背景
        DrawBox(0, 0, 800, 600, bgColor, TRUE);

        ally.move();


        auto [x, y] = ally.getPosition();


        DrawString(x, y, ally.getName().c_str(), GetColor(255, 255, 255));


        ScreenFlip(); // 裏画面と表画面を入れ替え
    }

    DxLib_End();
    return 0;
}