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
	ObImage*	hit;
	ObImage*	dead;
public:
	ObRect* col;

	Enemy(Enemy_Type type, int hp, int dmg, int def);
	~Enemy();
	void			Action();
	void			Hit(int dmg);
	void			Update();
	void			Render();
};

