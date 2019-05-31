#include "ObjectGroup.h"
#include "Camera.h"

ObjectGroup::ObjectGroup() {
	
}

ObjectGroup::~ObjectGroup() {
}

void ObjectGroup::AddObject(Entity * e) {
	entities.push_back(e);
}

void ObjectGroup::GetActiveObject(std::vector<Entity*> &entities) {
	for (auto child : this->entities) {
		if (child->IsActive())
			entities.push_back(child);
	}
}
