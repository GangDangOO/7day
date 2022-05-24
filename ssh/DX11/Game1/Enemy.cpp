#include "stdafx.h"

Enemy::Enemy(Enemy_Type type, int hp, int dmg, int def) : Status(hp, dmg, def)
{
	if (type == Enemy_Type::Warrior) {
		col = new ObRect();
		col->scale = Vector2(100.0f, 100.0f);
		col->isFilled = false;
		col->SetWorldPos(Vector2(-200.0f, -300.0f));

		idle = new ObImage(L"Enemy\\Warrior\\Idle.png");
		idle->scale = Vector2(140.0f, 140.0f);
		idle->maxFrame.x = 11;
		idle->frame.x = 0;
		idle->SetParentRT(*col);
		idle->ChangeAnim(ANISTATE::LOOP, 0.1f);

		hit = new ObImage(L"Enemy\\Warrior\\Take Hit.png");
		hit->scale = Vector2(140.0f, 140.0f);
		hit->maxFrame.x = 4;
		hit->frame.x = 0;
		hit->SetParentRT(*col);
		hit->ChangeAnim(ANISTATE::LOOP, 0.1f);

		dead = new ObImage(L"Enemy\\Warrior\\Death.png");
		dead->scale = Vector2(140.0f, 140.0f);
		dead->maxFrame.x = 9;
		dead->frame.x = 0;
		dead->SetParentRT(*col);
		dead->ChangeAnim(ANISTATE::ONCE, 0.1f);
	} 
	else if (type == Enemy_Type::Wizard) {
		col = new ObRect();
		col->scale = Vector2(100.0f, 100.0f);
		col->isFilled = false;
		col->SetWorldPos(Vector2(-200.0f, -300.0f));

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

	}
	idle->visible = true;
	hit->visible = false;
	dead->visible = false;
}

Enemy::~Enemy()
{
	SafeDelete(col);
	SafeDelete(idle);
	SafeDelete(hit);
}

void Enemy::Action()
{
	if (!b_dead) {
		if (hit->frame.x == hit->maxFrame.x - 1) {
			hit->visible = false;
			hit->frame.x = 0;
			idle->frame.x = 0;
			idle->visible = true;
		}
	}
	else {
		hit->visible = false;
		idle->visible = false;
		dead->visible = true;
	}
}

void Enemy::Hit(int dmg)
{
	if (!b_dead) {
		Status::Hit(dmg);
		hit->visible = true;
		idle->visible = false;
	}
}

void Enemy::Update()
{
	col->Update();
	idle->Update();
	hit->Update();
	dead->Update();
}

void Enemy::Render()
{
	col->Render();
	if (idle->visible) idle->Render();
	if (hit->visible) hit->Render();
	if (dead->visible) dead->Render();
}
