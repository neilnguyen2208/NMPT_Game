#include "ExternalDataCollector.h"
ExternalDataCollector* ExternalDataCollector::instance = NULL;

ExternalDataCollector::ExternalDataCollector()
{
	PlayerHitPoint = 16;
	isPlayerDead = false;
	isCrossOverMap = false;
	CurScene = Scene3_1;
	Life = 2;
	Score = 0;
	Mana = 0;
	CurSkill = 0;
	isLost = false;
	haveClimb = false;
	BossHitPoint = 16;
	isBossHaveHurt = false;
	BossHurtTime = 0.0f;
	mapWidth = 2048;

}

void ExternalDataCollector::SetScene(SceneList scene)
{
	CurScene = scene;
}

ExternalDataCollector::SceneList ExternalDataCollector::GetScene()
{
	return CurScene;
}

void ExternalDataCollector::SetPlayerDead(bool isDead)
{
	isPlayerDead = isDead;
}

void ExternalDataCollector::SetCrossOverMap(bool isCros)
{
	isCrossOverMap = isCros;
}

void ExternalDataCollector::SetScore(long score)
{
	Score = score;
}

void ExternalDataCollector::SetMana(int mana)
{
	Mana = mana;
}

void ExternalDataCollector::SetHitPoint(int blood)
{
	PlayerHitPoint = blood;
}

void ExternalDataCollector::SetLife(int life)
{
	Life = life;
}

void ExternalDataCollector::SetSkill(int curSkill)
{
	CurSkill = curSkill;
}

void ExternalDataCollector::SetLost(bool islost)
{
	isLost = islost;
}

void ExternalDataCollector::SetClimb(bool haveclimb)
{
	this->haveClimb = haveclimb;
}

bool ExternalDataCollector::GetClimb()
{
	return haveClimb;
}

long ExternalDataCollector::GetScore()
{
	return Score;
}

int ExternalDataCollector::GetMana()
{
	return Mana;
}

int ExternalDataCollector::GetHitPoint()
{
	return PlayerHitPoint;
}

int ExternalDataCollector::GetLife()
{
	return Life;
}

int ExternalDataCollector::GetSkill()
{
	return CurSkill;
}

bool ExternalDataCollector::GetLost()
{
	return isLost;
}

bool ExternalDataCollector::GetPlayerDead()
{
	return isPlayerDead;
}

bool ExternalDataCollector::GetCrossOverMap()
{
	return isCrossOverMap;
}

void ExternalDataCollector::SetBossHitPoint(int hitpoint)
{
	BossHitPoint = hitpoint;
}

int ExternalDataCollector::GetBossHitPoint()
{
	return BossHitPoint;
}

void ExternalDataCollector::SetBossHurt(bool isHurt)
{
	isBossHaveHurt = isHurt;
}

bool ExternalDataCollector::GetBossHurt()
{
	return isBossHaveHurt;
}

double ExternalDataCollector::GetBossHurtTime()
{
	return this->BossHurtTime;
}

void ExternalDataCollector::SetBossHurtTime(double hurttime)
{
	BossHurtTime = hurttime;
}

void ExternalDataCollector::SetMapWidth(int width)
{
	mapWidth = width;
}

int ExternalDataCollector::GetMapWidth()
{
	return mapWidth;
}

ExternalDataCollector * ExternalDataCollector::GetInstance()
{
	if (instance == NULL)
	{
		instance =  new ExternalDataCollector();
	}
	return instance;
}

ExternalDataCollector::~ExternalDataCollector()
{
	//Khong xoa! ^^
}
