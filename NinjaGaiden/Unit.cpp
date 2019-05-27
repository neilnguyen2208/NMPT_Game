#include"Unit.h"

Unit::Unit(Grid* grid, Entity* entity)
{
	this->entity = entity;
	this->grid = grid;
	p_prev = NULL;
	p_next = NULL;
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