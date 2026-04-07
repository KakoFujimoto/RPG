#pragma once

class GameManager;

class IGameState
{
public:
    virtual ~IGameState() = default;
    virtual void update(GameManager& gm) = 0;
    virtual void draw(GameManager& gm) = 0;
};