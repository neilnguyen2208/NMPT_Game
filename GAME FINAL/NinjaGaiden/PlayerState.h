#pragma once
#include "Entity.h"
#include "Animation.h"
#include "PlayerData.h"
#include "KeyBoard.h"
#include "CollisionDetector.h"
#include "GameConfig.h"

class PlayerState {
public:
	enum State{
		Idle,
		Running,
		Slash,
		Crouch,
		CrouchSlash,
		Jumping,
		Falling,
		Climb,
		UseSkill,
		Beaten,
		Die
	};
	~PlayerState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void HandleInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual State GetState();
	virtual int GetAnimationHeight();
	virtual int GetAnimationWidth();
	virtual void ResetState(int dummy);
	Animation *GetAnimation() { return m_Animation; }
protected:
	Animation *m_Animation;
	PlayerState(PlayerData *data);
	PlayerState();
	PlayerData *playerData;
};
