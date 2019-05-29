#include "PlayScene.h"
#include "Debug.h"

PlayScene::PlayScene() {
	//LoadResources
	map = new GameMap((char*)"Resources/TilesDebug.png", (char*)"Resources/OutputDebug.txt", 32, 32);
	int width = Graphic::GetInstance()->GetBackBufferWidth();
	int height = Graphic::GetInstance()->GetBackBufferHeight();

	//initiate camera for map
	camera = new Camera(width, height);
	map->SetCamera(camera); //set camera cho map de chay map
	camera->SetPosition(D3DXVECTOR3(width / 2, height / 2, 0));//camera ban dau co vi tri giua man hinh

	//initiate grid for map
	grid = map->GetGrid(); //grid cho playscene = grid tao boi map (muon tao grid phai thong qua map)
	grid->SetCamera(camera); //lay camera dua cho grid de tim cac cell co the active

	//initiate player for map
	player = new Player();
	player->SetPosition(32, 40 + player->GetBigHeight() / 2.0f);
	unit = map->GetUnit();
	unit = new Unit(grid, player);//them player(mot unit) vao grid, cac unit khac duoc them vao tu class gameMap
	
	//Set player for Grid to get Direction
	grid->SetPlayer(player);
}

PlayScene::~PlayScene() {

}

void PlayScene::Render() {
	map->Draw();
	grid->RenderActive(); //
	
}

void PlayScene::ProcessInput() {
	KeyBoard *input = KeyBoard::GetInstance();
	player->HandleInput();
}

void PlayScene::Update(double dt) {
	ProcessInput();
	CheckCollision(dt);

	grid->UpdateActive(dt); //Update nhung unit nao dang active
	grid->UpdateActivatingCells(dt); //ham nay them vao de cap nhat cac cell duoc activated, chua kiem tra duoc do chua co va cham voi ground	
	grid->CheckActivatedObjects();
		
	D3DXVECTOR3 playerPos = player->GetPosition();
	camera->FollowPlayer(playerPos.x, playerPos.y);
	CheckCamera();
}

void PlayScene::CheckCollision(double dt) {

	vector<Entity*> staticObjects = grid->GetStaticObjects(); //stacic object from 

	float cellWidth = grid->GetCellWidth();
	float cellHeight = grid->GetCellHeight();
	int rows = grid->GetRows();
	int columns = grid->GetColumns();

	auto side = Entity::NotKnow;

	BoxCollider exPlayer = BoxCollider(player->GetPosition(), player->GetWidth(), player->GetBigHeight());
	bool isOnGround = false;

	//player with ground
	for (size_t i = 0; i < staticObjects.size(); i++) {

		auto impactorRect = staticObjects[i]->GetRect();
		float groundTime = CollisionDetector::SweptAABB(exPlayer, player->GetVelocity(), impactorRect, D3DXVECTOR2(0, 0), side, dt);

		if (groundTime != 2) // if collision
		{
			if (side == Entity::Bottom && abs(exPlayer.bottom - impactorRect.top) <= PLAYER_OFFSET_GROUND) {

				if (player->GetVelocity().y > 0)
					continue;

				if (player->GetVelocity().y < 0)
					player->OnCollision(staticObjects[i], side, groundTime);

				isOnGround = true;
			}
		}
	}

	if (!isOnGround && !player->onAir) {
		player->OnFalling();
	}

	//gridcells activate with ground
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < columns; j++) {

			if (grid->GetGridCells(i, j) == NULL)
				continue;

			Unit*tmpcells_tonext = grid->GetGridCells(i, j);
			Unit*tmpcells_toprev = grid->GetGridCells(i, j)->GetPrevUnit();

			while (tmpcells_tonext != NULL)
			{
				if (tmpcells_tonext->GetEntity()->IsActive() == true && tmpcells_tonext->GetEntity()->GetTag() != Entity::Player)
				{
					bool onGround = false;
					for (size_t k = 0; k < staticObjects.size(); k++) {

						float collisionTime = CollisionDetector::SweptAABB(tmpcells_tonext->GetEntity(), staticObjects[k], side, dt);

						if (collisionTime == 2)
							continue;

						tmpcells_tonext->GetEntity()->OnCollision(staticObjects[k], side, collisionTime);
						if (side == Entity::Bottom)
							onGround = true;
					}
					if (!onGround/*&&grid->GetGridCells(i,j)->GetEntity()->GetTag()!=Entity::Eagle*/) {
						tmpcells_tonext->GetEntity()->AddVy(-CAT_GRAVITY);
					}
				}
				tmpcells_tonext = tmpcells_tonext->GetNextUnit();
			}

			while (tmpcells_toprev != NULL)
			{
				if (tmpcells_toprev->GetEntity()->IsActive() == true && tmpcells_toprev->GetEntity()->GetTag() != Entity::Player)
				{
					bool onGround = false;
					for (size_t k = 0; k < staticObjects.size(); k++) {

						float collisionTime = CollisionDetector::SweptAABB(tmpcells_toprev->GetEntity(), staticObjects[k], side, dt);

						if (collisionTime == 2)
							continue;

						tmpcells_toprev->GetEntity()->OnCollision(staticObjects[k], side, collisionTime);
						if (side == Entity::Bottom)
							onGround = true;
					}
					if (!onGround/*&&grid->GetGridCells(i,j)->GetEntity()->GetTag()!=Entity::Eagle*/) {
						tmpcells_toprev->GetEntity()->AddVy(-CAT_GRAVITY);
					}
				}
				tmpcells_toprev = tmpcells_toprev->GetPrevUnit();
			}
		}
	}
	
	grid->HandleGridCollision(dt);
}

void PlayScene::CheckCamera() {
	D3DXVECTOR3 camPos = camera->GetPosition();
	float halfWidth = (float)camera->GetWidth() / 2;
	float halfHeight = (float)camera->GetHeight() / 2;
	auto worldWidth = map->GetWidth();
	auto worldHeight = map->GetHeight();
	if (camPos.x - halfWidth < 0)
		camPos.x = halfWidth;
	if (camPos.x + halfWidth > worldWidth)
		camPos.x = worldWidth - halfWidth;
	camera->SetPosition(camPos);
}

void PlayScene::Reset() {
}
