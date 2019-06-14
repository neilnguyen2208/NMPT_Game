#include "SoundManager.h"

CSoundChoose *CSoundChoose::instance = NULL;

CSoundChoose * CSoundChoose::GetInstance() {
	if (instance == NULL)
		instance = new CSoundChoose();
	return instance;
}

void CSoundChoose::InitCSoundChoose(HWND hWnd)
{
	audio = new GAudio();

	//Thư mục music
	audio->Init_DirectSound(hWnd);

	Stage31 = audio->LoadSound((char*)"Sounds\\music\\Stage31.wav");
	Stage32 = audio->LoadSound((char*)"Sounds\\music\\Stage32.wav");
	Stage33 = audio->LoadSound((char*)"Sounds\\music\\Stage33.wav");
	
	//Thư mục sound
	BossDie = audio->LoadSound((char*)"Sounds\\sound\\BossDie.wav");
	BossGround = audio->LoadSound((char*)"Sounds\\sound\\BossGround.wav");

	EnemyDie = audio->LoadSound((char*)"Sounds\\sound\\EnemyDie.wav");
	Cannoer = audio->LoadSound((char*)"Sounds\\sound\\Cannoer.wav");
	Solider = audio->LoadSound((char*)"Sounds\\sound\\Solider.wav");

	NinjaDie = audio->LoadSound((char*)"Sounds\\sound\\NinjaDie.wav");
	NinjaJump = audio->LoadSound((char*)"Sounds\\sound\\NinjaJump.wav");
	NinjaSlash = audio->LoadSound((char*)"Sounds\\sound\\NinjaSlash.wav");
	NinjaBeaten = audio->LoadSound((char*)"Sounds\\sound\\NinjaBeaten.wav");
	NinjaItem = audio->LoadSound((char*)"Sounds\\sound\\NinjaItem.wav");

	SkillTimeFreeze = audio->LoadSound((char*)"Sounds\\sound\\SkillTimeFreeze.wav");
	SkillBlue = audio->LoadSound((char*)"Sounds\\sound\\SkillBlue.wav");
	SkillRed = audio->LoadSound((char*)"Sounds\\sound\\SkillRed.wav");
	SkillFlame = audio->LoadSound((char*)"Sounds\\sound\\SkillFlame.wav");
}


void CSoundChoose::PlayMusicChoose(int number)
{
	switch (number)
	{
	case 1: 
	{
		audio->LoopSound(Stage31);
	}break;
	case 2:
	{
		audio->LoopSound(Stage32);
	}break;
	case 3: 
	{
		audio->LoopSound(Stage33);
	}break;
	default:
	{}break;
	}
}
void CSoundChoose::PlaySoundChoose(int number)
{
	switch (number)
	{
	case 1: //Khi boss chết
	{
		audio->PlaySound(BossDie);
	}break;
	case 2: //Khi boss nhảy xuống chạm đất
	{
		audio->PlaySound(BossGround);
	}break;
	case 3: //Khi enemy chết
	{
		audio->PlaySound(EnemyDie);
	}break;
	case 4: //Khi Solider bắn 
	{
		audio->PlaySound(Solider);
	}break;
	case 5: //Khi Cannoer bắn 
	{
		audio->PlaySound(Cannoer);
	}break;
	case 6: 
	{
		audio->PlaySound(NinjaBeaten);
	}break;
	case 7: 
	{
		audio->PlaySound(NinjaSlash);
	}break;
	case 8:
	{
		audio->PlaySound(NinjaJump);
	} break;
	case 9: 
	{
		audio->PlaySound(NinjaItem);
	} break;
	case 10:
	{
		audio->PlaySound(NinjaDie);
	} break;
	case 11: //Khi sử dụng SkillTimeFreeze
	{
		audio->PlaySound(SkillTimeFreeze);
	} break;
	case 12: //Khi sử dụng SkillBlue
	{
		audio->PlaySound(SkillBlue);
	} break;
	case 13: //Khi sử dụng SkillRed
	{
		audio->PlaySound(SkillRed);
	} break;
	case 14: //Khi sử dụng SkillFlame
	{
		audio->PlaySound(SkillFlame);
	} break;
	default:
	{
	} break;
	}
}

void CSoundChoose::StopSound()
{
	audio->StopSound(Stage31);
	audio->StopSound(Stage32);
	audio->StopSound(Stage33);
}
void CSoundChoose::StopSoundDie()
{
	audio->StopSound(BossDie);
	audio->StopSound(NinjaDie);
}
