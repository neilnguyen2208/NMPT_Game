#pragma once
#include "Entity.h"
#include <cmath>
#include <limits>


class CollisionDetector {
public:
	CollisionDetector();
	//kiem tra va cham giua 2 hinh chu nhat
	static Entity::CollisionReturn RectAndRect(BoxCollider rect, BoxCollider rect2);
	//kiem tra 2 RECTco collide
	static bool IsCollide(BoxCollider rect1, BoxCollider rect2, D3DXVECTOR2 vel1 = D3DXVECTOR2());

	//neu Rectagle qua to thi va cham co the bi sai
	static Entity::SideCollision GetSideCollision4(BoxCollider e1, Entity::CollisionReturn data);

	//kiem tra vi tri va cham dua vao vung va cham cua 2 vat the
	//static Entity::SideCollision GetSideCollision8(Entity *e1, Entity::CollisionReturn data);
	//
	static float SweptAABB(Entity *ent1, Entity *ent2, Entity::SideCollision &side, double dt = 1/60.0f);
	static float SweptAABB(BoxCollider r1, D3DXVECTOR2 oriVel1, BoxCollider r2, D3DXVECTOR2 oriVel2, Entity::SideCollision &side, double dt = 1 / 60.0f);
	//board-phasing 
	static BoxCollider GetBoardPhasing(BoxCollider r, float vx, float vy);
	//kiem tra 1 diem co nam trong hinh chu nhat hay khong
	static bool PointAndRectangle(float x, float y, BoxCollider rect);

	//hinh chu nhat va hinh tron
	~CollisionDetector();
};