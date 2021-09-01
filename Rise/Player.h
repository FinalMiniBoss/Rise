#pragma once
#include "Drawable.h"

class Drawable;
class Player :
    public Drawable
{
public:
    enum class State
    {
        Grounded,
        Flying,
        Dead
    };
    float xVel = 0.f;
    float yVel = 0.f;
    float accel = 0.00015f;
    float fuel = 100.f;
    float fuelRate = 1.f;

    Player();

    void onKey(RenderWindow::Key);
    void onUpdate();
};

