#pragma once
#include"Entity.h"
#include"Animation.h"
#include"Textures.h"
#include"Player.h"
#include"RyuWeapon.h"

class BlueShuriken :public RyuWeapon
{
public:

	BlueShuriken();
	~BlueShuriken();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void Render();
	virtual void Update(double dt);

};

