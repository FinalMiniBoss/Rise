#pragma once
#include "Drawable.h"
#include <cstdlib>

class Drawable;
class Player :
    public Drawable
{
public:
    enum class State
    {
        Grounded,
        Flying,
        Falling,
        Dead
    } state = State::Grounded; 

    Drawable* Thrust = nullptr;

    float xVel = 0.f;
    float yVel = 0.f;
    float accel = 0.00015f;
    float maxFuel = 100.f;
    float fuel = 100.f;
    float fuelRate = 1.f;
    float refuelRate = 0.5f;

    Player();

    void onUpdate();
};

