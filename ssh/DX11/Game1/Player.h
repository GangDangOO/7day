#pragma once

class Player : public Status
{
private:
	STATE			state;
	ObImage*		idle;
	ObImage*		run;
	ObImage*		jump;
	ObImage*		fall;
	ObImage*		attack1;
	ObImage*		attack2;
	ObImage*		hit;
	Vector2			move;
	float			speed;
	float			gravity;
	float			cooltime_attack;
	bool			b_jump;
	bool			b_attack;
public:
	ObRect*			atk1_col;
	ObRect*			atk2_col;
	ObRect*			col;
	bool			b_act_atk1;
	bool			b_act_atk2;

	Player(int hp, int dmg, int def);
	~Player();
	void Action();
	void Fall_Down();
	void Change_State(STATE ps);
	void Update();
	void Render();
};

