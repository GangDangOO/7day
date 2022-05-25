#pragma once

enum class STATE {
	NONE,
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
	int		defalut_hp;
	int		defalut_dmg;
	int		defalut_def;
public:
	string	name;
	bool	b_dead;
	bool	b_invicible;

	Status(int hp, int dmg, int def);
	~Status();
	void			Decrease_Hp(int hp);
	void			Decrease_Dmg(int dmg);
	void			Decrease_Def(int def);
	void			Increase_Hp(int hp);
	void			Increase_Dmg(int dmg);
	void			Increase_Def(int def);
	void			Hit(int dmg);
	void			Set_Defalut_Status();
	int				Get_Hp();
	int				Get_Dmg();
	int				Get_Def();
};

