#pragma once
#include "Drawable.h"
class FuelGuage :
    public Drawable
{
public:
    Drawable* Fuel = nullptr;
    Drawable* BackGuage = nullptr;

    FuelGuage();
    ~FuelGuage();

    void onUpdate();
};

