#include "stdafx.h"

Player::Player(int hp, int dmg, int def) : Status(hp, dmg, def){
	name = "Player";
	col = new ObRect();
	col->isFilled = false;
	col->scale = Vector2(180.0f, 180.0f) / 3;
	col->SetWorldPos(Vector2(0.0f, 0.0f));

	idle = new ObImage(L"Player\\Idle.png");
	idle->scale = Vector2(180.0f, 180.0f) * 1.5f;
	idle->maxFrame.x = 11;
	idle->ChangeAnim(ANISTATE::LOOP, 0.1f);
	idle->frame.x = 0;
	idle->SetParentRT(*col);
	cout << idle->color.A() << endl;

	run = new ObImage(L"Player\\Run.png");
	run->scale = Vector2(180.0f, 180.0f) * 1.5f;
	run->maxFrame.x = 8;
	run->ChangeAnim(ANISTATE::LOOP, 0.1f);
	run->frame.x = 0;
	run->SetParentRT(*col);

	jump = new ObImage(L"Player\\Jump.png");
	jump->scale = Vector2(180.0f, 180.0f) * 1.5f;
	jump->maxFrame.x = 3;
	jump->ChangeAnim(ANISTATE::LOOP, 0.1f);
	jump->frame.x = 0;
	jump->SetParentRT(*col);

	fall = new ObImage(L"Player\\Fall.png");
	fall->scale = Vector2(180.0f, 180.0f) * 1.5f;
	fall->maxFrame.x = 3;
	fall->ChangeAnim(ANISTATE::LOOP, 0.1f);
	fall->frame.x = 0;
	fall->SetParentRT(*col);

	attack1 = new ObImage(L"Player\\Attack1.png");
	attack1->scale = Vector2(180.0f, 180.0f) * 1.5f;
	attack1->maxFrame.x = 7;
	attack1->ChangeAnim(ANISTATE::ONCE, 0.1f);
	attack1->frame.x = 0;
	attack1->SetParentRT(*col);

	attack2 = new ObImage(L"Player\\Attack2.png");
	attack2->scale = Vector2(180.0f, 180.0f) * 1.5f;
	attack2->maxFrame.x = 7;
	attack2->ChangeAnim(ANISTATE::ONCE, 0.1f);
	attack2->frame.x = 0;
	attack2->SetParentRT(*col);

	hit = new ObImage(L"Player\\Take_Hit.png");
	hit->scale = Vector2(180.0f, 180.0f) * 1.5f;
	hit->maxFrame.x = 4;
	hit->ChangeAnim(ANISTATE::ONCE, 0.2f);
	hit->frame.x = 0;
	hit->SetParentRT(*col);

	death = new ObImage(L"Player\\Death.png");
	death->scale = Vector2(180.0f, 180.0f) * 1.5f;
	death->maxFrame.x = 11;
	death->frame.x = 0;
	death->ChangeAnim(ANISTATE::ONCE, 0.2f);
	death->SetParentRT(*col);

	atk1_col = new ObRect();
	atk1_col->scale = Vector2(40.0f, 100.0f);
	atk1_col->isFilled = false;
	atk1_col->SetParentRT(*col);

	atk2_col = new ObRect();
	atk2_col->scale = Vector2(80.0f, 120.0f);
	atk2_col->isFilled = false;
	atk2_col->SetParentRT(*col);

	speed = 200.0f;
	move = Vector2(0.0f, 0.0f);
	cooltime_attack = 0.0f;
	b_jump = true;
	b_attack = true;
	b_act_atk1 = false;
	b_act_atk2 = false;
	b_hit = false;
	time_invicible = INVICIBLE_TIME;
}

Player::~Player() {
	SafeDelete(col);
	SafeDelete(idle);
	SafeDelete(run);
	SafeDelete(jump);
	SafeDelete(fall);
	SafeDelete(attack1);
	SafeDelete(attack2);
	SafeDelete(atk1_col);
	SafeDelete(atk2_col);
	SafeDelete(hit);
	SafeDelete(death);
}

