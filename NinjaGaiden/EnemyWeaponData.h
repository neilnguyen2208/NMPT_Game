#pragma once
#pragma once
class EnemyWeapon;
class EnemyWeaponState;

class EnemyWeaponData {
public:
	EnemyWeapon *weapon;
	EnemyWeaponState *state;
	EnemyWeaponData(EnemyWeapon *item) : weapon(item) {}
};