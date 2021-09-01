#include "Water.h"

Water::Water() {
	texture = WaterTexture;
	size = { 100,200 };
	clip = { 0,0,100,200 };
}

Water::Water(float t, int phase):phase(phase)
{
	texture = WaterTexture;
	size = { 100,200 };
	clip = { 0,0,100,200 };
	position = { t / 8.f, 1 };
	anchorPoint = { 1.f,0.5 };
}

void Water::onUpdate() {
	t++;
	position.x += sinf(((float)t +(float)(99*phase))/ 60.f)/(4000.f*std::sqrtf((float)phase));
	position.y -= cosf(((float)t+(float)(120*phase)) / 60.f)/(6400.f * std::sqrtf((float)phase));
	position.x += (float)((0.003225/3)+phase/100);
}