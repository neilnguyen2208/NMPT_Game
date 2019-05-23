#pragma once
class Enemy;
class EnemyState;

class EnemyData {
public:
	EnemyData() {}
	Enemy *enemy;
	EnemyState *state;
};