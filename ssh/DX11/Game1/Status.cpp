#include "stdafx.h"

Status::Status(int hp, int dmg, int def)
{
	this->hp = hp;
	this->dmg = dmg;
	this->def = def;

	b_dead = false;
}

Status::~Status()
{
}

void Status::Decrease_Hp(int dmg)
{
	if (!b_dead) {
		hp -= dmg - def;
		if (hp <= 0) {
			cout << "À¸¾Ç" << endl;
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

void Status::Invicible_Off()
{
	b_invicible = false;
}

void Status::Hit(int dmg)
{
	if (!b_invicible && !b_dead) {
		Decrease_Hp(dmg);
		cout << hp << endl;
		b_invicible = true;
	}
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
