#include"DxLib.h"
#include"FieldAlly.h"
#include"FieldMenu.h"
#include"Display.h"
#include"FieldItem.h"

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

    FieldAlly ally("ねこ", 400, 300);

    Item candy("あめ", 1);
    FieldItem fieldItem;
    fieldItem.spawn(candy, 800, 600);


	FieldMenu fieldMenu;
	Display display;

    while (ProcessMessage() == 0)
	{
		ClearDrawScreen(); // 画面をクリア

        int bgColor = GetColor(50, 50, 100); // 濃い青っぽい背景
        DrawBox(0, 0, 800, 600, bgColor, TRUE);

        //if (!subdMenu.isOpen()) 
        fieldMenu.update();
        
        if (!fieldMenu.getIsOpen()) {
            ally.move();
        }

        DrawString(ally.getX(), ally.getY(), ally.getName().c_str(), GetColor(255, 255, 255));
        fieldMenu.draw(display);

        fieldItem.draw();

        ScreenFlip(); // 裏画面と表画面を入れ替え
    }

    DxLib_End();
    return 0;
}