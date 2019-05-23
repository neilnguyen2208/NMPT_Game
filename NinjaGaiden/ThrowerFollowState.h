#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"

class ThrowerFollowState : public EnemyState {
public:
	ThrowerFollowState(EnemyData *data);
	~ThrowerFollowState();
	virtual void ResetState();
	virtual void Update(double dt);
};