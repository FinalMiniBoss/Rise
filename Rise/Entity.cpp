#include "Entity.h"

Entity::Entity()

{
	UUID = UUIDCounter++;
	children = {};
	std::cout << "Created Entity " << UUID << std::endl;
}

Entity::~Entity()
{
	while (!children.empty()) {
		Entity* c = children.back();
		children.pop_back();
		delete c;
	}
	std::cout << "Deleted Entity " << UUID << std::endl;
}

void Entity::addChild(Entity* child)
{
	children.push_back(child);
	child->parent = this;
	std::cout << "Added Entity " << child->UUID << " as child of Entity " << UUID << std::endl;
}

bool Entity::removeChild(Entity* child)
{
	bool found = false;
	for (auto& c : children)
	{
		if (c->UUID == child->UUID)
		{
			std::swap(c, children.back());
			found = true;
			break;
		}
	}
	if (found) {
		children.pop_back();
		std::cout << "Removed Entity " << child->UUID << " as a child of Entity " << UUID << std::endl;
	}
	else std::cout << "Entity " << child->UUID << " not a child of Entity " << UUID << std::endl;
	return found;
}

void Entity::update()
{
	key();
	this->onUpdate();
	for (auto& child : children)
	{
		child->update();
	}
}

void Entity::key()
{
	this->onKey({ RenderWindow::Key::Space,RenderWindow::KeyStates[RenderWindow::Key::Space] });
	this->onKey({ RenderWindow::Key::Left,RenderWindow::KeyStates[RenderWindow::Key::Left] });
	this->onKey({ RenderWindow::Key::Right,RenderWindow::KeyStates[RenderWindow::Key::Right] });
	this->onKey({ RenderWindow::Key::Esc,RenderWindow::KeyStates[RenderWindow::Key::Esc] });
}
