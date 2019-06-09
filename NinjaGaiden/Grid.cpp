#include "Grid.h"
#include"Unit.h"

#pragma region Kocare
Grid* Grid::instance = NULL;

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

float Grid::GetCellHeight()
{
	return cellHeight;
}

float Grid::GetCellWidth()
{
	return cellWidth;
}

void Grid::SetPlayer(Player*player)
{
	this->player = player;
}

Unit* Grid::GetGridCells(int i, int j)
{
	return this->gridcells[i][j];
}

Grid * Grid::GetInstance(BoxCollider box)
{
	if (instance == NULL)
		instance = new Grid(box);
	return instance;
}

void Grid::Move(Unit * unit, double x, double y, double dt)
{
	// See which cell it was in.
	int oldCellJ = (int)((unit->x) / cellWidth);
	int oldCellI = (int)((unit->y) / cellHeight);

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

	if (i < 0 || j < 0 || i>rows - 1 || j>columns - 1) //
	{
		other->entity->MakeInactive();
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
#pragma endregion
void Grid::HandleGridCollisionPlayerEnemy(double dt)
{
	//int iPlayer = player->GetPosition().y / cellHeight;
	//int jPlayer = player->GetPosition().x / cellWidth;

	//if (iPlayer < 0 || jPlayer < 0) return;

	//HandleGridCollisionPlayerEnemySubFunction(iPlayer, jPlayer, dt);
	//
	//// Also try the neighboring cells.
	//if (iPlayer > 0) HandleGridCollisionPlayerEnemySubFunction(iPlayer - 1, jPlayer, dt);
	//if (iPlayer < rows - 1) HandleGridCollisionPlayerEnemySubFunction(iPlayer + 1, jPlayer, dt);//

	//if (player->GetMoveDirection() == Entity::RightToLeft)
	//{
	//	if (jPlayer > 0 && iPlayer > 0) HandleGridCollisionPlayerEnemySubFunction(iPlayer - 1, jPlayer - 1, dt); //
	//	if (jPlayer > 0) HandleGridCollisionPlayerEnemySubFunction(iPlayer, jPlayer - 1, dt); //
	//	if (jPlayer > 0 && iPlayer < rows - 1) HandleGridCollisionPlayerEnemySubFunction(iPlayer + 1, jPlayer - 1, dt); //		
	//}
	//if (player->GetMoveDirection() == Entity::LeftToRight)
	//{
	//	if (jPlayer < columns - 1 && iPlayer < rows - 1) HandleGridCollisionPlayerEnemySubFunction(iPlayer + 1, jPlayer + 1, dt);//
	//	if (jPlayer < columns - 1 && iPlayer >0) HandleGridCollisionPlayerEnemySubFunction(iPlayer - 1, jPlayer + 1, dt);//
	//	if (jPlayer < columns - 1) HandleGridCollisionPlayerEnemySubFunction(iPlayer, jPlayer + 1, dt);//		
	//}
}

void Grid::HandleGridCollisionPlayerEnemySubFunction(int i, int j, double dt)
{
	auto side = Entity::NotKnow;          
	Unit*tmpcells_tonext = gridcells[i][j];
	
	//Process collide to next
	while (tmpcells_tonext != NULL)
	{
		if (tmpcells_tonext->entity->IsActive() == true && tmpcells_tonext->entity->GetTag() != Entity::Player)
		{	
			//check enemy in normal attack radius
			BoxCollider AttackRadius;
			AttackRadius.top = player->GetPosition().y + 20;
			AttackRadius.bottom = player->GetPosition().y - 20;
			AttackRadius.left = player->GetPosition().x - 42; //42
			AttackRadius.right = player->GetPosition().x + 42;

			if (!IsOverlap(AttackRadius, tmpcells_tonext->entity->GetRect()))
			{
				tmpcells_tonext = tmpcells_tonext->p_next;
				continue;
			}

			//collision ryu attack
			if( (player->GetState() == PlayerState::Slash || player->GetState() == PlayerState::CrouchSlash))
			{
				Entity* Katana = new Entity;
				Katana->SetType(Entity::RyuWeaponType);
				Katana->SetTag(Entity::Katana);
				Katana->SetWidth(19); //19
				Katana->SetHeight(7); //7
				Katana->SetVx(0);
				Katana->SetVy(0);
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
							
				float collisionTime = CollisionDetector::SweptAABB(tmpcells_tonext->entity, Katana, side, dt);
				if (collisionTime != 2) // collide happen
				{
					if (tmpcells_tonext->entity->GetType() == Entity::EnemyType||tmpcells_tonext->entity->GetType()==Entity::EnemyWeaponType || tmpcells_tonext->entity->GetType() == Entity::ItemType)
					{				
						if (tmpcells_tonext->entity->GetAliveState()==Entity::Die)
						{
							tmpcells_tonext = tmpcells_tonext->p_next;
							if (Katana != NULL)
							{
								delete Katana;
							}
							continue;
						}
						tmpcells_tonext->entity->OnCollision(Katana, side, dt); 
						player->AddScore(tmpcells_tonext->entity->GetTag()); // cộng điểm cho ninja chi chém enemy						
					}					
					tmpcells_tonext = tmpcells_tonext->p_next;
					if (Katana != NULL)
					{
						delete Katana;
					}
					continue;
				}
			}

			//collision ryu beaten
			if (tmpcells_tonext->entity->IsActive() && ((tmpcells_tonext->entity->GetAliveState() != Entity::Die && tmpcells_tonext->entity->GetType() != Entity::ItemType) || (tmpcells_tonext->entity->GetType() == Entity::ItemType && tmpcells_tonext->entity->GetStatusItem() != Entity::UnavailableItem))) {
				float collisionTime = CollisionDetector::SweptAABB(tmpcells_tonext->entity, player, side, dt);
				if (collisionTime == 2)
				{
					tmpcells_tonext = tmpcells_tonext->p_next;
					continue;
				}
				player->OnCollision(tmpcells_tonext->GetEntity(), side, collisionTime);

				if (tmpcells_tonext->entity->GetType() == Entity::ItemType)
				{
					player->AddItem(tmpcells_tonext->entity->GetTag());
					tmpcells_tonext->entity->SetActive(false);
					tmpcells_tonext->entity->SetAliveState(Entity::Remove);
				}
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
	int iMax = rows - 1;
	int jMax = camera->GetRect().right / cellWidth;
	int jMin = camera->GetRect().left / cellWidth;

	for (int i = 0; i <= iMax; i++)
		for (int j = 0; j <= columns - 1; j++)
		{			
			if (gridcells[i][j] == NULL)
				continue;
			Unit*tmpcells_tonext = gridcells[i][j];
			if (j < jMin)
			{
				gridcells[i][j]->entity->SetActive(false);
			}
			else
				if (j > jMax)
				{
					gridcells[i][j]->entity->SetActive(false);				
				}
				else
					if (j >= jMin && j <= jMax)
					{					
						if ((j == jMin))
						{							
							while (tmpcells_tonext != NULL)
							{
								if (tmpcells_tonext->entity->IsActive() == false && tmpcells_tonext->entity->GetMoveDirection() == Entity::LeftToRight)
								{
									if (player->useitemtimeFreeze == true && tmpcells_tonext->entity->GetType() == Entity::EnemyType)
									{
										tmpcells_tonext = tmpcells_tonext->p_next;
										continue;
									}
									tmpcells_tonext->entity->SetActive(true);
								}
								tmpcells_tonext = tmpcells_tonext->p_next;
							}
						}
						else if(j == jMax)
						{							
								while (tmpcells_tonext != NULL)
								{
									if (tmpcells_tonext->entity->IsActive() == false && (tmpcells_tonext->entity->GetMoveDirection() == Entity::RightToLeft))
									{
										if (player->useitemtimeFreeze == true && tmpcells_tonext->entity->GetType() == Entity::EnemyType)
										{
											tmpcells_tonext = tmpcells_tonext->p_next;
											continue;
										}
										tmpcells_tonext->entity->SetActive(true);
									}
									tmpcells_tonext = tmpcells_tonext->p_next;
								}								
						}
						else
							if (tmpcells_tonext->entity->GetType() == Entity::EnemyWeaponType)
							{
								while (tmpcells_tonext != NULL)
								{
									if (tmpcells_tonext->entity->IsActive() == false&& tmpcells_tonext->entity->GetAliveState() != Entity::Die)
									{
										if (player->useitemtimeFreeze == true)
										{
											tmpcells_tonext = tmpcells_tonext->p_next;
											continue;
										}
										tmpcells_tonext->entity->SetActive(true);
									}
									tmpcells_tonext = tmpcells_tonext->p_next;
								}							
							}
					}
		}
}

//Render - Update
void Grid::RenderActive()
{
	int iMax = rows - 1;
	int jMax = camera->GetRect().right / cellWidth;
	int jMin = camera->GetRect().left / cellWidth;

	for (int i = 0; i <= iMax; i++)
		for (int j = jMin; j <= jMax; j++)
		{
			if (gridcells[i][j] == NULL) continue;			 			
			Unit*tmpcells_tonext = gridcells[i][j];
			while (tmpcells_tonext != NULL)
			{
				if (tmpcells_tonext->entity->IsActive())
					tmpcells_tonext->entity->Render();
				tmpcells_tonext = tmpcells_tonext->p_next;
			}			
		}
}

void Grid::UpdateActivatingCells(double dt)
{
	int iMax = rows - 1;
	int jMax = camera->GetRect().right / cellWidth;
	int jMin = camera->GetRect().left / cellWidth;

	for (int i = 0; i <= iMax; i++)
		for (int j = jMin; j <= jMax; j++)
		{		
			if (gridcells[i][j] != NULL)
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

void Grid::UpdateActive(double dt)
{
	int iMax = rows - 1;
	int jMax = camera->GetRect().right / cellWidth;
	int jMin = camera->GetRect().left / cellWidth;

	for (int i = 0; i <= iMax; i++)
		for (int j = jMin; j <= jMax; j++)
		{
			if (gridcells[i][j] == NULL) continue;
			
			Unit*tmpcells_tonext = gridcells[i][j];
			while (tmpcells_tonext != NULL)
			{
				if (tmpcells_tonext->entity->IsActive())
				{
					if (player->useitemtimeFreeze == true && tmpcells_tonext->entity->GetType() == Entity::EnemyType)
					{
						if (tmpcells_tonext->entity->GetAliveState() == Entity::Beaten || tmpcells_tonext->entity->GetAliveState() == Entity::Die)
							tmpcells_tonext->entity->Update(dt);						
						tmpcells_tonext = tmpcells_tonext->p_next;;					
						continue;
					}
					tmpcells_tonext->entity->Update(dt);
				}
				tmpcells_tonext = tmpcells_tonext->p_next;
			}
		}
	player->checkTimeFreezeSkill();
}

void Grid::RemoveFromGrid(Unit *unit)
{
	int i = unit->entity->GetPosition().y/cellHeight;
	int j = unit->entity->GetPosition().x/cellWidth;
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
	if (gridcells[i][j] == unit)
	{
		gridcells[i][j] = unit->p_next;
	}
}

void Grid::ClearAllWeapon()
{
	for (int i = 0; i <= rows-1; i++)
		for (int j = 0; j <= columns-1; j++)		
		{
			if (gridcells[i][j] == NULL) continue;		
				Unit*tmpcells_toprev = gridcells[i][j]->p_prev;
				Unit*tmpcells_tonext = gridcells[i][j];
				while (tmpcells_tonext != NULL)
				{
					if ((tmpcells_tonext->entity->GetType() == Entity::EnemyWeaponType || tmpcells_tonext->entity->GetType() == Entity::RyuWeaponType || tmpcells_tonext->entity->GetType() == Entity::ItemType)&& tmpcells_tonext->entity->GetAliveState() == Entity::Remove)
						RemoveFromGrid(tmpcells_tonext);
					tmpcells_tonext = tmpcells_tonext->p_next;
				}
				while (tmpcells_toprev != NULL)
				{
					if ((tmpcells_toprev->entity->GetType() == Entity::EnemyWeaponType || tmpcells_toprev->entity->GetType() == Entity::RyuWeaponType || tmpcells_toprev->entity->GetType() == Entity::ItemType) && tmpcells_toprev->entity->GetAliveState() == Entity::Remove)
						RemoveFromGrid(tmpcells_toprev);
					tmpcells_toprev = tmpcells_toprev->p_prev;
				}	
		}
}

void Grid::HandleGridCollisionRyuWeaponEnemy(double dt)
{
	int iMax = rows-1;
	int jMax = camera->GetRect().right / cellWidth;
	int jMin = camera->GetRect().left / cellWidth;

	for (int i = 0; i <= iMax; i++)
		for (int j = jMin; j <= jMax; j++)
		{
			if (gridcells[i][j] == NULL)
				continue;
			Unit*tmpcells_tonext = gridcells[i][j];
			while (tmpcells_tonext != NULL)
			{
				if (tmpcells_tonext->entity->IsActive() && tmpcells_tonext->entity->GetType() == Entity::RyuWeaponType)
				{
					Entity*ryuWeapon = tmpcells_tonext->entity;
					HandleGridCollisionRyuWeaponEnemySubFunction(i, j,ryuWeapon, dt);

					// Also try the neighboring cells.
					if (i < rows - 1) HandleGridCollisionRyuWeaponEnemySubFunction(i + 1, j,ryuWeapon, dt); //
					if (i > 0) HandleGridCollisionRyuWeaponEnemySubFunction(i - 1, j,ryuWeapon, dt);
					if (player->GetMoveDirection() == Entity::RightToLeft)
					{
						if (j > 0 && i > 0) HandleGridCollisionRyuWeaponEnemySubFunction(i - 1, j - 1,ryuWeapon, dt); //
						if (j > 0) HandleGridCollisionRyuWeaponEnemySubFunction(i, j - 1,ryuWeapon, dt); //						
						if (j > 0 && i < rows - 1) HandleGridCollisionRyuWeaponEnemySubFunction(i + 1, j - 1,ryuWeapon, dt); //
					}
					if (player->GetMoveDirection() == Entity::LeftToRight)
					{
						if (j < columns - 1 && i < rows - 1) HandleGridCollisionRyuWeaponEnemySubFunction(i + 1, j + 1,ryuWeapon, dt);//
						if (j < columns - 1 &&i  >0) HandleGridCollisionRyuWeaponEnemySubFunction(i - 1, j + 1,ryuWeapon, dt);//
						if (j < columns - 1) HandleGridCollisionRyuWeaponEnemySubFunction(i, j + 1,ryuWeapon, dt);//
					}
				}
				tmpcells_tonext = tmpcells_tonext->p_next;
			}
		}
}

void Grid::HandleGridCollisionRyuWeaponEnemySubFunction(int i, int j, Entity*ryuWeapon, double dt)
{
	auto side = Entity::NotKnow;

	Unit*tmpcells_tonext = gridcells[i][j];

	//Process collide to next
	while (tmpcells_tonext != NULL)
	{
		if (tmpcells_tonext->entity->IsActive() == true && tmpcells_tonext->entity->GetType() != Entity::RyuWeaponType)
		{
			if (ryuWeapon->GetTag() == Entity::EntityTag::RedShuriken&&tmpcells_tonext->entity->GetType() == Entity::EntityType::PlayerType) //collsion ryu and red shuriken
			{
				float timeCollision = CollisionDetector::SweptAABB(ryuWeapon, tmpcells_tonext->entity, side, dt);
				if (timeCollision != 2) // collide happen
				{
					ryuWeapon->OnCollision(tmpcells_tonext->entity, side, dt);
				}
			}
			if (tmpcells_tonext->entity->GetType() != Entity::PlayerType)
				//collision ryu weapon enemy
			{
				float collisionTime_1 = CollisionDetector::SweptAABB(tmpcells_tonext->entity, ryuWeapon, side, dt);
				float collisionTime_2 = CollisionDetector::SweptAABB(ryuWeapon, tmpcells_tonext->entity, side, dt);
				if (collisionTime_1 != 2) // collide happen
				{
					if (tmpcells_tonext->entity->GetType() == Entity::EnemyType || tmpcells_tonext->entity->GetType() == Entity::EnemyWeaponType || tmpcells_tonext->entity->GetType() == Entity::ItemType)
					{
						tmpcells_tonext->entity->OnCollision(ryuWeapon, side, dt);
					}
				}
				if (collisionTime_2 != 2)
				{
					if (tmpcells_tonext->entity->GetType() == Entity::EnemyType || tmpcells_tonext->entity->GetType() == Entity::EnemyWeaponType || tmpcells_tonext->entity->GetType() == Entity::ItemType)
					{
						ryuWeapon->OnCollision(tmpcells_tonext->entity, side, dt);
					}
				}
			}
		}
		tmpcells_tonext = tmpcells_tonext->p_next;
	}
}