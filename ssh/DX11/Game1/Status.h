#pragma once

enum class STATE {
	IDLE,
	RUN,
	JUMP,
	FALL,
	ATTACK1,
	ATTACK2,
	Hit,
	Death
};

class Status
{
private:
	int		hp;
	int		dmg;
	int		def;
	bool	b_invicible;
public:
	bool	b_dead;

	Status(int hp, int dmg, int def);
	~Status();
	void			Decrease_Hp(int hp);
	void			Decrease_Dmg(int dmg);
	void			Decrease_Def(int def);
	void			Increase_Hp(int hp);
	void			Increase_Dmg(int dmg);
	void			Increase_Def(int def);
	void			Invicible_Off();
	void			Hit(int dmg);
	int				Get_Hp();
	int				Get_Dmg();
	int				Get_Def();
};

