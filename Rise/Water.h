#pragma once
#include "Drawable.h"
class Drawable;

class Water :
    public Drawable
{
public:
    int t = 0;
    int phase = 0;
    inline static SDL_Texture* WaterTexture = nullptr;
    Water();
    Water(float, int);
    ~Water();
    virtual void onUpdate();
};

