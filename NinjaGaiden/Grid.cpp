#include "Grid.h"
#include"Unit.h"
#include"Debug.h"

#pragma region Kocare
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

vector<Entity*> Grid::GetStaticObjects()
{
	return staticObject;
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

Entity::EntityDirection Grid::GetDirection()
{
	return player->GetMoveDirection();
}

void Grid::SetPlayer(Player*player)
{
	this->player = player;
}

Unit* Grid::GetGridCells(int i, int j)
{
	return this->gridcells[i][j];
}

#pragma endregion

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

void Grid::AddToCell(Unit * other)
{
	int j = (int)(other->entity->GetPosition().x / Grid::cellWidth);
	int i = (int)(other->entity->GetPosition().y / Grid::cellHeight);

	if (i < 0 || j < 0) //
	{
		other->entity->SetActive(false);
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

void Grid::HandleGridCollision(double dt)
{
	int iPlayer = player->GetPosition().y / cellHeight;
	int jPlayer = player->GetPosition().x / cellWidth;

	if (iPlayer < 0 || jPlayer < 0) return;

	HandleGridSubFunction(iPlayer, jPlayer, dt);

	// Also try the neighboring cells.
	if (player->GetMoveDirection() == Entity::RightToLeft)
	{
		if (jPlayer > 0 && iPlayer > 0) HandleGridSubFunction(iPlayer - 1, jPlayer - 1, dt); //
		if (jPlayer > 0) HandleGridSubFunction(iPlayer, jPlayer - 1, dt); //
		if (iPlayer < rows - 1) HandleGridSubFunction(iPlayer + 1, jPlayer, dt); //
		if (jPlayer > 0 && iPlayer < rows - 1) HandleGridSubFunction(iPlayer + 1, jPlayer - 1, dt); //
	}
	if (player->GetMoveDirection() == Entity::LeftToRight)
	{
		if (jPlayer < columns - 1 && iPlayer < rows - 1) HandleGridSubFunction(iPlayer + 1, jPlayer + 1, dt);//
		if (jPlayer < columns - 1 && iPlayer >0) HandleGridSubFunction(iPlayer - 1, jPlayer + 1, dt);//
		if (jPlayer < columns - 1) HandleGridSubFunction(iPlayer, jPlayer + 1, dt);//
		if (iPlayer < rows - 1) HandleGridSubFunction(iPlayer+1, jPlayer, dt);//
	}
}

void Grid::HandleGridSubFunction(int i, int j, double dt)
{
	auto side = Entity::NotKnow;
	HurtingTime = 0;

	Unit*tmpcells_tonext = gridcells[i][j];
	while (tmpcells_tonext != NULL)
	{
		if (tmpcells_tonext->entity->IsActive() == true && tmpcells_tonext->entity->GetTag() != Entity::Player)
		{
			//check enemy in attack radius
			BoxCollider AttackRadius;
			AttackRadius.top = player->GetPosition().y + 20;
			AttackRadius.bottom = player->GetPosition().y - 20;
			AttackRadius.left = player->GetPosition().x - 42;
			AttackRadius.right = player->GetPosition().x + 42;

			if (!IsOverlap(AttackRadius, tmpcells_tonext->entity->GetRect()))
			{
				tmpcells_tonext = tmpcells_tonext->p_next;
				continue;
			}

			//collision ryu attack
			if (player->GetState() == PlayerState::Slash || player->GetState() == PlayerState::CrouchSlash)
			{
				Entity* Katana = new Entity;
				Katana->SetType(Entity::RyuWeaponType);
				Katana->SetTag(Entity::Katana);
				if (player->GetMoveDirection() == Entity::LeftToRight&&player->GetState() == PlayerState::Slash)
					Katana->SetPosition(player->GetPosition().x + 21, player->GetPosition().y + 5.5);
				else
					if (player->GetMoveDirection() == Entity::RightToLeft&&player->GetState() == PlayerState::Slash)
						Katana->SetPosition(player->GetPosition().x - 21, player->GetPosition().y - 5.5);
					else
						if (player->GetMoveDirection() == Entity::LeftToRight&&player->GetState() == PlayerState::CrouchSlash)
							Katana->SetPosition(player->GetPosition().x + 21, player->GetPosition().y + 0);
						else
							if (player->GetMoveDirection() == Entity::RightToLeft&&player->GetState() == PlayerState::CrouchSlash)
								Katana->SetPosition(player->GetPosition().x - 21, player->GetPosition().y - 0);
							
				Katana->SetWidth(19);
				Katana->SetHeight(7);
				Katana->SetVx(0);
				Katana->SetVy(0);

				float collisionTime = CollisionDetector::SweptAABB(tmpcells_tonext->entity, Katana, side, dt);
				if (collisionTime != 2) // collide happen
				{
					if (tmpcells_tonext->entity->GetType() == Entity::EnemyType)
					{
						tmpcells_tonext->entity->OnCollision(Katana, side, dt);
						if (tmpcells_tonext == NULL)
							continue;
					}
					tmpcells_tonext = tmpcells_tonext->p_next;
					continue;
				}
			}

			//collision ryu beaten
			if (tmpcells_tonext->entity->IsActive()) {
				float collisionTime = CollisionDetector::SweptAABB(tmpcells_tonext->entity, player, side, dt);
				if (collisionTime == 2)
				{
					tmpcells_tonext = tmpcells_tonext->p_next;
					continue;
				}
				player->OnCollision(tmpcells_tonext->GetEntity(), side, collisionTime);			
			}
		}
		tmpcells_tonext = tmpcells_tonext->p_next;
	}
}


bool Grid::IsOverlap(BoxCollider r1, BoxCollider r2) {
	if (r1.bottom > r2.top || r1.top < r2.bottom || r1.left > r2.right || r1.right < r2.left)
		return false;
	return true;
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
			if (gridcells[i][j] != NULL&&isActiveCells[i][j]==true)
			{
				Unit*tmpcells_tonext = gridcells[i][j];	
				Unit*tmpcells_toprev = gridcells[i][j]->p_prev;
				while (tmpcells_tonext != NULL)
				{
					if (tmpcells_tonext->entity->IsActive())
						tmpcells_tonext->Move(tmpcells_tonext->entity->GetPosition().x, tmpcells_tonext->entity->GetPosition().y, dt);
					tmpcells_tonext = tmpcells_tonext->p_next;
				}
				while (tmpcells_toprev != NULL)
				{
					if (tmpcells_toprev->entity->IsActive())
						tmpcells_toprev->Move(tmpcells_toprev->entity->GetPosition().x, tmpcells_toprev->entity->GetPosition().y, dt);
					tmpcells_toprev = tmpcells_toprev->p_prev;
				}				
			}
		}
	}
}

///
void Grid::UpdateActive(double dt)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			if (gridcells[i][j] == NULL) continue;
			if (isActiveCells[i][j])
			{
				Unit*tmpcells_toprev = gridcells[i][j]->p_prev;
				Unit*tmpcells_tonext = gridcells[i][j];
				while (tmpcells_tonext != NULL)
				{
					/*if (tmpcells_tonext->entity->GetType() == Entity::PlayerType)
						tmpcells_tonext = tmpcells_tonext;*/
					if (gridcells[i][j]->entity->IsActive())
						tmpcells_tonext->entity->Update(dt);
					tmpcells_tonext = tmpcells_tonext->p_next;
				}
				while (tmpcells_toprev != NULL)
				{
					/*if (tmpcells_toprev->entity->GetType() == Entity::PlayerType)
						tmpcells_toprev = tmpcells_toprev;*/
					if (gridcells[i][j]->entity->IsActive())
						tmpcells_toprev->entity->Update(dt);
					tmpcells_toprev = tmpcells_toprev->p_prev;
				}
			}
			
		}
}
