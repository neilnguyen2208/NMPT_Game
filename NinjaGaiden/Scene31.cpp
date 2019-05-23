//#include "Stage31.h"
//
//Stage31::Stage31() {
//	//LoadResources
//	map = new GameMap((char*)"Resources/map31TileSet.png", (char*)"Resources/map31.txt", 32, 32);
//
//	int width = Graphics::GetInstance()->GetBackBufferWidth();
//	int height = Graphics::GetInstance()->GetBackBufferHeight();
//	camera = new Camera(width, height);
//	map->SetCamera(camera);
//	camera->SetPosition(D3DXVECTOR3(width / 2, height / 2, 0));
//
//	player = new Player();
//	player->SetPosition((float)player->GetWidth() / 2, (float)player->GetHeight() / 2 + 30);
//}
//
//Stage31::~Stage31() {
//
//}
//
//void Stage31::Render() {
//	map->Draw();
//	player->Render();
//}
//
//void Stage31::ProcessInput() {
//	player->HandleInput();
//}
//
//void Stage31::Update(double dt) {
//	//Xu ly input
//	ProcessInput();
//	//Kiem tra va cham
//	CheckCollision(dt);
//	//---UPDATE---
//
//	player->Update(dt);
//	//---Camera follow player
//	D3DXVECTOR3 playerPos = player->GetPosition();
//	camera->FollowPlayer(playerPos.x, playerPos.y);
//	CheckCamera();
//}
//
//void Stage31::CheckCollision(double dt) {
//
//	vector<Entity*> collideObjects;
//	map->GetGrid()->GetEntityWithRect(collideObjects, camera->GetRect());
//	Entity::SideCollision side = Entity::NotKnow;
//
//	for (size_t i = 0; i < collideObjects.size(); i++) {
//		for (size_t j = i + 1; j < collideObjects.size(); j++) {
//
//			float collisionTime = CollisionDetector::SweptAABB(collideObjects[i], collideObjects[j], side, dt);
//			if (collisionTime == 1)
//				continue;
//			collideObjects[i]->OnCollision(collideObjects[j], side, collisionTime);
//			collisionTime = CollisionDetector::SweptAABB(collideObjects[j], collideObjects[i], side, dt);
//			collideObjects[j]->OnCollision(collideObjects[i], side, collisionTime);
//		}
//	}
//
//	BoxCollider exPlayer = BoxCollider(player->GetPosition(), player->GetWidth(), player->GetBigHeight());
//
//	for (size_t i = 0; i < collideObjects.size(); i++) {
//
//		if (collideObjects[i]->isStatic && player->onAir) {
//			float groundTime = CollisionDetector::SweptAABB(collideObjects[i]->GetRect(), D3DXVECTOR2(0, 0), exPlayer, player->GetVelocity(), side, dt);
//			if (groundTime != 1 && side == Entity::Bottom) {
//				player->OnCollision(collideObjects[i], side);
//				continue;
//			}
//		}
//
//		float collisionTime = CollisionDetector::SweptAABB(player, collideObjects[i], side, dt);
//		if (collisionTime == 1)
//			continue;
//		player->OnCollision(collideObjects[i], side);
//		collisionTime = CollisionDetector::SweptAABB(collideObjects[i], player, side, dt);
//		collideObjects[i]->OnCollision(player, side, collisionTime);
//	}
//}
//
//void Stage31::CheckCamera() {
//	D3DXVECTOR3 camPos = camera->GetPosition();
//	float halfWidth = (float)camera->GetWidth() / 2;
//	float halfHeight = (float)camera->GetHeight() / 2;
//	auto worldWidth = map->GetWidth();
//	auto worldHeight = map->GetHeight();
//	if (camPos.x - halfWidth < 0)
//		camPos.x = halfWidth;
//	if (camPos.x + halfWidth > worldWidth)
//		camPos.x = worldWidth - halfWidth;
//	camera->SetPosition(camPos);
//}
//
//void Stage31::Reset() {
//}
