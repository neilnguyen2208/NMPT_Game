#pragma once
#include "Entity.h"
#include <vector>
class ObjectGroup {
public:
	ObjectGroup();
	~ObjectGroup();
	void AddObject(Entity *e);
	//Lay nhung object dang o trong camera
	void GetActiveObject(std::vector<Entity*> &entities);
	//Update nhung object o trong camera
	virtual void Update(double dt) = 0;
	//Render
	virtual void Render() = 0;
protected:
	std::vector<Entity*> entities;
};