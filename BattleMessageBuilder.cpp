#include"EffectResult.h"
#include"BattleMessageBuilder.h"
#include <cstdlib>

    std::string BattleMessageBuilder::build(const EffectResult& result)
    {
        if (!result.success)
        {
            if (result.mpShortage)
            {
                return result.userName + "は MPが たりない！";
            }
            return result.userName + "の こうどうは しっぱいした！";
        }

        std::string message =
            result.userName + "は " + result.actionName + "を つかった！";

        if (result.hpDelta != 0)
        {
            message += " HPが " +
                std::to_string(std::abs(result.hpDelta)) + " かいふくした！";
        }

        if (result.mpDelta != 0)
        {
            message += " MPが " +
                std::to_string(std::abs(result.mpDelta)) + " かいふくした！";
        }

        return message;
    }
