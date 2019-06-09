#include "Scoreboard.h"
Scoreboard::Scoreboard()
{
	auto texture1 = Textures::GetInstance();
	texture1->Add(TEX_BLOOD, "Resources/Sprites/health1.png", D3DCOLOR_XRGB(255, 255, 255));
	texblood1 = texture1->Get(TEX_BLOOD);

	auto texture2 = Textures::GetInstance();
	texture2->Add(TEX_BLEED, "Resources/Sprites/health2.png", D3DCOLOR_XRGB(255, 255, 255));
	texblood2 = texture2->Get(TEX_BLEED);

	auto texture3 = Textures::GetInstance();
	texture3->Add(TEX_POWER, "Resources/Sprites/power.png", D3DCOLOR_XRGB(255, 255, 255));
	texpower = texture3->Get(TEX_POWER);

	auto texture4 = Textures::GetInstance();
	texture4->Add(TEX_BORDER, "Resources/Sprites/border.png", D3DCOLOR_XRGB(255, 255, 255));
	texborder = texture4->Get(TEX_BORDER);

	auto texture5 = Textures::GetInstance();
	texture5->Add(TEX_SKILL_1, "Resources/Sprites/skill1.png", D3DCOLOR_XRGB(255, 163, 177));
	texskill1 = texture5->Get(TEX_SKILL_1);

	auto texture6 = Textures::GetInstance();
	texture6->Add(TEX_SKILL_2, "Resources/Sprites/skill2.png", D3DCOLOR_XRGB(255, 163, 177));
	texskill2 = texture6->Get(TEX_SKILL_2);

	auto texture7 = Textures::GetInstance();
	texture7->Add(TEX_SKILL_3, "Resources/Sprites/skill3.png", D3DCOLOR_XRGB(255, 163, 177));
	texskill3 = texture7->Get(TEX_SKILL_3);
}

Scoreboard::~Scoreboard()
{

}

void Scoreboard::DrawTextTop(LPDIRECT3DDEVICE9 gDevice, int score, int fate, int time, int stage, int blood, int bloodEnemy, int power, int skill)
{

	{
	//PLAYER + ENEMY + POWER PLAYER + SKILL BORDER  + SKILL
	
	//player blood
	for (int i = 0; i < 16; i++)
	{
		if (blood > i)
			Graphic::GetInstance()->Draw(165 + i * 5, 14, texblood1);
		else
			Graphic::GetInstance()->Draw(165 + i * 5, 14, texblood2);
	}
	//enemy blood
	for (int i = 0; i < 16; i++)
	{
		if (bloodEnemy > i)
			Graphic::GetInstance()->Draw(165 + i * 5, 28, texblood1);
		else
			Graphic::GetInstance()->Draw(165 + i * 5, 28, texblood2);
	}

	//power
	Graphic::GetInstance()->Draw(61, 30, texpower);

	//skill border
	Graphic::GetInstance()->Draw(95, 17, texborder);

	//skill
	switch (skill)
	{
	case 0:
		break;
	case 1:
		Graphic::GetInstance()->Draw(98, 21, texskill1);
		break;
	case 2:
		Graphic::GetInstance()->Draw(98, 21, texskill2);
		break;
	case 3:
		Graphic::GetInstance()->Draw(98, 21, texskill3);
		break;
	}

	}

	hr = D3DXCreateFont(gDevice, 14, 0, FW_NORMAL, 2, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		 ANTIALIASED_QUALITY, FF_MODERN, "Arial", &font);
	fSprite = Graphic::GetInstance()->GetSpriteHandler();
	if (SUCCEEDED(hr))
	{
		s1 = to_string(score);
		int s1_length = s1.length();
		if (s1_length < 6)
			for (int i = 0; i < 6 - s1_length; i++)
				s1 = "0" + s1;
		t = to_string(time);
		int t_length = t.length();
		if (s1_length < 3)
			for (int i = 0; i < 3 - t_length; i++)
				t = "0" + t;
		st = to_string(stage);
		f = to_string(fate);
		int f_length = f.length();
		if (f_length < 2)
			for (int i = 0; i < 2 - f_length; i++)
				f = "0" + f;
		p = to_string(power);
		int p_length = p.length();
		if (p_length < 2)
			for (int i = 0; i < 2 - p_length; i++)
				p = "0" + p;
		SetRect(&fRec, 30, 0, 256, 60);
		if (font)
		{
			string s = " SCORE- " + s1 + "   " + "STAGE- 3-" + st +
				" \n TIMER- " + t + "           " + "PLAYER-" + "                                         " +
				" \n P- " + f + "     - " + p + "           " + "ENEMY-" + "                                         ";
			hr = font->DrawText(fSprite, s.c_str(), -1, &fRec, DT_NOCLIP | DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
			if FAILED(hr)
				hr = hr;
		}
	}

	if (font != NULL)
		font->Release();
}