void Player::Action()
{
	// 공격
	if (!b_dead) {
		if (!b_hit) {
			Invicible_Time();
			if (INPUT->KeyDown(VK_LCONTROL) && b_attack) {
				if (b_jump) {
					Change_State(STATE::ATTACK1);
					move.x = 0.0f;
				}
				else {
					Change_State(STATE::ATTACK2);
				}
				b_attack = false;
			}
			if (state == STATE::ATTACK1 && attack1->frame.x == attack1->maxFrame.x - 1) {
				b_attack = true;
			}
			else if (state == STATE::ATTACK1 && attack1->frame.x == attack1->maxFrame.x - 4) {
				b_act_atk1 = true;
			}
			if (state == STATE::ATTACK2 && attack2->frame.x == attack2->maxFrame.x - 4) {
				b_act_atk2 = true;
				move = Vector2(0.0f, 0.0f);
			}
			// 이동
			if (b_attack) {
				if (INPUT->KeyDown('A')) {
					if (b_jump && state != STATE::RUN) {
						Change_State(STATE::RUN);
					}
				}
				else if (INPUT->KeyDown('D')) {
					if (b_jump && state != STATE::RUN) {
						Change_State(STATE::RUN);
					}
				}
				if (INPUT->KeyPress('A')) {
					if ((b_jump && state == STATE::FALL) ||
						(b_jump && state == STATE::ATTACK1) ||
						(b_jump && state == STATE::ATTACK2)) Change_State(STATE::RUN);
					atk1_col->SetLocalPos(Vector2(-40.0f, 10.0f));
					atk2_col->SetLocalPos(Vector2(-80.0f, 20.0f));
					move.x = -speed;
					run->reverseLR = true;
					idle->reverseLR = true;
					jump->reverseLR = true;
					fall->reverseLR = true;
					attack1->reverseLR = true;
					attack2->reverseLR = true;
					hit->reverseLR = true;
					death->reverseLR = true;
				}
				else if (INPUT->KeyPress('D')) {
					if ((b_jump && state == STATE::FALL) ||
						(b_jump && state == STATE::ATTACK1) ||
						(b_jump && state == STATE::ATTACK2)) Change_State(STATE::RUN);
					atk1_col->SetLocalPos(Vector2(40.0f, 10.0f));
					atk2_col->SetLocalPos(Vector2(80.0f, 20.0f));

					move.x = speed;
					run->reverseLR = false;
					idle->reverseLR = false;
					jump->reverseLR = false;
					fall->reverseLR = false;
					attack1->reverseLR = false;
					attack2->reverseLR = false;
					hit->reverseLR = false;
					death->reverseLR = false;
				}
				else {
					if (b_jump) Change_State(STATE::IDLE);
					move.x = 0.0f;
				}
				if (INPUT->KeyDown(VK_SPACE) && b_jump) {
					Change_State(STATE::JUMP);
					move.y = 300.0f;
					b_jump = false;
				}
			}
		}
		else if (hit->frame.x == hit->maxFrame.x - 1) {
			hit->frame.x = 0;
			b_hit = false;
			if (!INPUT->KeyPress('A') && !INPUT->KeyPress('D')) Change_State(STATE::IDLE);
			else Change_State(STATE::RUN);
		}
	}
	else {
		Change_State(STATE::Death);
	}
	CAM->position.x += move.x * DELTA;
	col->MoveWorldPos(move * DELTA);
}

void Player::Fall_Down()
{
	if (col->GetWorldPos().y > -300.0f) {
		gravity += 400.0f * DELTA;
		if (gravity > move.y && b_attack) {
			if (state != STATE::Hit) Change_State(STATE::FALL);
		}
		b_jump = false;
		col->MoveWorldPos(Vector2(0.0f, -1.0f) * gravity * DELTA);
	}
	else {
		if (state == STATE::ATTACK2) b_attack = true;
		gravity = 0.0f;
		move.y = 0.0f;
		if (!b_jump) {
			col->SetWorldPosY(-300.0f);
			b_jump = true;
		}
	}
}

