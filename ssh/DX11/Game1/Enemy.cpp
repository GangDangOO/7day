#include "stdafx.h"

Enemy::Enemy(Enemy_Type type, int hp, int dmg, int def) : Status(hp, dmg, def)
{
	this->type = type;
	if (type == Enemy_Type::Warrior) {
		name = "Warrior";

		col = new ObRect();
		col->scale = Vector2(60.0f, 90.0f);
		col->isFilled = false;

		idle = new ObImage(L"Enemy\\Warrior\\Idle.png");
		idle->scale = Vector2(140.0f, 140.0f) * 2.0f;
		idle->maxFrame.x = 11;
		idle->frame.x = 0;
		idle->SetParentRT(*col);
		idle->MoveLocalPos(Vector2(0.0f, -10.0f));
		idle->ChangeAnim(ANISTATE::LOOP, 0.1f);

		run = new ObImage(L"Enemy\\Warrior\\Run.png");
		run->scale = Vector2(140.0f, 140.0f) * 2.0f;
		run->maxFrame.x = 8;
		run->frame.x = 0;
		run->SetParentRT(*col);
		run->MoveLocalPos(Vector2(0.0f, -10.0f));
		run->ChangeAnim(ANISTATE::LOOP, 0.1f);

		attack1 = new ObImage(L"Enemy\\Warrior\\Attack1.png");
		attack1->scale = Vector2(140.0f, 140.0f) * 2.0f;
		attack1->maxFrame.x = 6;
		attack1->frame.x = 0;
		attack1->SetParentRT(*col);
		attack1->MoveLocalPos(Vector2(0.0f, -10.0f));
		attack1->ChangeAnim(ANISTATE::ONCE, 0.1f);

		hit = new ObImage(L"Enemy\\Warrior\\Take Hit.png");
		hit->scale = Vector2(140.0f, 140.0f) * 2.0f;
		hit->maxFrame.x = 4;
		hit->frame.x = 0;
		hit->SetParentRT(*col);
		hit->MoveLocalPos(Vector2(0.0f, -10.0f));
		hit->ChangeAnim(ANISTATE::ONCE, 0.1f);

		death = new ObImage(L"Enemy\\Warrior\\Death.png");
		death->scale = Vector2(140.0f, 140.0f) * 2.0f;
		death->maxFrame.x = 9;
		death->frame.x = 0;
		death->SetParentRT(*col);
		death->MoveLocalPos(Vector2(0.0f, -10.0f));
		death->ChangeAnim(ANISTATE::ONCE, 0.1f);

		atk1_col = new ObRect();
		atk1_col->scale = Vector2(170.0f, 80.0f);
		atk1_col->isFilled = false;
		atk1_col->SetParentRT(*col);

		b_act_atk1 = false;
	} 
	else if (type == Enemy_Type::Wizard) {
		name = "Wizard";

		col = new ObRect();
		col->scale = Vector2(60.0f, 90.0f);
		col->isFilled = false;

		idle = new ObImage(L"Enemy\\Wizard\\Idle.png");
		idle->scale = Vector2(140.0f, 140.0f) * 1.5f;
		idle->maxFrame.x = 6;
		idle->frame.x = 0;
		idle->SetParentRT(*col);
		idle->ChangeAnim(ANISTATE::LOOP, 0.1f);

		run = new ObImage(L"Enemy\\Wizard\\Run.png");
		run->scale = Vector2(140.0f, 140.0f) * 1.5f;
		run->maxFrame.x = 8;
		run->frame.x = 0;
		run->SetParentRT(*col);
		run->ChangeAnim(ANISTATE::LOOP, 0.1f);

		attack1 = new ObImage(L"Enemy\\Wizard\\Attack1.png");
		attack1->scale = Vector2(140.0f, 140.0f) * 1.5f;
		attack1->maxFrame.x = 8;
		attack1->frame.x = 0;
		attack1->SetParentRT(*col);
		attack1->ChangeAnim(ANISTATE::ONCE, 0.1f);

		hit = new ObImage(L"Enemy\\Wizard\\Hit.png");
		hit->scale = Vector2(140.0f, 140.0f) * 1.5f;
		hit->maxFrame.x = 4;
		hit->frame.x = 0;
		hit->SetParentRT(*col);
		hit->ChangeAnim(ANISTATE::ONCE, 0.1f);

		death = new ObImage(L"Enemy\\Wizard\\Death.png");
		death->scale = Vector2(140.0f, 140.0f) * 1.5f;
		death->maxFrame.x = 7;
		death->frame.x = 0;
		death->SetParentRT(*col);
		death->ChangeAnim(ANISTATE::ONCE, 0.1f);

		atk1_col = new ObRect();
		atk1_col->scale = Vector2(40.0f, 40.0f);
		atk1_col->isFilled = false;
		atk1_col->SetParentRT(*col);
	}
	state = STATE::NONE;
	Change_State(STATE::IDLE);
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

void Enemy::Action(Vector2 player)
{
	if (!b_dead) {
		if (INPUT->KeyDown('E')) {
			if (col->GetWorldPos().x > player.x) {
				if (type == Enemy_Type::Warrior) {
					atk1_col->SetLocalPosX(-20.0f);
				}
				else if (type == Enemy_Type::Wizard) {
					atk1_col->SetLocalPosX(-40.0f);
				}
				attack1->reverseLR = true;
			}
			else if (col->GetWorldPos().x < player.x) {
				if (type == Enemy_Type::Warrior) {
					atk1_col->SetLocalPosX(20.0f);
				}
				else if (type == Enemy_Type::Wizard) {
					atk1_col->SetLocalPosX(40.0f);
				}
				attack1->reverseLR = false;
			}
			Change_State(STATE::ATTACK1);
		}
		if (attack1->frame.x == attack1->maxFrame.x - 3) {
			b_act_atk1 = true;
		}
		else if (attack1->frame.x == attack1->maxFrame.x - 1) {
			b_act_atk1 = false;
			Change_State(STATE::IDLE);
		}
		if (state != STATE::ATTACK1 && state != STATE::ATTACK2) {

			// ������ �ൿ
			time_random -= DELTA;
			if (time_random < 0.0f) {
				rd_fatrol = RANDOM->Int(0, 2);
				time_random = 2.0f;
			}
			// �ǰݻ��°� �ƴ� ��
			if (!b_invicible) {
				if (col->GetWorldPos().x > player.x) {
					idle->reverseLR = true;
					run->reverseLR = true;
					hit->reverseLR = true;
					death->reverseLR = true;
				}
				else if (col->GetWorldPos().x < player.x) {
					idle->reverseLR = false;
					run->reverseLR = false;
					hit->reverseLR = false;
					death->reverseLR = false;
				}
				switch (rd_fatrol)
				{
				case 0:
					// ������ �ֱ�
					Change_State(STATE::IDLE);
					break;
				case 1:
					// �÷��̾�� �̵�
					Change_State(STATE::RUN);
					if (run->reverseLR == true) {
						col->MoveWorldPos(Vector2(-180.0f * DELTA, 0.0f));
					}
					else {
						col->MoveWorldPos(Vector2(180.0f * DELTA, 0.0f));
					}
					break;
				case 2:
					// Ŭ������ Ư���ൿ
					cout << name << " �ٽ� �Ѹ�" << endl;
					time_random = 0.0f;
					break;
				default:
					break;
				}
			} else if (hit->frame.x == hit->maxFrame.x - 1) {
				Change_State(STATE::IDLE);
			}
		}
	}
	else {
		Change_State(STATE::Death);
	}
}

void Enemy::Hit(int dmg)
{
	if (!b_dead && !b_invicible) {
		Status::Hit(dmg);
		Change_State(STATE::Hit);
	}
}

void Enemy::Change_State(STATE ps)
{
	if (state != ps) {
		state = ps;
		if (state == STATE::IDLE) {
			cout << name << " �������ֱ�" << endl;
			idle->visible = true;
		}
		else {
			idle->frame.x = 0;
			idle->visible = false;
		}

		if (state == STATE::RUN) {
			cout << name << " �����̱�" << endl;
			run->visible = true;
		}
		else {
			run->frame.x = 0;
			run->visible = false;
		}

		if (state == STATE::ATTACK1) {
			cout << name << "����" << endl;
			attack1->visible = true;
		}
		else {
			attack1->frame.x = 0;
			attack1->visible = false;
		}

		if (state == STATE::Hit) {
			cout << name << " ����������" << endl;
			hit->visible = true;
		}
		else {
			hit->frame.x = 0;
			hit->visible = false;
		}

		if (state == STATE::Death) {
			death->ChangeAnim(ANISTATE::ONCE, 0.1f);
			death->visible = true;
		}
		else {
			death->frame.x = 0;
			death->visible = false;
		}
	}
}

void Enemy::Respawn(Vector2 pos)
{
	time_respawn -= DELTA;
	if (time_respawn < 0.0f) {
		time_respawn = 4.0f;
		col->SetWorldPosX(pos.x + 500.0f);
		Set_Defalut_Status();
		time_random = 0.0f;
		Change_State(STATE::IDLE);
	}
}

void Enemy::Update()
{
	col->Update();
	atk1_col->Update();

	idle->Update();
	run->Update();
	attack1->Update();
	hit->Update();
	death->Update();
}

void Enemy::Render()
{
	col->Render();
	atk1_col->Render();
	if (idle->visible) idle->Render();
	if (run->visible) run->Render();
	if (attack1->visible) attack1->Render();
	if (hit->visible) hit->Render();
	if (death->visible) death->Render();
}
