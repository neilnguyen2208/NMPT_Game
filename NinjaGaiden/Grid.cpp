#include "Grid.h"
#include"Unit.h"
#include"Debug.h"
Grid::Grid()
{
	//
	// Clear the grid.
	for (int x = 0; x < GRID_COLUMNS; x++)
	{
		for (int y = 0; y < GRID_ROWS; y++)
		{
			gridcells[x][y] = NULL;
		}
	}

	isActiveCells = new bool*[rows];
	for (int i = 0; i < rows; i++)
	{
		isActiveCells[i] = new bool[columns];
		for (int j = 0; j < columns; j++)
		{
			isActiveCells[i][j] = false;
		}
	}

	//intit several things
//	player->SetMoveDirection(Entity::LeftToRight);
}

Grid::Grid(BoxCollider r, int rows, int columns) {
	//--Debug
	this->rows = 4;
	this->columns = 32;
	rows = this->rows;
	columns = this->columns;
	//
	mapWidth = r.GetWidth();
	mapHeight = r.GetHeight();
	cellWidth = mapWidth / this->columns;
	cellHeight = mapHeight / this->rows;
	gridcells = new Unit**[this->rows];
	for (int i = 0; i < this->rows; i++)
	{
		gridcells[i] = new Unit*[this->columns];
		for (int j = 0; j < this->columns; j++)
		{
			gridcells[i][j] = NULL;
		}
	}

	isActiveCells = new bool*[rows];
	for (int i = 0; i < rows; i++)
	{
		isActiveCells[i] = new bool[columns];
		for (int j = 0; j < columns; j++)
		{
			isActiveCells[i][j] = false;
		}
	}
	
}

Grid::~Grid() {
}

void Grid::Move(Unit * unit, double x, double y, double dt)
{
	// See which cell it was in.
	int oldCellJ = (int)((unit->x) / cellWidth);
	int oldCellI = (int)((unit->y) / cellHeight);

	//unit->entity->UpdatePosition(dt);
	// See which cell it's moving to.

	int cellJ = (int)((unit->entity->GetPosition().x) / cellWidth);
	int cellI = (int)((unit->entity->GetPosition().y) / cellHeight);

	// If it didn't change cells, we're done.
	if (oldCellJ == cellJ && oldCellI == cellI) return;

	unit->x = unit->entity->GetPosition().x;
	unit->y = unit->entity->GetPosition().y;

	// Unlink it from the list of its old cell.
	if (unit->p_prev != NULL)
	{
		unit->p_prev->p_next = unit->p_next;
	}

	if (unit->p_next != NULL)
	{
		unit->p_next->p_prev = unit->p_prev;
	}

	// If it's the head of a list, remove it.
	if (gridcells[oldCellI][oldCellJ] == unit)
	{
		
		gridcells[oldCellI][oldCellJ] = unit->p_next;
	}
	
	// Add it back to the grid at its new cell.
	AddToCell(unit);

}

vector<Entity*> Grid::GetStaticObjects()
{
	return staticObject;
}

void Grid::AddToCell(Unit * other)
{
	int j = (int)(other->entity->GetPosition().x / Grid::cellWidth);
	int i = (int)(other->entity->GetPosition().y / Grid::cellHeight);

	if (i < 0 || j < 0) //
	{
		DebugOut(L"%dOut of grid", j);
		return;
	}

	// Add to the front of list for the cell it's in.
	other->p_prev = NULL;
	
	other->p_next = gridcells[i][j];
	gridcells[i][j] = other;

	if (other->p_next != NULL)
	{
		other->p_next->p_prev = other;
	}
}

void Grid::HandleMelee()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			HandleCell(gridcells[i][j]);
		}
	}
}

void Grid::HandleCell(Unit * unit)
{
	while (unit != NULL)
	{
		Unit* other = unit->p_next;
		while (other != NULL)
		{
			if (unit->entity->GetPosition().x == other->entity->GetPosition().x &&
				unit->entity->GetPosition().y == other->entity->GetPosition().y)
			{
				HandleAttack(unit, other);
			}
			other = other->p_next;
		}
		unit = unit->p_next;
	}
}

void Grid::HandleCell(int x, int y)
{
	Unit* unit = gridcells[x][y];
	while (unit != NULL)
	{
		// Handle other units in this cell.
		HandleUnit(unit, unit->p_next);

		// Also try the neighboring cells.
		if (x > 0 && y > 0) HandleUnit(unit, gridcells[x - 1][y - 1]);
		if (x > 0) HandleUnit(unit, gridcells[x - 1][y]);
		if (y > 0) HandleUnit(unit, gridcells[x][y - 1]);
		if (x > 0 && y < rows - 1)
		{
			HandleUnit(unit, gridcells[x - 1][y + 1]);
		}
		unit = unit->p_next;
	}
}

void Grid::HandleUnit(Unit* unit, Unit* other)
{
	while (other != NULL)
	{
		if (distance(unit, other) < ATTACK_DISTANCE)
		{
			HandleAttack(unit, other);
		}

		other = other->p_next;
	}
}

void Grid::HandleAttack(Unit * unit, Unit * other)
{
}

double Grid::distance(Unit* unit, Unit* other)
{
	return sqrt((unit->entity->GetPosition().x - other->entity->GetPosition().x) * (unit->entity->GetPosition().x - other->entity->GetPosition().x) + (unit->entity->GetPosition().y - other->entity->GetPosition().y) * (unit->entity->GetPosition().y - other->entity->GetPosition().y));
}

Camera* Grid::GetCamera()
{
	return this->camera;
}

void Grid::SetCamera(Camera*camera)
{
	this->camera = camera;
}

