#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "Entity.h"
#include "GameConfig.h"
#include "MyHelper.h"
#include "Enemy.h"
#include "PlayerData.h"
#include "PlayerState.h"

class Unit;

//Tao ra grid tu map
class Grid {

	int mapWidth;
	int mapHeight;
	int rows;
	int columns;
	float cellWidth;
	float cellHeight;
	Unit*** gridcells; //Unit* gridCells[rows][columns]
	static Grid*instance;
	Player*player;
public:
	vector<Entity*> staticObject; //array of static entity (ground)
	vector<Entity*> GetStaticObjects();

	void AddToCell(Unit *unit); //add a unit to cell
	void Move(Unit* unit, double x, double y, double dt); //

	float GetCellWidth();
	float GetCellHeight();

	void CheckActivatedObjects(); 
	
	Grid(BoxCollider r);//constructor cua grid dua vao khung cua the gioi, so luong hang, so luong cot
	~Grid();
	int GetRows() { return rows; }
	int GetColumns() { return columns; }

	void RenderActive();
	void UpdateActivatingCells(double dt);//update the isActiveCell after a frame
	void UpdateActive(double dt);
	
	void HandleGridCollisionPlayerEnemy(double dt); //unit = gridcells[i][j]
	void HandleGridCollisionPlayerEnemySubFunction(int i, int j, double dt);
	bool IsOverlap(BoxCollider r1, BoxCollider r2);

	void HandleGridCollisionRyuWeaponEnemy(double dt);
	void HandleGridCollisionRyuWeaponEnemySubFunction(int i, int j,Entity*weapon, double dt);

	Unit* GetGridCells(int, int);
	
	static Grid* GetInstance(BoxCollider box);

	void RemoveFromGrid(Unit*);

	void ClearAllWeapon();
	void Reset();
};