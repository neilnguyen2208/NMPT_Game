#include "CollisionDetector.h"

CollisionDetector::CollisionDetector() {

}

Entity::CollisionReturn CollisionDetector::RectAndRect(BoxCollider rect, BoxCollider rect2) {
	Entity::CollisionReturn result;

	result.IsCollided = true;

	BoxCollider bound;
	bound.top = rect.top < rect2.top ? rect.top : rect2.top;
	bound.left = rect.left > rect2.left ? rect.left : rect2.left;
	bound.right = rect.right < rect2.right ? rect.right : rect2.right;
	bound.bottom = rect.bottom > rect2.bottom ? rect.bottom : rect2.bottom;

	result.regionCollision = bound;
	return result;
}

bool CollisionDetector::IsCollide(BoxCollider rect1, BoxCollider rect2, D3DXVECTOR2 vel1) {
	if (vel1 != D3DXVECTOR2())
		rect1.Plus(vel1);
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top < rect2.bottom || rect1.bottom > rect2.top)
		return false;
	return true;
}

Entity::SideCollision CollisionDetector::GetSideCollision4(BoxCollider e1, Entity::CollisionReturn data) {

	float e1Width = e1.GetWidth();
	float e1Height = e1.GetHeight();

	Entity::SideCollision result;

	auto pos1 = e1.GetCenter();
	auto pos2 = data.regionCollision.GetCenter();
	//cos = ke / huyen
	auto cornerAngle = (e1Width / 2) / sqrt(pow(e1Width / 2, 2) + pow(e1Height / 2, 2));

	D3DXVECTOR2 direct = D3DXVECTOR2(pos2.x - pos1.x, pos2.y - pos1.y);
	D3DXVec2Normalize(&direct, &direct);

	if (direct.y > 0) {
		if (direct.x <= cornerAngle && direct.x >= -cornerAngle)
			result = Entity::Top;
		else if (direct.x <= 1.1f && direct.x > cornerAngle)
			result = Entity::Right;
		else if (direct.x >= -1.1f && direct.x < -cornerAngle)
			result = Entity::Left;
	}
	else {
		if (direct.x <= 1.1f && direct.x > cornerAngle)
			result = Entity::Right;
		else if (direct.x <= cornerAngle && direct.x >= -cornerAngle)
			result = Entity::Bottom;
		else if (direct.x >= -1.1f && direct.x < -cornerAngle)
			result = Entity::Left;
	}
	return result;
}

