#include "stdafx.h"

Status::Status(int hp, int dmg, int def)
{
	this->hp = hp;
	this->dmg = dmg;
	this->def = def;

	defalut_hp = this->hp;
	defalut_dmg = this->dmg;
	defalut_def = this->def;
	b_invicible = false;
	b_dead = false;
}

Status::~Status()
{
}

void Status::Decrease_Hp(int dmg)
{
	if (!b_dead) {
		hp -= dmg - def;
		cout << name << " HP : " << hp << endl;
		if (hp <= 0) {
			b_dead = true;
		}
	}
}

void Status::Decrease_Dmg(int dec)
{
	if (!b_dead) dmg -= dec;
}

void Status::Decrease_Def(int dec)
{
	if (!b_dead) def -= dec;
}

void Status::Increase_Hp(int heal)
{
	if(!b_dead) hp += heal;
}

void Status::Increase_Dmg(int sum)
{
	if (!b_dead) dmg += sum;
}

void Status::Increase_Def(int sum)
{
	if (!b_dead) def += sum;
}

void Status::Hit(int dmg)
{
	Decrease_Hp(dmg);
	b_invicible = true;
	cout << name << " Hp : " << hp << endl;
}

void Status::Set_Defalut_Status()
{
	hp = defalut_hp;
	dmg = defalut_dmg;
	def = defalut_def;
	b_invicible = false;
	b_dead = false;
}

int Status::Get_Hp()
{
	return hp;
}

int Status::Get_Dmg()
{
	return dmg;
}

int Status::Get_Def()
{
	return def;
}
