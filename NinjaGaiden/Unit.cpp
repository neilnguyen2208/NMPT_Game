#include"Unit.h"

Unit::Unit(Grid* grid, Entity* entity) 
{
	this->grid = grid;
	this->entity = entity;
	this->p_next = NULL;
	this->p_prev = NULL;
	grid->AddToCell(this);
	x = entity->GetPosition().x;
	y = entity->GetPosition().y;
 }

void Unit::Move(double x, double y, double dt)
{
	grid->Move(this, x, y, dt);
}

BoxCollider Unit::GetCellRect(int i, int j, int cellHeight,int cellWidth)
{
	BoxCollider rect;
	rect.top = (i + 1)*cellHeight - 1;
	rect.bottom = i * cellHeight;
	rect.left = j*cellWidth;
	rect.right = (j + 1)*cellWidth - 1;
	return rect;
}

Entity* Unit::GetEntity()
{
	return this->entity;
}

Unit* Unit::GetNextUnit()
{
	return this->p_next;
}

Unit* Unit::GetPrevUnit()
{
	return this->p_prev;
}

void Unit::Reset()
{
	if(NULL!=entity)
		delete entity;
	entity = NULL;
}
