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
		Ground, //Ground
		Wall, //Wall

		Player, //Player

		// 3.1 Enemy
		Sparta,
		Cat,
		Thrower,
		Eagle,
		Soldier,
		
		// 3.1 Enemy weapon
		ThrowerBullet,
		SoldierBullet,

		// 3.2 Enemy
		Runner,
		Cannoner,
		// 3.2 Enemy weapon
		CannonerBullet,

		// 3.3
		Boss,
		BossWeapon,

		//Directtly Process Item
		SpiritPoints5, //6
		SpiritPoints10, //7
		Scores500, //8
		Scores1000, //9
		TimeFreeze, //10
		Health, //11
		ThrowingStar, //12
		WindmillStar, //13
		Flames, //14


		//Skill and Katana Entity (RyuWeaponType) use for Collide
		FlameWheel,
		RedShuriken,
		BlueShuriken,
		Katana,

		//CamRect
		CamRect,
		
		//None
		None
	};
	enum EntityType {
		StaticType,
		PlayerType,
		EnemyType,
		ItemType,
		RyuWeaponType,
		EnemyWeaponType,
		NoneType
	};
	enum EntityAliveState {
		Alive,
		Beaten, 
		Die,
		Remove
	};
	enum EntityDirection {
		LeftToRight,
		RightToLeft
	};
	enum StatusItem {
		AvailableItem,
		UnavailableItem
	};
	virtual BoxCollider GetRect();
	virtual void SetActive(bool active);
	virtual bool IsActive();
	virtual EntityTag GetTag();
	virtual void SetTag(EntityTag tag);
	virtual EntityType GetType();
	virtual void SetType(EntityType type);
	virtual EntityAliveState GetAliveState();
	virtual void SetAliveState(EntityAliveState alivestate);

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

	virtual void MakeInactive();

	virtual void SetStatusItem(StatusItem status);
	virtual StatusItem GetStatusItem();

protected:
	
	bool isActive;
	int id;
	EntityTag tag;
	EntityType type;
	EntityAliveState aliveState;
	//duoc goi khi set position cua Entity, dung cho ke thua
	virtual void OnSetPosition(D3DXVECTOR3 pos);

	//vi tri tam position x va y
	D3DXVECTOR3 position;

	//phan toc vx, vy
	D3DXVECTOR2 velocity;

	//size cua entity
	float width, height;

	EntityDirection direction;
	StatusItem status;

};