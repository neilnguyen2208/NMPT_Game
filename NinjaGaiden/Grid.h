#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "Entity.h"
#include "GameConfig.h"
#include "MyHelper.h"
#include "Enemy.h"

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
	void HandleMelee();
	void HandleCell(Unit* unit);
	void HandleCell(int x, int y); //unit = gridcells[x][y]
	void HandleAttack(Unit* unit, Unit* other);
	void HandleUnit(Unit* unit, Unit* other);
	double distance(Unit* unit, Unit* other);	
	Camera*camera;

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

	Grid();
	Grid(BoxCollider r, int rows = GRID_ROWS, int columns = GRID_COLUMNS);//constructor cua grid dua vao khung cua the gioi, so luong hang, so luong cot
	~Grid();
	int GetRows() { return rows; }
	int GetColumns() { return columns; }

	void RenderActive();
	void UpdateActivatingCells(double dt);//update the isActiveCell after a frame
	void UpdateActive(double dt);
	//void UpdatePosition(double dt);

	Unit* GetGridCells(int, int);
	Entity* GetEntity(int, int);
	//vector<Unit*> 
};