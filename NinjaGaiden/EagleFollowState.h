#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"

class EagleFollowState : public EnemyState {
public:
	EagleFollowState(EnemyData *data);
	~EagleFollowState();
	virtual void ResetState();
	virtual void Update(double dt);
};