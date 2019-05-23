#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "BoxCollider.h"

class Entity {

public:
	bool isStatic;
	static int currentID;

	Entity();

	enum SideCollision {
		Left, //0
		Right, //1
		Top, //2
		Bottom, //3
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		NotKnow
	};
	struct CollisionReturn
	{
		bool IsCollided;
		BoxCollider regionCollision;
	};
	enum EntityTag
	{
		Ground,
		Player,
		Sparta,
		Cat,
		Thrower,
		Eagle,
		Soldier,
		SpiritPoints5,
		SpiritPoints10,
		Scores500,
		Scores1000,
		TimeFreeze,
		Health,
		ThrowingStar,
		WindmillStar,
		Flames,
		CamRect,
		None
	};
	enum EntityType {
		StaticType,
		PlayerType,
		EnemyType,
		ItemType,
		NoneType
	};
	enum EntityDirection {
		LeftToRight,
		RightToLeft
	};
	void UpdatePosition(double dt);
	virtual BoxCollider GetRect();
	virtual void SetActive(bool active);
	virtual bool IsActive();
	virtual EntityTag GetTag();
	virtual void SetTag(EntityTag tag);
	virtual EntityType GetType();
	virtual void SetType(EntityType type);
	virtual void SetStatic(bool flag);
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(D3DXVECTOR2 pos);
	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual void AddPosition(D3DXVECTOR3 pos);
	virtual void AddPosition(D3DXVECTOR2 pos);
	virtual void AddPosition(float x, float y);
	virtual D3DXVECTOR3 GetPosition();

	virtual EntityDirection GetMoveDirection();
	virtual void SetMoveDirection(EntityDirection direction);
	virtual void SetWidth(int width);
	virtual float GetWidth();
	virtual void SetHeight(int height);
	virtual float GetHeight();

	virtual D3DXVECTOR2 GetVelocity();
	virtual void SetVelocity(D3DXVECTOR2 vel);

	virtual float GetVx();
	virtual void SetVx(float vx);
	virtual void AddVx(float vx);

	virtual float GetVy();
	virtual void SetVy(float vy);
	virtual void AddVy(float vy);

	virtual void AddVelocity(D3DXVECTOR2 vel);

	virtual int GetID();

	virtual void Update(double dt);
	virtual void Render();

	virtual void OnCollision(Entity *impactor, SideCollision side, float collisionTime);

protected:
	bool isActive;
	int id;
	EntityTag tag;
	EntityType type;
	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void OnSetPosition(D3DXVECTOR3 pos);

	//vi tri tam position x va y
	D3DXVECTOR3 position;

	//phan toc vx, vy
	D3DXVECTOR2 velocity;

	//size cua entity
	float width, height;

	//Update Position
	

	EntityDirection direction;
};