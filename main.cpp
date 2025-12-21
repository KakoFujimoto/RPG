#include"DxLib.h"
#include"FieldAlly.h"
#include"FieldMenu.h"
#include"Display.h"
#include"FieldItem.h"
#include"GameManager.h"
#include"RandomGenerator.h"
#include"EffectType.h"
#include"EffectResult.h"

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

    Effect healMpEffect{
         EffectType::HealMp,
         8,
         21
    };
    Effect healHpEffect{
         EffectType::HealHp,
         30,
         50
    };
    Item candy("あめ", healMpEffect, 1);
    Item cottonCandy("わたがし", healHpEffect, 1);


    RandomGenerator rng;
    gm.getFieldItemManager().spawn(candy, 800, 600, rng);
    gm.getFieldItemManager().spawn(cottonCandy, 500, 100, rng);


    AllyParameter& allyParameter = gm.getAlly().getParameter();


    // テストコードここから
    allyParameter.consumeMp(5);
    allyParameter.takeDamage(480);

	Display display;
	FieldMenu fieldMenu(&gm, display, allyParameter);

    // フィールドメニューで表示させるため、味方キャラにホイミ等を習得させる(仮の処理)
    Effect hoimiEffect{
         EffectType::HealHp,
         30,
         50
    };
    Effect behoimiEffect{
        EffectType::HealHp,
        80,
        120
    };
    Spell hoimi(rng, "ホイミ", 3, hoimiEffect);
    allyParameter.getSpellManager().learnSpell(hoimi);

    Spell behoimi(rng, "ベホイミ", 6, behoimiEffect);
    allyParameter.getSpellManager().learnSpell(behoimi);
   
    bool prevA = false;
    bool prevS = false;

    EffectResult lastResult;
    // テストコードここまで

    while (ProcessMessage() == 0)
	{
		ClearDrawScreen(); // 画面をクリア

        // テストコードここから
        bool currentA = CheckHitKey(KEY_INPUT_A);
        bool currentS = CheckHitKey(KEY_INPUT_S);

        if (currentA && !prevA)
        {
            // あめを使用
            lastResult = gm.getItemBag().useItem("あめ", gm.getAlly());
            fieldMenu.showEffect(lastResult);
        }
        prevA = currentA;

        if (currentS && !prevS)
        {   
            // ホイミを使用
            lastResult = allyParameter.getSpellManager().castSpell("ホイミ", gm.getAlly());
            fieldMenu.showEffect(lastResult);
        }
        prevS = currentS;

        // テストコードここまで

        int bgColor = GetColor(0, 140, 0);
        DrawBox(0, 0, 800, 600, bgColor, TRUE);

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
