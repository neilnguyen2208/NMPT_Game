#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "Entity.h"
#include "GameConfig.h"
#include "MyHelper.h"
#include "Enemy.h"
#include "Grid.h"


class Grid;

class Unit {

	//use topleft coordinates

	Entity* entity;
	Unit* p_next;
	Unit* p_prev;
	Grid* grid;
	float x, y;
	
	friend class Grid;
	//
public: BoxCollider GetCellRect(int i, int j, int cellHeight,int cellWidth);

	//
public:
	
	Unit(Grid* grid, Entity* entity);
	void Move(double x, double y, double dt);
	Entity* GetEntity();
	Unit*GetNextUnit();
	Unit*GetPrevUnit();
	void Reset();
};