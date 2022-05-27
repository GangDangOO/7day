#pragma once

#define RESPAWN_COOL 5.0f
#define RESET_INT_STATE 2.0f
#define ATTACK_COOL 1.0f
enum class Enemy_Type {
	Warrior,
	Wizard,
	Huntress
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
	ObImage*	magic;
	ObImage*	arrow[5];
	int			rd_fatrol;
	int			rd_spawn;
	float		time_random;
	float		time_respawn;
	float		time_atk_cool;
	bool		b_power_dir;
public:
	ObRect* col;
	ObRect* arrow_col[5];
	ObRect* atk1_col;
	ObRect* atk2_col;
	bool	b_act_atk1;
	bool	b_act_atk2;
	bool	b_arrow_act[5];

	Enemy(Enemy_Type type, int hp, int dmg, int def);
	~Enemy();
	void			Action(Vector2 player);
	void			Hit(int dmg);
	void			Change_State(STATE ps);
	void			Power_Attack(Vector2 pos);
	void			Respawn(Vector2 pos);
	void			Update();
	void			Render();
};

