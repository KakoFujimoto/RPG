#include"DxLib.h"
#include"FieldAlly.h"
#include"FieldMenu.h"
#include"Display.h"
#include"FieldItem.h"
#include"GameManager.h"
#include"RandomGenerator.h"
#include"EffectType.h"
#include"EffectResult.h"
#include"FieldEnemy.h"
#include"EnemyParameter.h"

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


    ////////// テストコードここから //////////
    // == あめとわたがしの効果を設定 ==
    // あめ(MP回復)
    Effect healMpEffect{
         EffectType::HealMp,
         8,
         21
    };
    // わたがし(HP回復)
    Effect healHpEffect{
         EffectType::HealHp,
         30,
         50
    };
    Item candy("あめ", healMpEffect, 1);
    Item cottonCandy("わたがし", healHpEffect, 1);

    // == あめとわたがしをフィールド上に湧かせる ==
    RandomGenerator rng;
    gm.getFieldItemManager().spawn(candy, 800, 600, rng);
    gm.getFieldItemManager().spawn(cottonCandy, 500, 100, rng);


    // == 回復効果の確認用に手動で味方キャラのパラメータを下げる ==
    AllyParameter& allyParameter = gm.getAlly().getParameter();
    allyParameter.consumeMp(5);
    allyParameter.takeDamage(480);

	Display display;
	FieldMenu fieldMenu(&gm, display, allyParameter);

    // == 手動で味方キャラにホイミとベホイミを習得させる ==
    // == ホイミとベホイミの効果を設定 ==
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
    // == ホイミとベホイミをインスタンス化/味方キャラに習得させる ==
    Spell hoimi(rng, "ホイミ", 3, hoimiEffect);
    allyParameter.getSpellManager().learnSpell(hoimi);

    Spell behoimi(rng, "ベホイミ", 6, behoimiEffect);
    allyParameter.getSpellManager().learnSpell(behoimi);
   
    // == 敵のインスタンス化 ==
    FieldEnemy slime(
        Position{ 400, 300 },
        EnemyParameter("スライム", 10, 0, 13, 11, 8, 1, 0)
    );

    FieldEnemy druky(
        Position{ 200, 200 },
        EnemyParameter("ドラキー", 14, 10, 13, 11, 8, 1, 0)
    );
    // == 敵をフィールド上に湧かせる ==
    gm.getFieldEnemyManager().spawn(slime, 200, 200, rng);
    gm.getFieldEnemyManager().spawn(druky, 100, 300, rng);

    ////////// テストコードここまで //////////

    while (ProcessMessage() == 0)
	{
		ClearDrawScreen(); // 画面をクリア

        int bgColor = GetColor(0, 140, 0);
        DrawBox(0, 0, 800, 600, bgColor, TRUE);

        gm.update();
        fieldMenu.update();
        
        if (!fieldMenu.getIsOpen()) {
            gm.getAlly().move();
        }

        // == 仮の処理(味方キャラの文字列描画) ==
        DrawString(gm.getAlly().getX(), gm.getAlly().getY(), gm.getAlly().getName().c_str(), GetColor(255, 255, 255));
        // == 仮の処理ここまで ==

        fieldMenu.draw(display);
        gm.updateItemBag();

        ////////// テストコードここから //////////
        // == 敵の描画 ==
        if (!gm.isBattle())
        {
            gm.getFieldEnemyManager().draw();
            gm.getFieldItemManager().draw();
        }
        ////////// テストコードここまで //////////

        gm.checkEncount();

        ScreenFlip(); // 裏画面と表画面を入れ替え
    }

    DxLib_End();
    return 0;
}