void Grid::SetCellsActivate(Camera*camera) //Dat cac cell o trang thai activate (theo id)
{
	//i,y,rows   j,x,columns     i truoc, j sau
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{			
			isActiveCells[i][j] = false;
		}
	}
	
	BoxCollider r1 = camera->GetRect();
	for (int i = r1.bottom / cellHeight; i < r1.top / cellHeight; i++) //
		for (int j = r1.left / cellWidth; j < r1.right / cellWidth; j++)
		{
			isActiveCells[i][j] = true;
		}
}

bool** Grid::GetActivatedCells()
{
	return isActiveCells;
}

float Grid::GetCellHeight()
{
	return cellHeight;
}

float Grid::GetCellWidth()
{
	return cellWidth;
}

void Grid::CheckActivatedObjects()
{
	//lay cac unit hai ben ria map
	bool** activatedcells = GetActivatedCells();
	int jmax = 0;
	int jmin = 1000;
	for (int j = 0; j < columns; j++)
	{
		if (activatedcells[0][j] == true)
		{
			if (j > jmax)
				jmax = j;
			if (j < jmin)
			{
				jmin = j;
			}
		}
	}
	//lay huong di nhan vat
	Entity::EntityDirection playerdirection = player->GetMoveDirection();
	for (int i = 0; i < rows; i++)
		for (int j_full = 0; j_full < columns; j_full++)
		{
			if (gridcells[i][j_full] == NULL)
				continue;
			if (j_full < jmin)
			{ 
				if (gridcells[i][j_full]->entity->GetType() == Entity::PlayerType)
					j_full = j_full;
				gridcells[i][j_full]->entity->SetActive(false);
			}
			else
				if (j_full > jmax)
				{
					if (gridcells[i][j_full]->entity->GetType() == Entity::PlayerType)
						j_full = j_full;
					gridcells[i][j_full]->entity->SetActive(false);
				}
				else

					if (j_full == jmin)
					{
						if ((player->GetMoveDirection() == Entity::RightToLeft) && (gridcells[i][j_full]->entity->GetMoveDirection() == Entity::LeftToRight))
							if (!gridcells[i][j_full]->entity->IsActive())
							{
								Unit*tmpcells_toprev = gridcells[i][j_full]->p_prev;
								Unit*tmpcells_tonext = gridcells[i][j_full];
								while (tmpcells_tonext != NULL)
								{
									tmpcells_tonext->entity->SetActive(true);
									tmpcells_tonext = tmpcells_tonext->p_next;
								}
							}
					}
					else
						if (j_full == jmax)
						{
							if ((player->GetMoveDirection() == Entity::LeftToRight) && (gridcells[i][j_full]->entity->GetMoveDirection() == Entity::RightToLeft))
								if (!gridcells[i][j_full]->entity->IsActive())
								{
									Unit*tmpcells_toprev = gridcells[i][j_full]->p_prev;
									Unit*tmpcells_tonext = gridcells[i][j_full];
									while (tmpcells_tonext != NULL)
									{
										tmpcells_tonext->entity->SetActive(true);
										tmpcells_tonext = tmpcells_tonext->p_next;
									}
								}
						}
		}
}

Entity::EntityDirection Grid::GetDirection()
{
	return player->GetMoveDirection();
}

void Grid::SetPlayer(Player*player)
{
	this->player = player;
}

//Render - Update
void Grid::RenderActive()
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			if (gridcells[i][j] == NULL) continue;
			if (gridcells[i][j]->entity->IsActive()) {
				Unit*tmpcells_toprev = gridcells[i][j]->p_prev;
				Unit*tmpcells_tonext = gridcells[i][j];
				while (tmpcells_tonext != NULL)
				{
					if (tmpcells_tonext->entity->IsActive())
						tmpcells_tonext->entity->Render();
					tmpcells_tonext = tmpcells_tonext->p_next;
				}
				while (tmpcells_toprev != NULL)
				{
					if (tmpcells_toprev->entity->IsActive())
						tmpcells_toprev->entity->Render();
					tmpcells_toprev = tmpcells_toprev->p_prev;
				}
			}
		}
}

void Grid::UpdateActivatingCells(double dt)
{
	SetCellsActivate(this->camera);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{		
			if (gridcells[i][j] != NULL&&gridcells[i][j]->entity->IsActive()==true)
			{
				Unit*tmpcells_tonext = gridcells[i][j];
				while (tmpcells_tonext != NULL)
				{
					if (tmpcells_tonext->entity->IsActive())
						tmpcells_tonext->Move(tmpcells_tonext->entity->GetPosition().x, tmpcells_tonext->entity->GetPosition().y, dt);
					tmpcells_tonext = tmpcells_tonext->p_next;
				}
			}
		}
	}
}

void Grid::UpdateActive(double dt)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			if (gridcells[i][j] == NULL) continue;
			if (isActiveCells[i][j])
			{
				Unit*tmpcells_tonext = gridcells[i][j];
				while (tmpcells_tonext != NULL)
				{
					if (tmpcells_tonext->entity->GetType() == Entity::PlayerType)
						tmpcells_tonext = tmpcells_tonext;
					if (gridcells[i][j]->entity->IsActive())
						tmpcells_tonext->entity->Update(dt);
					tmpcells_tonext = tmpcells_tonext->p_next;
				}
			}
			
		}
}

Unit* Grid::GetGridCells(int i, int j)
{
	return this->gridcells[i][j];
}

Entity* Grid::GetEntity(int i, int j)
{
	if (gridcells[i][j] == NULL)
		return NULL;
	return this->gridcells[i][j]->entity;
}