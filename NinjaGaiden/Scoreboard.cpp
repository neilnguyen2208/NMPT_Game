#include "Scoreboard.h"
Scoreboard::Scoreboard()
{
	auto texture1 = Textures::GetInstance();
	texture1->Add(TEX_BLOOD, "Resources/Sprites/health1.png", D3DCOLOR_XRGB(255, 255, 255));
	tex1 = texture1->Get(TEX_BLOOD);

	auto texture2 = Textures::GetInstance();
	texture2->Add(TEX_BLEED, "Resources/Sprites/health2.png", D3DCOLOR_XRGB(255, 255, 255));
	tex2 = texture2->Get(TEX_BLEED);

	auto texture3 = Textures::GetInstance();
	texture3->Add(TEX_POWER, "Resources/Sprites/power.png", D3DCOLOR_XRGB(255, 255, 255));
	texpower = texture3->Get(TEX_POWER);

	auto texture4 = Textures::GetInstance();
	texture4->Add(TEX_BORDER, "Resources/Sprites/border.png", D3DCOLOR_XRGB(255, 255, 255));
	texborder = texture4->Get(TEX_BORDER);

}

Scoreboard::~Scoreboard()
{

}

void Scoreboard::DrawTextTop(LPDIRECT3DDEVICE9 gDevice, int score, int time, int stage, int life, int lifeEnemy, int power)
{

	{
	//Blood PLAYER + ENEMY + POWER PLAYER + BORDER SKILL
	//player 165, 14
	for (int i = 0; i < 16; i++)
	{
		if (life > i)
			Graphic::GetInstance()->Draw(165 + i * 5, 14, tex1);
		else
			Graphic::GetInstance()->Draw(165 + i * 5, 14, tex2);
	}
	//enemy 165, 28
	for (int i = 0; i < 16; i++)
	{
		if (lifeEnemy > i)
			Graphic::GetInstance()->Draw(165 + i * 5, 28, tex1);
		else
			Graphic::GetInstance()->Draw(165 + i * 5, 28, tex2);
	}

	Graphic::GetInstance()->Draw(59, 29, texpower);
	Graphic::GetInstance()->Draw(95, 17, texborder);
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
		l = to_string(life);
		int l_length = l.length();
		if (l_length < 2)
			for (int i = 0; i < 2 - l_length; i++)
				l = "0" + l;
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
				" \n P- " + l + "     - " + p + "           " + "ENEMY-" + "                                         ";
			hr = font->DrawText(fSprite, s.c_str(), -1, &fRec, DT_NOCLIP | DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
			if FAILED(hr)
				hr = hr;
		}
	}

	if (font != NULL)
		font->Release();
}