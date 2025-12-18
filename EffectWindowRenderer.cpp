#include"EffectWindowRenderer.h"
#include"EffectResult.h"
#include <string>
#include<DxLib.h>


void EffectWindowRenderer::draw(const EffectResult& result)
{
    if (!result.success) return;

    int y = 100;

    if (result.hpDelta != 0)
    {
        std::string text =
            (result.hpDelta > 0 ? "HP +" : "HP ")
            + std::to_string(result.hpDelta);

        DrawString(50, y, text.c_str(), GetColor(255, 255, 255));
        y += 20;
    }

    if (result.mpDelta != 0)
    {
        std::string text =
            (result.mpDelta > 0 ? "MP +" : "MP ")
            + std::to_string(result.mpDelta);

        DrawString(50, y, text.c_str(), GetColor(255, 255, 255));
    }
}