#pragma once
#include <vector>
#include <iostream>

#include "RenderWindow.h"

class Entity {
public:
	std::vector<Entity*> children;
	uint32_t UUID;
	Entity* parent;

	Entity();
	~Entity();

	void addChild(Entity* child);
	bool removeChild(Entity* child);

	void update();
	virtual void onUpdate() {}

	void key();
	virtual void onKey(std::pair<RenderWindow::Key, RenderWindow::KeyState> key) {}
private:
	inline static uint32_t UUIDCounter = 0;
};
