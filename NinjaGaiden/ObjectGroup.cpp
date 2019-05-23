#include "ObjectGroup.h"
#include "Camera.h"

ObjectGroup::ObjectGroup() {
	
}

ObjectGroup::~ObjectGroup() {
}

void ObjectGroup::AddObject(Entity * e) {
	//for (size_t i = 0; i < entities.size(); i++)
	//	if (e == entities[i])
	//		return;
	entities.push_back(e);
}

void ObjectGroup::GetActiveObject(std::vector<Entity*> &entities) {
	for (auto child : this->entities) {
		if (child->IsActive())
			entities.push_back(child);
	}
}
