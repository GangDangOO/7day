#include "stdafx.h"

Enemy::Enemy(Enemy_Type type, int hp, int dmg, int def) : Status(hp, dmg, def)
{
	if (type == Enemy_Type::Warrior) {
		col = new ObRect();
		col->scale = Vector2(60.0f, 90.0f);
		col->isFilled = false;

		idle = new ObImage(L"Enemy\\Warrior\\Idle.png");
		idle->scale = Vector2(140.0f, 140.0f) * 2.0f;
		idle->maxFrame.x = 11;
		idle->frame.x = 0;
		idle->SetParentRT(*col);
		idle->ChangeAnim(ANISTATE::LOOP, 0.1f);

		hit = new ObImage(L"Enemy\\Warrior\\Take Hit.png");
		hit->scale = Vector2(140.0f, 140.0f) * 2.0f;
		hit->maxFrame.x = 4;
		hit->frame.x = 0;
		hit->SetParentRT(*col);
		hit->ChangeAnim(ANISTATE::LOOP, 0.1f);

		death = new ObImage(L"Enemy\\Warrior\\Death.png");
		death->scale = Vector2(140.0f, 140.0f) * 2.0f;
		death->maxFrame.x = 9;
		death->frame.x = 0;
		death->SetParentRT(*col);
		death->ChangeAnim(ANISTATE::ONCE, 0.1f);
	} 
	else if (type == Enemy_Type::Wizard) {
		col = new ObRect();
		col->scale = Vector2(60.0f, 60.0f);
		col->isFilled = false;

		idle = new ObImage(L"Enemy\\Wizard\\Idle.png");
		idle->scale = Vector2(140.0f, 140.0f);
		idle->maxFrame.x = 6;
		idle->frame.x = 0;
		idle->SetParentRT(*col);
		idle->ChangeAnim(ANISTATE::LOOP, 0.1f);

		hit = new ObImage(L"Enemy\\Wizard\\Hit.png");
		hit->scale = Vector2(140.0f, 140.0f);
		hit->maxFrame.x = 4;
		hit->frame.x = 0;
		hit->SetParentRT(*col);
		hit->ChangeAnim(ANISTATE::ONCE, 0.1f);

		death = new ObImage(L"Enemy\\Wizard\\Death.png");
		death->scale = Vector2(140.0f, 140.0f) * 2.0f;
		death->maxFrame.x = 7;
		death->frame.x = 0;
		death->SetParentRT(*col);
		death->ChangeAnim(ANISTATE::ONCE, 0.1f);
	}
	idle->visible = true;
	hit->visible = false;
	death->visible = false;
}

Enemy::~Enemy()
{
	SafeDelete(col);
	SafeDelete(idle);
	SafeDelete(run);
	SafeDelete(jump);
	SafeDelete(fall);
	SafeDelete(hit);
	SafeDelete(death);
	SafeDelete(attack1);
	SafeDelete(attack2);
}

void Enemy::Action()
{
	if (!b_dead) {
		if (hit->frame.x == hit->maxFrame.x - 1) {
			Change_State(STATE::IDLE);
		}
	}
	else {
		Change_State(STATE::Death);
	}
}

void Enemy::Hit(int dmg)
{
	if (!b_dead) {
		Status::Hit(dmg);
		Change_State(STATE::Hit);
	}
}

void Enemy::Change_State(STATE ps)
{
	if (state != ps) {
		cout << "½ÇÇàµÊ" << endl;
		state = ps;
		if (state == STATE::IDLE) {
			idle->frame.x = 0;
			idle->visible = true;
		}
		else idle->visible = false;

		if (state == STATE::Hit) {
			hit->frame.x = 0;
			hit->visible = true;
		}
		else hit->visible = false;

		if (state == STATE::Death) {
			death->frame.x = 0;
			death->visible = true;
		}
		else death->visible = false;
	}
}

void Enemy::Update()
{
	col->Update();
	idle->Update();
	hit->Update();
	death->Update();
}

void Enemy::Render()
{
	col->Render();
	if (idle->visible) idle->Render();
	if (hit->visible) hit->Render();
	if (death->visible) death->Render();
}
