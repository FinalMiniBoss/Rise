#include "Platform.h"

Platform::Platform()
{
	texture = PlatformTexture;
	size = { 100,10 };
	clip = { 0,0,100,10 };
	anchorPoint = { 0.5,0.f };
	position = { static_cast<float>((rand() % 701) + 50) / 800.f ,-0.1f };
}

Platform::~Platform()
{
}

void Platform::onUpdate(){}