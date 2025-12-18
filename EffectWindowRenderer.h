#pragma once

struct EffectResult;
class Display;

class EffectWindowRenderer {
private:
    Display& display;
    const EffectResult* result = nullptr;

    int posX = 40;
    int posY = 420;
    int width = 720;
    int height = 140;
    bool visible = false;
    int showFrame = 0; //•\¦ƒtƒŒ[ƒ€”

public:
    EffectWindowRenderer(Display& d);
    void draw();
    void setResult(const EffectResult* r);
    void setPosition(int x, int y);
    void show();
    void hide();
};

