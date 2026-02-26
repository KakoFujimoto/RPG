#pragma once
#include<string>

struct EffectResult;
class BattleMessageBuilder {
private:

public:
    static std::string build(const EffectResult& result);

};
