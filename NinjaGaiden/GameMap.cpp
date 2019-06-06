#include "GameMap.h"
#pragma region get, set, add for Tileset
Tileset::Tileset(int rows, int columns, int tileWidth, int tileHeight) {
	this->rows = rows;
	this->columns = columns;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
}

void Tileset::Add(int id, LPSPRITE tile) {
	tiles[id] = tile;
}

int Tileset::GetRows() {
	return rows;
}

int Tileset::GetColumns() {
	return columns;
}

int Tileset::GetTileWidth() {
	return tileWidth;
}

int Tileset::GetTileHeight() {
	return tileHeight;
}

LPSPRITE Tileset::GetSprite(int id) {
	return tiles[id];
}

#pragma endregion

GameMap::GameMap(char * tilesetPath, char * mapPath, int tileHeight, int tileWidth) {
	LoadTileset(tilesetPath, tileWidth, tileHeight);
	SetMapPath(mapPath);
}

void GameMap::SetMapPath(char * mapPath) {
	this->mapPath = mapPath;
	std::fstream reader(mapPath);
	if (reader.fail()) {
		return;
	}
	reader >> rows;
	reader >> columns;
	mapIDs = new int*[rows];

	for (int i = 0; i < rows; i++) {
		mapIDs[i] = new int[columns];
		for (int j = 0; j < columns; j++) {
			reader >> mapIDs[i][j];
		}
	}

	BoxCollider gridRect = BoxCollider(GetHeight(), 0, 0, GetWidth());
	grid = Grid::GetInstance(gridRect);

	reader >> mapObject;
	int id = 0;
	int i = 0;
	int posx = 0;
	int posy = 0;
	int wid = 0;
	int hei = 0;
	int direction = 1;
	for (int i = 0; i < mapObject; i++) {
		reader >> id;
		reader >> posx;
		reader >> posy;
		reader >> wid;
		reader >> hei;
		reader >> direction;
		if (i == 39)
			i = i;
		switch (id) {
		case 0: {
			Entity *ground = new Entity();
			ground->SetTag((Entity::EntityTag)id);
			ground->SetType(Entity::StaticType);
			ground->SetStatic(true);
			ground->SetPosition(D3DXVECTOR3(posx + wid / 2, posy - hei / 2, 0));
			ground->SetWidth(wid);
			ground->SetHeight(hei);
			grid->staticObject.push_back(ground);
		}
				break;
		case 1: {
			Sparta *sparta = new Sparta();
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			sparta->SetSpawnBox(box, direction);			
			unit = new Unit(grid, sparta);
		}
				break;
		case 2: {
			Cat *cat = new Cat();
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			cat->SetSpawnBox(box, direction);
			//enemyGroup->AddObject(cat);
			unit = new Unit(grid, cat);
		}
				break;
		case 3: {
			Thrower *thrower = new Thrower();
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			thrower->SetSpawnBox(box, direction);
			//enemyGroup->AddObject(thrower);
			unit = new Unit(grid, thrower);
		}
				break;
		case 4: {
			Eagle *eagle = new Eagle();
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			eagle->SetSpawnBox(box, direction);
			//enemyGroup->AddObject(eagle);
			unit = new Unit(grid, eagle);
		}
				break;
		case 5: {
			Soldier *soldier = new Soldier();
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			soldier->SetSpawnBox(box, direction);
			//enemyGroup->AddObject(soldier);
			unit = new Unit(grid, soldier);
		}
				break;
		}
	}
}

#pragma region get, set, add for GameMap
	int GameMap::GetWidth() {
		return tileset->GetTileWidth() * columns;
	}

	int GameMap::GetHeight() {
		return tileset->GetTileHeight() * rows;
	}

	int GameMap::GetTileWidth() {
		return tileset->GetTileWidth();
	}

	int GameMap::GetTileHeight() {
		return tileset->GetTileHeight();
	}

	Grid * GameMap::GetGrid() {
		return grid;
	}

	Unit * GameMap::GetUnit()
	{
		return this->unit;
	}

	void GameMap::SetCamera(Camera * cam) {
		camera = cam;
	}

	Camera* GameMap::GetCamera()
	{
		return this->camera;
	}


#pragma endregion
	void GameMap::Draw() {

		for (size_t i = 0; i < 1; i++) {

			//chieu dai va chieu rong cua tile
			int tileWidth = tileset->GetTileWidth();
			int tileHeight = tileset->GetTileHeight();

			for (int m = 0; m < this->rows; m++) {
				for (int n = 0; n < this->columns; n++) {
					int id = mapIDs[m][n];
					LPSPRITE sprite = tileset->GetSprite(id);

					BoxCollider spriteBound;
					spriteBound.top = (rows - m - 1) * tileHeight;
					spriteBound.bottom = spriteBound.top - tileHeight;
					spriteBound.left = n * tileWidth;
					spriteBound.right = spriteBound.left + tileWidth;

					if (camera->IsCollide(spriteBound)) {
						D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, (rows - m - 1) * tileHeight + tileHeight / 2, 0);
						sprite->SetHeight(tileHeight);
						sprite->SetWidth(tileWidth);
						sprite->Draw(position, BoxCollider());
					}
				}

			}
		}

	}
/*
	void GameMap::CheckActive(D3DXVECTOR2 velocity) {
		//enemyGroup->CheckActive(camera, velocity);
	}
*/
/*
	void GameMap::GetActiveObject(std::vector<Entity*> &entities) {
		//enemyGroup->GetActiveObject(entities);
	}

	void GameMap::UpdateActive(double dt) {
		//enemyGroup->Update(dt);
	}

	void GameMap::RenderActive() {
		//enemyGroup->Render();
	}
*/
	GameMap::~GameMap() {
		delete mapIDs;
	}

	void GameMap::LoadTileset(char * filePath, int tileWidth, int tileHeight) {
		//Parse map tu file 
		Textures::GetInstance()->Add(TEX_STAGE31, filePath, D3DCOLOR_XRGB(255, 0, 255));
		auto texture = Textures::GetInstance()->Get(TEX_STAGE31);
		D3DSURFACE_DESC desc;
		texture->GetLevelDesc(0, &desc);
		auto width = desc.Width;
		auto height = desc.Height;
		tileset = new Tileset(height / tileHeight, width / tileWidth, tileWidth, tileHeight);

		for (int i = 0; i < tileset->GetRows(); i++) {
			for (int j = 0; j < tileset->GetColumns(); j++) {
				BoxCollider r;
				r.top = i * tileHeight;
				r.left = j * tileWidth;
				r.bottom = r.top + tileHeight;
				r.right = r.left + tileWidth;
				LPSPRITE sprite = new Sprite(r, texture);
				tileset->Add(i * tileset->GetColumns() + j, sprite);
			}
		}
	}