float CollisionDetector::SweptAABB(Entity * ent1, Entity * ent2, Entity::SideCollision &side, double dt) {
	BoxCollider r1 = ent1->GetRect();
	if (r1.GetWidth() == 0)
		r1 = r1;
	BoxCollider r2 = ent2->GetRect();

	D3DXVECTOR2 vel2 = ent2->GetVelocity() * dt;

	auto vel = ent1->GetVelocity() * dt;
	BoxCollider board = GetBoardPhasing(r1, vel.x - vel2.x, vel.y - vel2.y);

	auto deltaVX = vel.x - vel2.x;
	auto deltaVY = vel.y - vel2.y;

	auto deltaVel = vel - vel2;

	if (IsCollide(r1, r2)) {
		auto pos1 = r1.GetCenter();
		auto pos2 = r2.GetCenter();
		side = GetSideCollision4(r1, RectAndRect(r1, r2));
		return 0;
	}

	if (!IsCollide(board, r2))
		return 2;

	float dxEntry = 0, dxExit = 0;
	float dyEntry = 0, dyExit = 0;

	//get min distance of 2 coordinate x and y axis
	if (deltaVel.x > 0) {
		dxEntry = r2.left - r1.right;
		dxExit = r2.right - r1.left;
	}
	else {
		dxEntry = r2.right - r1.left;
		dxExit = r2.left - r1.right;
	}
	if (deltaVel.y > 0) {
		dyEntry = r2.top - r1.bottom;
		dyExit = r2.bottom - r1.top;
	}
	else {
		dyEntry = r2.bottom - r1.top;
		dyExit = r2.top - r1.bottom;
	}

	float txEntry = 0, txExit = 0;
	float tyEntry = 0, tyExit = 0;

	//get time to meet or break up each other in x and y axis
	if (deltaVel.x == 0) {
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else {
		txEntry = dxEntry / deltaVel.x;
		txExit = dxExit / deltaVel.x;
	}
	if (deltaVel.y == 0) {
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else {
		tyEntry = dyEntry / deltaVel.y;
		tyExit = dyExit / deltaVel.y;
	}
	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1 || tyEntry > 1)
		return 2;
	if (txEntry > tyEntry) {
		if (dxEntry < 0.0f)
			side = Entity::Left;
		else
			side = Entity::Right;
	}
	else {
		if (dyEntry < 0.0f)
			side = Entity::Bottom;
		else
			side = Entity::Top;
	}
	return entryTime;
}

float CollisionDetector::SweptAABB(BoxCollider r1, D3DXVECTOR2 oriVel1, BoxCollider r2, D3DXVECTOR2 oriVel2, Entity::SideCollision & side, double dt) {

	if (r2.bottom + oriVel2.y * dt == r1.top)
		r1 = r1;

	//-------------------------------DEBUG-------------------------
	//if (r2.bottom - r1.top < abs(oriVel2.y * dt) && oriVel2.y * dt < 0)
	//	r2 = r2;

	auto vel = oriVel1 * dt;
	auto vel2 = oriVel2 * dt;
	BoxCollider board = GetBoardPhasing(r1, vel.x - vel2.x, vel.y - vel2.y);

	auto deltaVX = vel.x - vel2.x;
	auto deltaVY = vel.y - vel2.y;

	auto deltaVel = vel - vel2;

	if (IsCollide(r1, r2)) {
		auto pos1 = r1.GetCenter();
		auto pos2 = r2.GetCenter();
		side = GetSideCollision4(r1, RectAndRect(r1, r2));
		return 0;
	}

	if (!IsCollide(board, r2))
		return 2;

	float dxEntry = 0, dxExit = 0;
	float dyEntry = 0, dyExit = 0;

	//get min distance of 2 coordinate x and y axis
	if (deltaVel.x > 0) {
		dxEntry = r2.left - r1.right;
		dxExit = r2.right - r1.left;
	}
	else {
		dxEntry = r2.right - r1.left;
		dxExit = r2.left - r1.right;
	}
	if (deltaVel.y > 0) {
		dyEntry = r2.bottom - r1.top;
		dyExit = r2.top - r1.bottom;
	}
	else {
		dyEntry = r2.top - r1.bottom;
		dyExit = r2.bottom - r1.top;
	}

	float txEntry = 0, txExit = 0;
	float tyEntry = 0, tyExit = 0;

	//get time to meet or break up each other in x and y axis
	if (deltaVel.x == 0) {
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else {
		txEntry = dxEntry / deltaVel.x;
		txExit = dxExit / deltaVel.x;
	}
	if (deltaVel.y == 0) {
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else {
		tyEntry = dyEntry / deltaVel.y;
		tyExit = dyExit / deltaVel.y;
	}
	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(txExit, tyExit);

	if (entryTime > exitTime || (txEntry < 0.0f && tyEntry < 0.0f) || txEntry > 1 || tyEntry > 1)
		return 2; // khong va cham
	if (txEntry > tyEntry) {
		if (dxEntry < 0.0f)
			side = Entity::Left;
		else
			side = Entity::Right;
	}
	else {
		if (dyEntry < 0.0f)
			side = Entity::Bottom;
		else
			side = Entity::Top;
	}
	return entryTime;
}

BoxCollider CollisionDetector::GetBoardPhasing(BoxCollider r, float vx, float vy) {
	BoxCollider board = r;
	if (vx > 0)
		board.right += vx;
	else
		board.left += vx;
	if (vy > 0)
		board.top += vy;
	else
		board.bottom += vy;

	return board;
}

bool CollisionDetector::PointAndRectangle(float x, float y, BoxCollider rect) {
	if (x < rect.left || x > rect.right || y < rect.top || y > rect.bottom)
		return false;
	return true;
}

CollisionDetector::~CollisionDetector() {
}
