#include "PlayScene.h"
#include"SceneManager.h"
#include"ExternalDataCollector.h"

PlayScene::PlayScene() {
	//LoadResources	
	ExternalDataCollector::GetInstance()->SetScene(ExternalDataCollector::Scene3_3);
	map = new GameMap((char*)"Resources/Scene/Scene3_3 TileSet.png", (char*)"Resources/Scene/Scene3_3 Output.txt", 32, 32);
	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();
	/*map = new GameMap((char*)"Resources/TilesDebug.png", (char*)"Resources/OutputDebug.txt", 32, 32);
	ExternalDataCollector::GetInstance()->SetScene(ExternalDataCollector::Scene3_1);*/
	//map is not a Singleton
	map->SetCamera(Camera::GetInstance());
	Camera::GetInstance()->SetPosition(D3DXVECTOR3(width / 2, height / 2, 0));
	Player::GetInstance()->SetPosition(32, 40 + Player::GetInstance()->GetBigHeight() / 2.0f);
	unit = new Unit(Grid::GetInstance(BoxCollider(map->GetHeight(),0,0, map->GetWidth())), Player::GetInstance());
	sb = new Scoreboard();
	score = new Score();
}
PlayScene::~PlayScene() {

}

void PlayScene::Render() {
	map->Draw();
	Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->RenderActive(); 	
	sb->DrawTextTop(Graphic::GetInstance()->Getdirect3DDevice(), score->GetScore(), score->GetFate(), score->GetTime(), score->GetScene(), score->GetNinjaBlood(), score->GetBossBlood(), score->GetPower(), score->GetSkill());
}                                                                           

void PlayScene::ProcessInput() {
	KeyBoard *input = KeyBoard::GetInstance();
	Player::GetInstance()->HandleInput();
}

void PlayScene::Update(double dt) {
	ProcessInput();
	CheckCollision(dt);

	Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->UpdateActive(dt); //Update nhung unit nao dang active
	Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->UpdateActivatingCells(dt); //ham nay them vao de cap nhat cac cell duoc activated, chua kiem tra duoc do chua co va cham voi ground	
	Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->CheckActivatedObjects();
	Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->ClearAllWeapon();

	D3DXVECTOR3 playerPos = Player::GetInstance()->GetPosition();
	Camera::GetInstance()->FollowPlayer(playerPos.x, playerPos.y);
	CheckCamera();

	//Update for Scorebar
	score->SetSkill(Player::GetInstance()->skillnumer);
	score->SetPower(Player::GetInstance()->power);
	score->SetScore(Player::GetInstance()->score);
	score->SetNinjaBlood(Player::GetInstance()->blood);
	score->SetFate(Player::GetInstance()->fate);

	//Update for ExternalDataCollector
	ExternalDataCollector::GetInstance()->SetLife(Player::GetInstance()->fate);

	if (ExternalDataCollector::GetInstance()->GetHitPoint()==0||Player::GetInstance()->GetPosition().y<0)
	{
		ExternalDataCollector::GetInstance()->SetLife(ExternalDataCollector::GetInstance()->GetLife() - 1);
		if (ExternalDataCollector::GetInstance()->GetLife() == -1)
		{
			ExternalDataCollector::GetInstance()->SetLost(true);
		}
		ExternalDataCollector::GetInstance()->SetPlayerDead(true);
		Reset();
	}
	else
	{
		if (ExternalDataCollector::GetInstance()->GetScene() != ExternalDataCollector::SceneList::Scene3_3)
		{
			if (Player::GetInstance()->GetPosition().x >= map->GetWidth() - 100)
			{
				ExternalDataCollector::GetInstance()->SetCrossOverMap(true);
				Reset();
			}
		}
		else
		{
			//if (ExternalDataCollector::GetInstance()->GetBossHitPoint() <= 0)
			//{
				//ExternalDataCollector::GetInstance()->SetCrossOverMap(true);
				//Reset();
			//}
		}
	}
}

