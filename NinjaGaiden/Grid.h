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
#include "SoundManager.h"

class Unit;

//Tao ra grid tu map
class Grid {

	int mapWidth;
	int mapHeight;
	int rows;
	int columns;
	float cellWidth;
	float cellHeight;

	Player*player;//lay huong di nhan vat
	Unit*** gridcells; //Unit* gridCells[rows][columns]
	
	Camera*camera;

	static Grid*instance;

	

public:
	vector<Entity*> staticObject; //array of static entity (ground)
	vector<Entity*> GetStaticObjects();

	void AddToCell(Unit *unit); //add a unit to cell
	void Move(Unit* unit, double x, double y, double dt); //

	bool **isActiveCells;//two dimensions array of all cells overlaped with camera
	void SetCellsActivate(Camera*camera);//Set value for array above
	bool** GetActivatedCells();

	float GetCellWidth();
	float GetCellHeight();

	void SetPlayer(Player*);
	Player::EntityDirection GetDirection();
	

	void CheckActivatedObjects(); 

	Camera*GetCamera();
	void SetCamera(Camera*camera);

	
	Grid(BoxCollider r, int rows = GRID_ROWS, int columns = GRID_COLUMNS);//constructor cua grid dua vao khung cua the gioi, so luong hang, so luong cot
	~Grid();
	int GetRows() { return rows; }
	int GetColumns() { return columns; }

	void RenderActive();
	void UpdateActivatingCells(double dt);//update the isActiveCell after a frame
	void UpdateActive(double dt);
	
	void HandleGridCollisionPlayerEnemy(double dt); //unit = gridcells[i][j]
	void HandleGridCollisionPlayerEnemySubFunction(int i, int j, double dt);
	bool IsOverlap(BoxCollider r1, BoxCollider r2);
	double HurtingTime;

	void HandleGridCollisionRyuWeaponEnemy(double dt);
	void HandleGridCollisionRyuWeaponEnemySubFunction(int i, int j,Entity*weapon, double dt);

	Unit* GetGridCells(int, int);
	
	static Grid* GetInstance(BoxCollider box);

	void RemoveFromGrid(Unit*);

	void ClearAllWeapon();
};