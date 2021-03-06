#pragma once
#include "Drawable.h"
class Drawable;

class Platform :
    public Drawable
{
public:
    inline static SDL_Texture* PlatformTexture = nullptr;
    inline static SDL_Texture* BigPlatformTexture = nullptr;
    Platform();
    ~Platform();
    virtual void onUpdate();
};

