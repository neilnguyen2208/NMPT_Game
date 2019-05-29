#pragma once
#include "Sprites.h"
#include "Textures.h"
#include "Camera.h"
#include "Grid.h"
#include "Sparta.h"
#include "Cat.h"
#include "Thrower.h"
#include "Eagle.h"
#include "Soldier.h"
#include "Item.h"
#include <iostream>
#include <fstream>
#include"Unit.h"

class Tileset {
	int tileWidth;
	int tileHeight;
	int rows;
	int columns;
	unordered_map<int, LPSPRITE> tiles;
public:
	Tileset(int rows, int columns, int tileWidth, int tileHeight);
	void Add(int id, LPSPRITE tile);
	int GetRows();
	int GetColumns();
	int GetTileWidth();
	int GetTileHeight();
	LPSPRITE GetSprite(int id);
};

class GameMap {
public:
	GameMap(char* tilesetPath, char* mapPath, int tileHeight = 32, int tileWidth = 32);
	void SetMapPath(char *mapPath);
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	Grid *GetGrid();//
	Unit*GetUnit();
	Camera* GetCamera();
	void SetCamera(Camera *cam);
	void Draw();
	//Player* GetPlayer();
	//void SetPlayer(Player* player);
	//Active objects
	//void CheckActive(D3DXVECTOR2 velocity);
	//void GetActiveObject(std::vector<Entity*> &entities);
	//void UpdateActive(double dt);
	//void RenderActive();
	
	~GameMap();
private:
	
	Player*player;
	Unit*unit;
	Grid *grid;
	void LoadTileset(char *filePath, int tileWidth, int tileHeight);
	Tileset *tileset;
	LPCSTR mapPath;
	int rows;
	int columns;
	int mapObject;
	int **mapIDs;
	std::unordered_map<int, LPSPRITE> listTileset;
	Camera *camera;
};