void Player::Change_State(STATE ps)
{
	if (state != ps) {
		state = ps;
		if (state == STATE::IDLE) {
			idle->frame.x = 0;
			idle->visible = true;
		}
		else idle->visible = false;
		if (state == STATE::RUN) {
			run->frame.x = 0;
			run->visible = true;
		}
		else run->visible = false;
		if (state == STATE::JUMP) {
			jump->frame.x = 0;
			jump->visible = true;
		}
		else jump->visible = false;
		if (state == STATE::FALL) {
			fall->frame.x = 0;
			fall->visible = true;
		}
		else fall->visible = false;
		if (state == STATE::ATTACK1) {
			attack1->ChangeAnim(ANISTATE::ONCE, 0.1f);
			attack1->frame.x = 0;
			attack1->visible = true;
		}
		else {
			b_act_atk1 = false;
			attack1->visible = false;
		}
		if (state == STATE::ATTACK2) {
			attack2->ChangeAnim(ANISTATE::ONCE, 0.1f);
			attack2->frame.x = 0;
			attack2->visible = true;
		}
		else {
			b_act_atk2 = false;
			attack2->visible = false;
		}
		if (state == STATE::Hit) {
			hit->ChangeAnim(ANISTATE::ONCE, 0.2f);
			hit->frame.x = 0;
			hit->visible = true;
		}
		else hit->visible = false;
		if (state == STATE::Death) {
			death->ChangeAnim(ANISTATE::ONCE, 0.2f);
			death->frame.x = 0;
			death->visible = true;
		}
		else death->visible = false;
	}
}

void Player::Invicible_Time()
{
	if (b_invicible) {
		time_invicible -= DELTA;
		if (time_invicible < 0.0f) {
			time_invicible = INVICIBLE_TIME;
			b_invicible = false;
			idle->color.A(0.5f);
			run->color.A(0.5f);
			jump->color.A(0.5f);
			fall->color.A(0.5f);
			attack1->color.A(0.5f);
			attack2->color.A(0.5f);
		}
		else {
			idle->color.A(RANDOM->Float(0.0f, 0.5f));
			run->color.A(RANDOM->Float(0.0f, 0.5f));
			jump->color.A(RANDOM->Float(0.0f, 0.5f));
			fall->color.A(RANDOM->Float(0.0f, 0.5f));
			attack1->color.A(RANDOM->Float(0.0f, 0.5f));
			attack2->color.A(RANDOM->Float(0.0f, 0.5f));
		}
	}
}

void Player::Hit(int dmg)
{
	if (!b_dead && !b_invicible) {
		b_attack = true;
		b_hit = true;
		move.x = 0.0f;
		Status::Hit(dmg);
		Change_State(STATE::Hit);
	}
}

void Player::Hit(int dmg, Vector2 power)
{
	if (!b_dead && !b_invicible) {
		move = power;
		col->SetWorldPosY(-299.0f);
		b_attack = true;
		b_hit = true;
		Status::Hit(dmg);
		Change_State(STATE::Hit);
	}
}

void Player::Update()
{
	col->Update();
	atk1_col->Update();
	atk2_col->Update();
	idle->Update();
	run->Update();
	jump->Update();
	fall->Update();
	attack1->Update();
	attack2->Update();
	hit->Update();
	death->Update();
}

void Player::Render()
{
	col->Render();
	atk1_col->Render();
	atk2_col->Render();
	if (idle->visible) idle->Render();
	if (run->visible) run->Render();
	if (jump->visible) jump->Render();
	if (fall->visible) fall->Render();
	if (attack1->visible) attack1->Render();
	if (attack2->visible) attack2->Render();
	if (hit->visible) hit->Render();
	if (death->visible) death->Render();
}
