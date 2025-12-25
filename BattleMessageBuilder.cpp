#include"EffectResult.h"
#include"BattleMessageBuilder.h"
#include <cstdlib>

std::string BattleMessageBuilder::build(const EffectResult& r)
{
    std::string msg;

    if (r.actionType == ActionType::Spell)
    {
        msg = r.userName + "は " + r.actionName + "を となえた！\n";

        if (r.hpDelta > 0)
            msg += "HPが " + std::to_string(r.hpDelta) + " かいふくした！\n";
    }
    else if (r.actionType == ActionType::Item)
    {
        msg = r.userName + "は " + r.actionName + "を つかった！\n";

        if (r.hpDelta > 0)
            msg += "HPが " + std::to_string(r.hpDelta) + " かいふくした！\n";

        if (r.mpDelta > 0)
            msg += "MPが " + std::to_string(r.mpDelta) + " かいふくした！\n";
    }

    return msg;
}

