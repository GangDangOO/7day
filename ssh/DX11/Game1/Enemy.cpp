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
		attack1->ChangeAnim(ANISTATE::ONCE, 0.2f);

		attack2 = new ObImage(L"Enemy\\Warrior\\Attack2.png");
		attack2->scale = Vector2(140.0f, 140.0f) * 2.0f;
		attack2->maxFrame.x = 4;
		attack2->frame.x = 0;
		attack2->SetParentRT(*col);
		attack2->MoveLocalPos(Vector2(0.0f, -10.0f));
		attack2->ChangeAnim(ANISTATE::LOOP, 0.1f);

		hit = new ObImage(L"Enemy\\Warrior\\Take Hit.png");
		hit->scale = Vector2(140.0f, 140.0f) * 2.0f;
		hit->maxFrame.x = 4;
		hit->frame.x = 0;
		hit->SetParentRT(*col);
		hit->MoveLocalPos(Vector2(0.0f, -10.0f));
		hit->ChangeAnim(ANISTATE::ONCE, 0.2f);

		death = new ObImage(L"Enemy\\Warrior\\Death.png");
		death->scale = Vector2(140.0f, 140.0f) * 2.0f;
		death->maxFrame.x = 9;
		death->frame.x = 0;
		death->SetParentRT(*col);
		death->MoveLocalPos(Vector2(0.0f, -10.0f));
		death->ChangeAnim(ANISTATE::ONCE, 0.2f);

		atk1_col = new ObRect();
		atk1_col->scale = Vector2(170.0f, 80.0f);
		atk1_col->isFilled = false;
		atk1_col->SetParentRT(*col);

		atk2_col = new ObRect();
		atk2_col->scale = Vector2(60.0f, 90.0f);
		atk2_col->isFilled = false;
		atk2_col->SetParentRT(*col);

		b_act_atk1 = false;
		b_act_atk2 = false;
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

		attack2 = new ObImage(L"Enemy\\Wizard\\Attack2.png");
		attack2->scale = Vector2(140.0f, 140.0f) * 1.5f;
		attack2->maxFrame.x = 8;
		attack2->frame.x = 0;
		attack2->SetParentRT(*col);
		attack2->ChangeAnim(ANISTATE::ONCE, 0.1f);

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
		atk1_col->scale = Vector2(60.0f, 70.0f);
		atk1_col->isFilled = false;
		atk1_col->SetParentRT(*col);

		atk2_col = new ObRect();
		atk2_col->scale = Vector2(700.0f, 700.0f) * 0.15f;
		atk2_col->isFilled = false;

		magic = new ObImage(L"Effect\\12_nebula_spritesheet.png");
		magic->scale = Vector2(800.0f, 800.0f) * 0.2f;
		magic->maxFrame.x = 8;
		magic->maxFrame.y = 8;
		magic->frame.x = 0;
		magic->frame.y = 0;
		magic->SetParentRT(*atk2_col);
		magic->ChangeAnim(ANISTATE::LOOP, 0.1f);
	}
	else if (type == Enemy_Type::Huntress) {
		name = "Huntress";

		col = new ObRect();
		col->scale = Vector2(60.0f, 90.0f);
		col->isFilled = false;

		idle = new ObImage(L"Enemy\\Huntress\\Idle.png");
		idle->scale = Vector2(100.0f, 100.0f) * 2.0f;
		idle->maxFrame.x = 10;
		idle->frame.x = 0;
		idle->SetParentRT(*col);
		idle->ChangeAnim(ANISTATE::LOOP, 0.1f);

		run = new ObImage(L"Enemy\\Huntress\\Run.png");
		run->scale = Vector2(100.0f, 100.0f) * 2.0f;
		run->maxFrame.x = 8;
		run->frame.x = 0;
		run->SetParentRT(*col);
		run->ChangeAnim(ANISTATE::LOOP, 0.1f);

		wstring w = L"Enemy\\Huntress\\Attack.png";
		attack1 = new ObImage(L"Enemy\\Huntress\\Attack.png");
		attack1->scale = Vector2(100.0f, 100.0f) * 2.0f;
		attack1->maxFrame.x = 6;
		attack1->frame.x = 0;
		attack1->SetParentRT(*col);
		attack1->ChangeAnim(ANISTATE::ONCE, 0.1f);

		attack2 = new ObImage(L"Enemy\\Huntress\\Attack.png");
		attack2->scale = Vector2(100.0f, 100.0f) * 2.0f;
		attack2->maxFrame.x = 6;
		attack2->frame.x = 0;
		attack2->SetParentRT(*col);
		attack2->ChangeAnim(ANISTATE::ONCE, 0.1f);

		hit = new ObImage(L"Enemy\\Huntress\\Hit.png");
		hit->scale = Vector2(100.0f, 100.0f) * 2.0f;
		hit->maxFrame.x = 3;
		hit->frame.x = 0;
		hit->SetParentRT(*col);
		hit->ChangeAnim(ANISTATE::ONCE, 0.1f);

		death = new ObImage(L"Enemy\\Huntress\\Death.png");
		death->scale = Vector2(100.0f, 100.0f) * 2.0f;
		death->maxFrame.x = 10;
		death->frame.x = 0;
		death->SetParentRT(*col);
		death->ChangeAnim(ANISTATE::ONCE, 0.1f);

		for (int i = 0; i < 5; i++) {
			arrow_col[i] = new ObRect();
			arrow_col[i]->scale = Vector2(24.0f, 5.0f) * 2.0f;
			arrow_col[i]->isFilled = false;
			arrow_col[i]->SetWorldPos(Vector2(0.0f, 800.0f));

			arrow[i] = new ObImage(L"Enemy\\Huntress\\Move.png");
			arrow[i]->scale = Vector2(24.0f, 5.0f) * 2.0f;
			arrow[i]->maxFrame.x = 2;
			arrow[i]->frame.x = 0;
			arrow[i]->SetParentRT(*arrow_col[i]);
			arrow[i]->ChangeAnim(ANISTATE::LOOP, 0.1f);
			arrow[i]->visible = false;

			b_arrow_act[i] = false;
		}
	}
	state = STATE::NONE;
	time_random = RESET_INT_STATE;
	time_respawn = RESPAWN_COOL;
	time_atk_cool = ATTACK_COOL;
}

