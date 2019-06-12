#pragma once
#include "Entity.h"
#include "PlayerData.h"
#include "KeyBoard.h"
#include "PlayerState.h"

class Player : public Entity {
public:
	static Player *GetInstance();
	Player();
	~Player();
	virtual void Update(double dt);
	virtual void Render();
	void SetState(PlayerState::State name, int dummy = -1);
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	void AddItem(Entity::EntityTag tag);
	BoxCollider GetRect();
	BoxCollider GetBigBound();
	PlayerState::State GetState();	
	virtual int GetBigWidth();
	virtual int GetBigHeight();
	virtual float GetWidth();
	virtual float GetHeight();
	virtual void OnFalling();
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual BoxCollider GetCollider();

	void HandleInput();

	bool onAir;
	bool isHurting;
	bool isRenderLastFrame;
	double HurtingTime = 0;
	bool isHurtingAnimation = false;
	int timeHurtingAnimation = 0;

	//Cac item khac xu ky ngay khi nhat duoc
	enum Skill {
		BlueShurikenSkill,
		RedShurikenSkill,
		FlameWheelSkill,
		NoneSkill
	};
	virtual void SetSkill(Skill skill);
	virtual Skill GetSkill();
	int skillnumer;

	virtual void AddScore(Entity::EntityTag tag);
	virtual void AddBlood(Entity::EntityTag tag);

	int power; //Luu qua man nho, khong luu qua man lon
	int blood; // Luu qua man nho, khong luu qua man lon
	int score; // Luu qua man
	int fate; // Luu qua man

	int timeFreeze;
	bool useitemtimeFreeze;
	void TimeFreezeSkill(bool skill);
	void checkTimeFreezeSkill();

	void Reset();

protected:
	static Player *instance;
	PlayerData *playerData;
	PlayerState
		*idleState,
		*runningState,
		*slashState,
		*crouchState,
		*jumpState,
		*crouchSlashState,
		*climbState,
		*useSkillState,
		*beatenState;
	PlayerState::State currentState;
	BoxCollider collider;
	float collisionTime;
	SideCollision side;
	Skill skill;
};