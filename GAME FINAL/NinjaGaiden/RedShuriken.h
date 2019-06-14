#pragma once
#include"Entity.h"
#include"Animation.h"
#include"Textures.h"
#include"Player.h"
#include"RyuWeapon.h"

class RedShuriken :public RyuWeapon
{
public:

	RedShuriken();
	~RedShuriken();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void Render();
	virtual void Update(double dt);
	void SetAccelerate(float x, float y);
	void SetAccelerateX(float x);
	void SetAccelerateY(float y);
	void SetTarget(D3DXVECTOR3 target); //when RedShuriken's velocity = 0 => target = player->GetPosition();
	
private:

	D3DXVECTOR3 target; // target to RedShuken follow with
	float accelerateX, accelerateY;

};

