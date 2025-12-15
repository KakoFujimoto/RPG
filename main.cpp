#include"DxLib.h"
#include"FieldAlly.h"
#include"FieldMenu.h"
#include"Display.h"
#include"FieldItem.h"
#include"GameManager.h"
#include"RandomGenerator.h"
#include"EffectType.h"

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

    GameManager gm;
    //EffectType effectType;
    Item candy("あめ", EffectType::HealMp, 1);
    Item cottonCandy("わたがし", EffectType::HealHp, 1);


    RandomGenerator rng;
    gm.getFieldItemManager().spawn(candy, 800, 600, rng);
    gm.getFieldItemManager().spawn(cottonCandy, 500, 100, rng);


    AllyParameter allyParameter("ねこ", 15, 0, 13, 11, 8, 1, 0);
	Display display;
	FieldMenu fieldMenu(&gm, display, allyParameter);

    // フィールドメニューで表示させるため、味方キャラにホイミを習得させる(仮の処理)
    Spell hoimi(rng, "ホイミ", 3);
    //hoimi.learn();
    allyParameter.getSpellManager().learnSpell(hoimi);
   

    while (ProcessMessage() == 0)
	{
		ClearDrawScreen(); // 画面をクリア

        int bgColor = GetColor(0, 140, 0);
        DrawBox(0, 0, 800, 600, bgColor, TRUE);

        //if (!subdMenu.isOpen()) 
        fieldMenu.update();
        
        if (!fieldMenu.getIsOpen()) {
            gm.getAlly().move();
        }

        DrawString(gm.getAlly().getX(), gm.getAlly().getY(), gm.getAlly().getName().c_str(), GetColor(255, 255, 255));
        fieldMenu.draw(display);

        gm.getFieldItemManager().draw();

        gm.updateItemBag();

        ScreenFlip(); // 裏画面と表画面を入れ替え
    }

    DxLib_End();
    return 0;
}