Enemy::~Enemy()
{
	SafeDelete(col);
	SafeDelete(atk1_col);
	SafeDelete(atk2_col);
	SafeDelete(idle);
	SafeDelete(run);
	SafeDelete(jump);
	SafeDelete(fall);
	SafeDelete(hit);
	SafeDelete(death);
	SafeDelete(attack1);
	SafeDelete(attack2);
	SafeDelete(magic);
	for (int i = 0; i < 5; i++) {
		SafeDelete(arrow[i]);
		SafeDelete(arrow_col[i]);
	}
}

void Enemy::Action(Vector2 player)
{
	if (type == Enemy_Type::Huntress) {
		for (int i = 0; i < 5; i++) {
			if (arrow[i]->visible) {
				if (!arrow[i]->reverseLR) {
					arrow_col[i]->MoveWorldPos(Vector2(250.0f, 0.0f) * DELTA);
					float v = arrow_col[i]->GetWorldPos().x - player.x;
					if (v < 0.0f) v *= -1.0f;
					if (v < App.GetHalfWidth()) {
						arrow[i]->visible = false;
						b_arrow_act[i] = false;
					}
				}
				else if (arrow[i]->reverseLR) {
					arrow_col[i]->MoveWorldPos(Vector2(-250.0f, 0.0f) * DELTA);
					if (arrow[i]->GetWorldPos().x > App.GetHalfWidth() || arrow[i]->GetWorldPos().x < -App.GetHalfWidth()) {
						arrow[i]->visible = false;
						b_arrow_act[i] = false;
					}
				}
			}
		}
	}
	if (!b_dead) {
		float dir = col->GetWorldPos().x - player.x;
		if (type == Enemy_Type::Huntress) {
			if (attack1->frame.x == attack1->maxFrame.x - 1) {
				for (int i = 0; i < 5; i++) {
					if (!arrow[i]->visible) {
						arrow_col[i]->SetWorldPos(col->GetWorldPos());
						arrow[i]->reverseLR = attack1->reverseLR;
						arrow[i]->visible = true;
						b_arrow_act[i] = true;
						attack1->frame.x = 0;
						break;
					}
				}
				Change_State(STATE::IDLE);
			}
		}
		else if (attack1->frame.x == attack1->maxFrame.x - 3) {
			b_act_atk1 = true;
		}
		else if (attack1->frame.x == attack1->maxFrame.x - 1) {
			b_act_atk1 = false;
			Change_State(STATE::IDLE);
		}
		// 무작위 행동
		time_random -= DELTA;
		if (time_random < 0.0f) {
			rd_fatrol = RANDOM->Int(0, 4);
			time_random = RESET_INT_STATE;
			time_atk_cool = ATTACK_COOL;
			if (dir > 0.0f) b_power_dir = true;
			else b_power_dir = false;
		}
		if (state != STATE::ATTACK1) {
			// 피격상태가 아닐 시
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
					// 가만히 있기
					Change_State(STATE::IDLE);
					if (idle->reverseLR == true) {
						if (dir < 100.0f && time_atk_cool < 0.0f) {
							if (type == Enemy_Type::Warrior) {
								atk1_col->SetLocalPosX(-20.0f);
							}
							else if (type == Enemy_Type::Wizard) {
								atk1_col->SetLocalPos(Vector2(-50.0f, 30.0f));
							}
							attack1->reverseLR = true;
							Change_State(STATE::ATTACK1);
							time_atk_cool = ATTACK_COOL;
						}
						else {
							time_atk_cool -= DELTA;
						}
					}
					else {
						if (dir > -100.0f && time_atk_cool < 0.0f) {
							if (type == Enemy_Type::Warrior) {
								atk1_col->SetLocalPosX(20.0f);
							}
							else if (type == Enemy_Type::Wizard) {
								atk1_col->SetLocalPosX(40.0f);
							}
							attack1->reverseLR = false;
							Change_State(STATE::ATTACK1);
							time_atk_cool = ATTACK_COOL;
						}
						else {
							time_atk_cool -= DELTA;
						}
					}
					Change_State(STATE::IDLE);
					break;
				case 1:
				case 2:
				case 3:
					// 플레이어에게 이동 후 공격
					if (type == Enemy_Type::Huntress) {
						time_atk_cool -= DELTA;
						if (run->reverseLR == true) {
							if (dir < 300.0f && time_atk_cool < 0.0f) {
								attack1->reverseLR = true;
								Change_State(STATE::ATTACK1);
								time_atk_cool = ATTACK_COOL;
							}
							else if (dir < 300.0f) {
								Change_State(STATE::IDLE);
							}
							else {
								col->MoveWorldPos(Vector2(-150.0f * DELTA, 0.0f));
								Change_State(STATE::RUN);
							}
						}
						else {
							if (dir > -300.0f && time_atk_cool < 0.0f) {
								attack1->reverseLR = false;
								Change_State(STATE::ATTACK1);
								time_atk_cool = ATTACK_COOL;
							}
							else if (dir > -300.0f) {
								Change_State(STATE::IDLE);
							}
							else {
								col->MoveWorldPos(Vector2(150.0f * DELTA, 0.0f));
								Change_State(STATE::RUN);
							}
						}
					} else
					if (run->reverseLR == true) {
						if (dir < 100.0f && time_atk_cool < 0.0f) {
							if (type == Enemy_Type::Warrior) {
								atk1_col->SetLocalPosX(-20.0f);
							}
							else if (type == Enemy_Type::Wizard) {
								atk1_col->SetLocalPos(Vector2(-50.0f, 30.0f));
							}
							attack1->reverseLR = true;
							Change_State(STATE::ATTACK1);
							time_atk_cool = ATTACK_COOL;
						}
						else {
							if (dir > 50) {
								col->MoveWorldPos(Vector2(-180.0f * DELTA, 0.0f));
								Change_State(STATE::RUN);
							}
							else {
								Change_State(STATE::IDLE);
							}
							time_atk_cool -= DELTA;
						}
					}
					else {
						if (dir > -100.0f && time_atk_cool < 0.0f) {
							if (type == Enemy_Type::Warrior) {
								atk1_col->SetLocalPosX(20.0f);
							}
							else if (type == Enemy_Type::Wizard) {
								atk1_col->SetLocalPosX(40.0f);
							}
							attack1->reverseLR = false;
							Change_State(STATE::ATTACK1);
							time_atk_cool = ATTACK_COOL;
						}
						else {
							if (dir < -50) {
								col->MoveWorldPos(Vector2(180.0f * DELTA, 0.0f));
								Change_State(STATE::RUN);
							}
							else {
								Change_State(STATE::IDLE);
							}
							time_atk_cool -= DELTA;
						}
					}
					break;
				case 4:
					// 클래스별 특수행동
					if (type == Enemy_Type::Huntress) Change_State(STATE::IDLE);
					else Power_Attack(player);
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
		rd_fatrol = 0;
	}
}

void Enemy::Hit(int dmg)
{
	if (!b_dead && !b_invicible) {
		b_act_atk1 = false;
		b_act_atk2 = false;
		Status::Hit(dmg);
		Change_State(STATE::Hit);
	}
}

void Enemy::Change_State(STATE ps)
{
	if (state != ps) {
		state = ps;
		if (state == STATE::IDLE) {
			cout << name << " 가만히있기" << endl;
			idle->ChangeAnim(ANISTATE::LOOP, 0.1f);
			idle->visible = true;
		}
		else {
			idle->frame.x = 0;
			idle->visible = false;
		}

		if (state == STATE::RUN) {
			cout << name << " 움직이기" << endl;
			run->visible = true;
		}
		else {
			run->frame.x = 0;
			run->visible = false;
		}

		if (state == STATE::ATTACK1) {
			cout << name << "공격" << endl;
			if (type == Enemy_Type::Warrior) attack1->ChangeAnim(ANISTATE::ONCE, 0.2f);
			else if (type == Enemy_Type::Wizard) attack1->ChangeAnim(ANISTATE::ONCE, 0.1f);
			attack1->visible = true;
		}
		else {
			attack1->frame.x = 0;
			attack1->visible = false;
		}

		if (state == STATE::ATTACK2) {
			cout << name << "특수공격" << endl;
			// 전사 특수공격
			if (type == Enemy_Type::Warrior) attack2->ChangeAnim(ANISTATE::LOOP, 0.25f);
			// 법사 특수공격
			else if (type == Enemy_Type::Wizard) {
				attack2->ChangeAnim(ANISTATE::ONCE, 0.15f);
				magic->color.A(0.0f);
				magic->frame.x = 0;
				magic->visible = true;
			}
			// 활쟁이 특수공격
			else if (type == Enemy_Type::Huntress) {

			}
			attack2->visible = true;
		}
		else {
			if (type == Enemy_Type::Warrior) b_act_atk2 = false;
			attack2->frame.x = 0;
			attack2->visible = false;
			if (type == Enemy_Type::Wizard) {
				magic->visible = false;
			}
		}
		if (state == STATE::Hit) {
			cout << name << " 데미지받음" << endl;
			hit->ChangeAnim(ANISTATE::ONCE, 0.2f);
			hit->visible = true;
		}
		else {
			hit->frame.x = 0;
			hit->visible = false;
		}

		if (state == STATE::Death) {
			death->ChangeAnim(ANISTATE::ONCE, 0.2f);
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
	if (time_respawn < 1.2f) death->color.A(RANDOM->Float(0.0f, 0.5f));
	if (time_respawn < 0.0f) {
		int rdpos = RANDOM->Int(0, 1);
		time_respawn = RESPAWN_COOL;
		if (rdpos == 0) col->SetWorldPosX(pos.x + 500.0f);
		else col->SetWorldPosX(pos.x - 500.0f);
		death->color.A(0.5f);
		Set_Defalut_Status();
		time_random = 0.0f;
		Change_State(STATE::IDLE);
	}
}

void Enemy::Update()
{
	col->Update();
	if (type != Enemy_Type::Huntress) atk1_col->Update();
	if (type != Enemy_Type::Huntress) atk2_col->Update();

	idle->Update();
	run->Update();
	attack1->Update();
	attack2->Update();
	hit->Update();
	death->Update();
	if (type == Enemy_Type::Wizard) magic->Update();
	if (type == Enemy_Type::Huntress)
		for (int i = 0; i < 5; i++) {
			arrow[i]->Update();
			arrow_col[i]->Update();
		}
}

void Enemy::Render()
{
	/*col->Render();
	if (type != Enemy_Type::Huntress) atk1_col->Render();
	if (type != Enemy_Type::Huntress) atk2_col->Render();*/
	idle->Render();
	run->Render();
	attack1->Render();
	attack2->Render();
	hit->Render();
	death->Render();
	if (type == Enemy_Type::Wizard) magic->Render();
	if (type == Enemy_Type::Huntress)
		for (int i = 0; i < 5; i++) {
			arrow[i]->Render();
			// arrow_col[i]->Render();
		}
}

void Enemy::Power_Attack(Vector2 pos)
{
	if (b_power_dir) attack2->reverseLR = true;
	else attack2->reverseLR = false;
	if (type == Enemy_Type::Warrior) {
		if (time_random < 1.3f) {
			Change_State(STATE::ATTACK2);
			b_act_atk2 = true;
			if (!b_power_dir) {
				col->MoveWorldPos(Vector2(350.0f, 0.0f) * DELTA);
			}
			else {
				col->MoveWorldPos(Vector2(-350.0f, 0.0f) * DELTA);
			}
		}
		else {
			Change_State(STATE::IDLE);
			idle->ChangeAnim(ANISTATE::STOP, 0.1f);
		}
	}
	else if (type == Enemy_Type::Wizard) {
		Change_State(STATE::ATTACK2);
		magic->color.A(magic->color.A() + DELTA * 0.5f);
		if (magic->color.A() < 0.2f) atk2_col->SetWorldPos(pos);
		if (magic->color.A() >= 0.5f) {
			magic->color.A(0.5f);
			b_act_atk2 = true;
		}
		else b_act_atk2 = false;
	}
}
