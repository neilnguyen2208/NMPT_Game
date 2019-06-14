#include "GameMap.h"
#include"ExternalDataCollector.h"
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
	if (ExternalDataCollector::GetInstance()->GetScene() == ExternalDataCollector::Scene3_1)
	{
		LoadTileset_1(tilesetPath, tileWidth, tileHeight); SetMapPath(mapPath);
	}
	if (ExternalDataCollector::GetInstance()->GetScene() == ExternalDataCollector::Scene3_2)
	{
		LoadTileset_2(tilesetPath, tileWidth, tileHeight); SetMapPath(mapPath);
	}
	if (ExternalDataCollector::GetInstance()->GetScene() == ExternalDataCollector::Scene3_3)
	{
		LoadTileset_3(tilesetPath, tileWidth, tileHeight); SetMapPath(mapPath);
	}	
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
	ExternalDataCollector::GetInstance()->SetMapWidth(GetWidth());
	grid = Grid::GetInstance();

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
	
		switch (id) {
		case 0: {
			Entity *ground = new Entity();
			ground->SetTag(Entity::Ground);
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
			unit = new Unit(grid, soldier);
		}
				break;
		case 6: {
			Runner *runner = new Runner();
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			runner->SetSpawnBox(box, direction);
			unit = new Unit(grid, runner);
		}
				break;
		case 7: {
			Cannoner *cannoner = new Cannoner();
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			cannoner->SetSpawnBox(box, direction);
			unit = new Unit(grid, cannoner);
		}
				break;
		case 8: {
			Boss *boss = new Boss();
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			boss->SetSpawnBox(box, direction);
			unit = new Unit(grid, boss);
		}
				break;
		case 9: { //SpiritPoints5 
			Item *item9 = new Item(Entity::SpiritPoints5);
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			item9->SetSpawnBox(box, direction);
			unit = new Unit(grid, item9);
		}
				break;
		case 10: { //SpiritPoints10 
			Item *item10 = new Item(Entity::SpiritPoints10);
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			item10->SetSpawnBox(box, direction);
			unit = new Unit(grid, item10);
		}
				 break;
		case 11: { //Scores500 
			Item *item11 = new Item(Entity::Scores500);
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			item11->SetSpawnBox(box, direction);
			unit = new Unit(grid, item11);
		}
				 break;
		case 12: { //Scores1000 
			Item *item12 = new Item(Entity::Scores1000);
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			item12->SetSpawnBox(box, direction);
			unit = new Unit(grid, item12);
		}
				 break;
		case 13: { //TimeFreeze 
			Item *item13 = new Item(Entity::TimeFreeze);
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			item13->SetSpawnBox(box, direction);
			unit = new Unit(grid, item13);
		}
				 break;
		case 14: { //Health 
			Item *item14 = new Item(Entity::Health);
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			item14->SetSpawnBox(box, direction);
			unit = new Unit(grid, item14);
		}
				 break;
		case 15: { //ThrowingStar 
			Item *item15 = new Item(Entity::ThrowingStar);
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			item15->SetSpawnBox(box, direction);
			unit = new Unit(grid, item15);
		}
				 break;
		case 16: { //WindmillStar 
			Item *item16 = new Item(Entity::WindmillStar);
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			item16->SetSpawnBox(box, direction);
			unit = new Unit(grid, item16);
		}
				 break;
		case 17: { //Flames 
			Item *item17 = new Item(Entity::Flames);
			BoxCollider box;
			box.top = posy;
			box.left = posx;
			box.bottom = posy - hei;
			box.right = posx + wid;
			item17->SetSpawnBox(box, direction);
			unit = new Unit(grid, item17);
		}
				 break;
		case 18: { //Wall
			Entity *ground = new Entity();
			ground->SetTag(Entity::Wall);
			ground->SetType(Entity::StaticType);
			ground->SetStatic(true);
			ground->SetPosition(D3DXVECTOR3(posx + wid / 2, posy - hei / 2, 0));
			ground->SetWidth(wid);
			ground->SetHeight(hei);
			grid->staticObject.push_back(ground);
		}
				break;
		case 19: { //ClimbWall
			Entity *ground = new Entity();
			ground->SetTag(Entity::ClimbWall);
			ground->SetType(Entity::StaticType);
			ground->SetStatic(true);
			ground->SetPosition(D3DXVECTOR3(posx + wid / 2, posy - hei / 2, 0));
			ground->SetWidth(wid);
			ground->SetHeight(hei);
			grid->staticObject.push_back(ground);
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

	GameMap::~GameMap() {
		delete mapIDs;
	}

	void GameMap::LoadTileset_1(char * filePath, int tileWidth, int tileHeight) {
		//Parse map tu file 
		Textures::GetInstance()->Add(TEX_STAGE31, filePath, D3DCOLOR_XRGB(255, 0, 255));
		auto texture_1 = Textures::GetInstance()->Get(TEX_STAGE31);
		
		D3DSURFACE_DESC desc;
		texture_1->GetLevelDesc(0, &desc);
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
				LPSPRITE sprite = new Sprite(r, texture_1);
				tileset->Add(i * tileset->GetColumns() + j, sprite);
			}
		}
	}

	void GameMap::LoadTileset_2(char * filePath, int tileWidth, int tileHeight) {
		//Parse map tu file 
		Textures::GetInstance()->Add(TEX_STAGE32, filePath, D3DCOLOR_XRGB(255, 0, 255));
		auto texture_2 = Textures::GetInstance()->Get(TEX_STAGE32);
		D3DSURFACE_DESC desc;
		texture_2->GetLevelDesc(0, &desc);
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
				LPSPRITE sprite = new Sprite(r, texture_2);
				tileset->Add(i * tileset->GetColumns() + j, sprite);
			}
		}
	}

	void GameMap::LoadTileset_3(char * filePath, int tileWidth, int tileHeight) {
		//Parse map tu file 
		Textures::GetInstance()->Add(TEX_STAGE33, filePath, D3DCOLOR_XRGB(255, 0, 255));
		auto texture_3 = Textures::GetInstance()->Get(TEX_STAGE33);
		D3DSURFACE_DESC desc;
		texture_3->GetLevelDesc(0, &desc);
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
				LPSPRITE sprite = new Sprite(r, texture_3);
				tileset->Add(i * tileset->GetColumns() + j, sprite);
			}
		}
	}
