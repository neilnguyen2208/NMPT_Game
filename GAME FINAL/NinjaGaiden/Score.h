#pragma once
class Score
{
	int score;		//Số điểm hiện có
	int power;		//Sức mạnh(mana) của ninja
	int ninjaBlood; // Máu của simon
	int bossBlood; // Máu của boss
	int scene;     //Màn hiện tại
	int beforeScene; //Lưu lại màn mà ninja chết 
	int fate;       //Mạng của ninja
	int skill;		//Skill của ninja: 1.BlueShuriken 2.RedShuriken 3.FlameRound
	int time;	

public:
	Score();
	~Score();

	////Hàm tính điểm
	//void CalculatorHurt(int a); //Truyền vào số máu bị mất
	//void CalculatorHurtBoss(int a);
	//void CalculatorItem(int a); //Truyền vào biến item nào
	//void CalculatorWhenBossDie();
	//void CalculatorOrb();
	//void Calculator1Sec();
	//Get
	int GetScore() { return score; };
	int GetPower() { return power; };
	int GetNinjaBlood() { return ninjaBlood; };
	int GetBossBlood() { return bossBlood; };
	int GetScene() { return scene; };
	int GetBeforeScene() { return beforeScene; };
	int GetTime() { return time; };
	int GetFate() { return fate; };
	int GetSkill() { return skill; };

	// SET
	void SetScore(int a) { score = a; };
	void SetPower(int a) { power = a; };
	void SetNinjaBlood(int a) { ninjaBlood = a; };
	void SetBossBlood(int a) { bossBlood = a; };
	void SetScene(int a) { scene = a; };
	void SetBeforeScene(int a) { beforeScene = a; };
	void SetTime(int a) { time = a; };
	void SetFate(int a) { fate = a; };
	void SetSkill(int a) { skill = a; };
};

