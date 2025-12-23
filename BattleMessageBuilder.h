#pragma once
#include<string>

class EffectResult;
class BattleMessageBuilder {
private:

public:
    static std::string build(const EffectResult& result);

};
