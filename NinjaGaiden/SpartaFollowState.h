#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"

class SpartaFollowState : public EnemyState {
public:
	SpartaFollowState(EnemyData *data);
	~SpartaFollowState();
	virtual void ResetState();
	virtual void Update(double dt);

};