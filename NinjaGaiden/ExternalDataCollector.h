#pragma once
#include"d3dx9.h"
#include"BoxCollider.h"
class ExternalDataCollector
{
	static ExternalDataCollector*instance;
	ExternalDataCollector();
//player
	bool isCrossOverMap;
	bool isPlayerDead;
	bool isLost;
	int Life;
	long Score;
	int PlayerHitPoint;
	int Mana;
	bool haveClimb;

//boss
	int BossHitPoint;
	bool isBossHaveHurt;
	double BossHurtTime;
public:

//player
	enum SceneList
	{
		Scene3_1,
		Scene3_2,
		Scene3_3
	};
	SceneList CurScene;
	int CurSkill;
	void SetScene(SceneList scene);
	SceneList GetScene();
	void SetPlayerDead(bool);
	void SetCrossOverMap(bool);
	void SetScore(long);
	void SetMana(int);
	void SetHitPoint(int);
	void SetLife(int);
	void SetSkill(int);
	void SetLost(bool);
	void SetClimb(bool);
	bool GetClimb();
	long GetScore();
	int GetMana();
	int GetHitPoint();
	int GetLife();
	int GetSkill();
	bool GetLost();
	bool GetPlayerDead();
	bool GetCrossOverMap();
//boss
	void SetBossHitPoint(int);
	int GetBossHitPoint();
	void SetBossHurt(bool);
	bool GetBossHurt();
	double GetBossHurtTime();
	void SetBossHurtTime(double);

	static ExternalDataCollector*GetInstance();	
	~ExternalDataCollector();
};

