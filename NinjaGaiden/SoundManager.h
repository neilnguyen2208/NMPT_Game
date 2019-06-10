#pragma once
#include "GAudio.h"

class CSoundChoose
{
private:
	static CSoundChoose *instance;

	//Thư mục music
	GAudio* audio;
	GSound* Stage31;
	GSound* Stage32;
	GSound* Stage33;

	//Thư mục sound

	//Boss
	GSound* BossDie;
	GSound* BossGround;

	//Enemy
	GSound* EnemyDie;
	GSound* Cannoer;
	GSound* Solider;

	//Ninja
	GSound* NinjaDie;
	GSound* NinjaJump;
	GSound* NinjaSlash;
	GSound* NinjaBeaten;
	GSound* NinjaItem;

	//Skill
	GSound* SkillTimeFreeze;
	GSound* SkillBlue;
	GSound* SkillRed;
	GSound* SkillFlame;

public:
	static CSoundChoose *GetInstance();
	void PlaySoundChoose(int number);
	void PlayMusicChoose(int number);
	void StopSound();
	void InitCSoundChoose(HWND hWnd);
	~CSoundChoose();
};