void PlayScene::CheckCollision(double dt) {
	vector<Entity*> staticObjects = Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->GetStaticObjects(); //stacic object from 
	auto side = Entity::NotKnow;
	BoxCollider exPlayer = BoxCollider(Player::GetInstance()->GetPosition(), Player::GetInstance()->GetWidth(), Player::GetInstance()->GetBigHeight());
	bool isOnGround = false;

	//Player::GetInstance() with ground
	for (size_t i = 0; i < staticObjects.size(); i++) {
		auto impactorRect = staticObjects[i]->GetRect();
		float groundTime = CollisionDetector::SweptAABB(exPlayer, Player::GetInstance()->GetVelocity(), impactorRect, D3DXVECTOR2(0, 0), side, dt);
		
		if (groundTime != 2) // if collision
		{
			if (side == Entity::Bottom && abs(exPlayer.bottom - impactorRect.top) <= PLAYER_OFFSET_GROUND) {
				if (Player::GetInstance()->GetVelocity().y > 0)
					continue;
				if (Player::GetInstance()->GetVelocity().y < 0)
					Player::GetInstance()->OnCollision(staticObjects[i], side, groundTime);
				isOnGround = true;
			}
			else
			{
				if (ExternalDataCollector::GetInstance()->GetScene() == ExternalDataCollector::Scene3_2 || ExternalDataCollector::GetInstance()->GetScene() == ExternalDataCollector::Scene3_3)
				{
					if (side == Entity::Right && abs(exPlayer.right - impactorRect.left) <= PLAYER_OFFSET_GROUND) {
						Player::GetInstance()->OnCollision(staticObjects[i], side, groundTime);
					}
					else if (side == Entity::Left && abs(exPlayer.left - impactorRect.right) <= PLAYER_OFFSET_GROUND) {
						Player::GetInstance()->OnCollision(staticObjects[i], side, groundTime);
					}
				}
			}
		}
	}

	if (!isOnGround && !Player::GetInstance()->onAir) {
		Player::GetInstance()->OnFalling();
	}

	float cellWidth = Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->GetCellWidth();
	float cellHeight = Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->GetCellHeight();
	int iMax = Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->GetRows() - 1;
	int jMax = Camera::GetInstance()->GetRect().right / cellWidth;
	int jMin = Camera::GetInstance()->GetRect().left / cellWidth;

	//gridcells activate with ground
	for (size_t i = 0; i <= iMax; i++)
	{
		for (size_t j = jMin; j <= jMax; j++) {
			if (Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->GetGridCells(i, j) == NULL)
				continue;			
			Unit*tmpcells_tonext = Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->GetGridCells(i, j);
			while (tmpcells_tonext != NULL)
			{
				if(tmpcells_tonext->GetEntity()!=NULL)
				if (tmpcells_tonext->GetEntity()->IsActive() == true && tmpcells_tonext->GetEntity()->GetTag() != Entity::Player&&tmpcells_tonext->GetEntity()->GetType()!=Entity::EnemyWeaponType&&tmpcells_tonext->GetEntity()->GetType()!=Entity::RyuWeaponType)
				{
					bool onGround = false;
					for (size_t k = 0; k < staticObjects.size(); k++) {
						if (staticObjects[k]->GetTag() != Entity::Ground) continue;
						float collisionTime = CollisionDetector::SweptAABB(tmpcells_tonext->GetEntity(), staticObjects[k], side, dt);
						if (collisionTime == 2)
							continue;

						if (tmpcells_tonext->GetEntity()->GetTag() != Entity::EntityTag::Runner&&tmpcells_tonext->GetEntity()->GetTag() != Entity::EntityTag::Boss)
							tmpcells_tonext->GetEntity()->OnCollision(staticObjects[k], side, collisionTime);
						if (side == Entity::Bottom)
							onGround = true;
					}
					if (!onGround&&tmpcells_tonext->GetEntity()->GetTag()!=Entity::SoldierBullet&&tmpcells_tonext->GetEntity()->GetType()!=Entity::RyuWeaponType&&tmpcells_tonext->GetEntity()->GetType() != Entity::ItemType&&tmpcells_tonext->GetEntity()->GetTag()!=Entity::CannonerBullet){
						tmpcells_tonext->GetEntity()->AddVy(-CAT_GRAVITY);
					}
				}
				tmpcells_tonext = tmpcells_tonext->GetNextUnit();
			}
		}
	}

	if (Player::GetInstance()->GetSkill() != Player::NoneSkill)
	{
		Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->HandleGridCollisionRyuWeaponEnemy(dt);
	}
	Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->HandleGridCollisionPlayerEnemy(dt);
}

void PlayScene::CheckCamera() {
	D3DXVECTOR3 camPos = Camera::GetInstance()->GetPosition();
	float halfWidth = (float)Camera::GetInstance()->GetWidth() / 2;
	float halfHeight = (float)Camera::GetInstance()->GetHeight() / 2;
	auto worldWidth = map->GetWidth();
	auto worldHeight = map->GetHeight();
	if (camPos.x - halfWidth < 0)
		camPos.x = halfWidth;
	if (camPos.x + halfWidth > worldWidth)
		camPos.x = worldWidth - halfWidth;
	Camera::GetInstance()->SetPosition(camPos);
}

