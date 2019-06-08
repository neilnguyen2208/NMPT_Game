#pragma once
#include"Entity.h"
#include"Animation.h"
#include"Textures.h"
#include"Camera.h"
class RyuWeapon :public Entity
{
public:

	float offsetScaleX;

	virtual void Update(double dt);
	virtual void Render();

	virtual BoxCollider GetRect();

	virtual void SetActive(bool active);
	virtual bool IsActive();
	virtual void SetRect(BoxCollider box);

	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual void SetMoveDirection(Entity::EntityDirection dir);



	EntityDirection GetMoveDirection();

	virtual void OnCollision(Entity* impactor, SideCollision side, float timeCollision);

	//Get collilder width
	virtual float GetWidth();
	virtual float GetBigWidth();

	//Get collider height;
	virtual float GetHeight();
	virtual float GetBigHeight();
	virtual BoxCollider GetCollider();

	virtual void MakeInactive();



	RyuWeapon();
	~RyuWeapon();

protected:

	BoxCollider collider;
	float collisionTime;
	SideCollision side;
	Animation* m_Animation;

	int ExplodeWidth;
	int ExplodeHeight;

	Camera*camera;

};

