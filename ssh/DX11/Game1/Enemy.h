#pragma once

enum class Enemy_Type {
	Warrior,
	Wizard
};

class Enemy : public Status
{
private:
	Enemy_Type	type;
	STATE		state;
	ObImage*	idle;
	ObImage*	run;
	ObImage*	jump;
	ObImage*	fall;
	ObImage*	attack1;
	ObImage*	attack2;
	ObImage*	hit;
	ObImage*	death;
	int			rd_fatrol;
	int			rd_spawn;
	float		time_random = 5.0f;
	float		time_respawn = 4.0f;
public:
	ObRect* col;
	ObRect* atk1_col;
	bool	b_act_atk1;

	Enemy(Enemy_Type type, int hp, int dmg, int def);
	~Enemy();
	void			Action(Vector2 player);
	void			Hit(int dmg);
	void			Change_State(STATE ps);
	void			Respawn(Vector2 pos);
	void			Update();
	void			Render();
};

