#include"DxLib.h"
#include"FieldAlly.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // ƒEƒBƒ“ƒhƒEƒ‚[ƒh‚Å‹N“®
    ChangeWindowMode(TRUE);
    // ‰æ–ÊƒTƒCƒY‚ðÝ’è
    SetGraphMode(800, 600, 32);

    // DXƒ‰ƒCƒuƒ‰ƒŠ‚Ì‰Šú‰»
    if (DxLib_Init() == -1) {
        return -1;
    }

    // •`‰ææ‚ð— ‰æ–Ê‚É‚·‚é
    SetDrawScreen(DX_SCREEN_BACK);

    FieldAlly* neko = new FieldAlly("‚Ë‚±");
    neko->setPosition(400, 300);


    while (ProcessMessage() == 0) {
        //ClearDrawScreen();‚±‚ê‚¾‚Æ•”wŒi‚É‚È‚é

        int bgColor = GetColor(50, 50, 100); // ”Z‚¢Â‚Á‚Û‚¢”wŒi
        DrawBox(0, 0, 800, 600, bgColor, TRUE);

        neko->move();

        auto [x, y] = neko->getPosition();



        DrawString(x, y, neko->getName().c_str(), GetColor(255, 255, 255));

        ScreenFlip(); // — ‰æ–Ê‚Æ•\‰æ–Ê‚ð“ü‚ê‘Ö‚¦
    }

    DxLib_End();
    return 0;
}