void PlayScene::Reset() {	
	Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight()))->Reset();
	delete map;
	map = NULL;
	
	if (ExternalDataCollector::GetInstance()->GetLost())
	{
		ExternalDataCollector::GetInstance()->SetScene(ExternalDataCollector::Scene3_1);		
		map = new GameMap((char*)"Resources/Scene/Scene3_1 TileSet.png", (char*)"Resources/Scene/Scene3_1 Output.txt", 32, 32);
	}
	else
		if (ExternalDataCollector::GetInstance()->GetPlayerDead())
		{
			if (ExternalDataCollector::GetInstance()->GetScene() == ExternalDataCollector::Scene3_1)
			{
				ExternalDataCollector::GetInstance()->SetScene(ExternalDataCollector::Scene3_1);			
				map = new GameMap((char*)"Resources/Scene/Scene3_1 TileSet.png", (char*)"Resources/Scene/Scene3_1 Output.txt", 32, 32);
			}
			else if (ExternalDataCollector::GetInstance()->GetScene() == ExternalDataCollector::Scene3_2)
			{
				ExternalDataCollector::GetInstance()->SetScene(ExternalDataCollector::Scene3_2);			
				map = new GameMap((char*)"Resources/Scene/Scene3_2 TileSet.png", (char*)"Resources/Scene/Scene3_2 Output.txt", 32, 32);
			} else
			if (ExternalDataCollector::GetInstance()->GetScene() == ExternalDataCollector::Scene3_3)
			{
				ExternalDataCollector::GetInstance()->SetScene(ExternalDataCollector::Scene3_3);			
				map = new GameMap((char*)"Resources/Scene/Scene3_3 TileSet.png", (char*)"Resources/Scene/Scene3_3 Output.txt", 32, 32);
			}
		}
		else 
			if (ExternalDataCollector::GetInstance()->GetCrossOverMap())
			{
				if (ExternalDataCollector::GetInstance()->GetScene() == ExternalDataCollector::Scene3_1)
				{
					ExternalDataCollector::GetInstance()->SetScene(ExternalDataCollector::Scene3_2);			
					map = new GameMap((char*)"Resources/Scene/Scene3_2 TileSet.png", (char*)"Resources/Scene/Scene3_2 Output.txt", 32, 32);
				}
				else if (ExternalDataCollector::GetInstance()->GetScene() == ExternalDataCollector::Scene3_2)
				{
					ExternalDataCollector::GetInstance()->SetScene(ExternalDataCollector::Scene3_3);					
					map = new GameMap((char*)"Resources/Scene/Scene3_3 TileSet.png", (char*)"Resources/Scene/Scene3_3 Output.txt", 32, 32);
				}
				else if (ExternalDataCollector::GetInstance()->GetScene() == ExternalDataCollector::Scene3_3)
				{
					//Win;
				}
			}

	//chet thi reset, khong chet thi thoi
	if (ExternalDataCollector::GetInstance()->GetPlayerDead()||ExternalDataCollector::GetInstance()->GetLost())
	{
		Player::GetInstance()->Reset();	
		if (ExternalDataCollector::GetInstance()->GetLost())
		{
			ExternalDataCollector::GetInstance()->SetLife(2);
		}
		Player::GetInstance()->fate = ExternalDataCollector::GetInstance()->GetLife();
		ExternalDataCollector::GetInstance()->SetPlayerDead(false);
		ExternalDataCollector::GetInstance()->SetLost(false);
	}
	if (ExternalDataCollector::GetInstance()->GetCrossOverMap())
	{
		ExternalDataCollector::GetInstance()->SetCrossOverMap(false);
	}

	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();

	map->SetCamera(Camera::GetInstance());
	Camera::GetInstance()->SetPosition(D3DXVECTOR3(width / 2, height / 2, 0));
	if (ExternalDataCollector::GetInstance()->GetScene() != ExternalDataCollector::Scene3_3)
		Player::GetInstance()->SetPosition(32, 40 + Player::GetInstance()->GetBigHeight() / 2.0f);
	else
		Player::GetInstance()->SetPosition(50, 80 + Player::GetInstance()->GetBigHeight() / 2.0f);

	unit = new Unit(Grid::GetInstance(BoxCollider(map->GetWidth(),0,0,map->GetHeight())), Player::GetInstance());
}


