#pragma once

enum class Enemy_Type {
	Warrior,
	Wizard
};

class Enemy : public Status
{
private:
	STATE		state;
	ObImage*	idle;
	ObImage*	run;
	ObImage*	jump;
	ObImage*	fall;
	ObImage*	attack1;
	ObImage*	attack2;
	ObImage*	hit;
	ObImage*	death;
public:
	ObRect* col;

	Enemy(Enemy_Type type, int hp, int dmg, int def);
	~Enemy();
	void			Action();
	void			Hit(int dmg);
	void			Change_State(STATE ps);
	void			Update();
	void			Render();
};

