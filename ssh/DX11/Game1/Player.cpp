#include "stdafx.h"

Player::Player(int hp, int dmg, int def) : Status(hp, dmg, def){

	col = new ObRect();
	col->isFilled = false;
	col->scale = Vector2(1980.0f / 11, 180.0f) / 3;
	col->SetWorldPos(Vector2(0.0f, 0.0f));

	idle = new ObImage(L"Player\\Idle.png");
	idle->scale = Vector2(1980.0f / 11, 180.0f) * 1.5f;
	idle->maxFrame.x = 11;
	idle->ChangeAnim(ANISTATE::LOOP, 0.1f);
	idle->frame.x = 0;
	idle->SetParentRT(*col);

	run = new ObImage(L"Player\\Run.png");
	run->scale = Vector2(1440.0f / 8, 180.0f) * 1.5f;
	run->maxFrame.x = 8;
	run->ChangeAnim(ANISTATE::LOOP, 0.1f);
	run->frame.x = 0;
	run->SetParentRT(*col);

	jump = new ObImage(L"Player\\Jump.png");
	jump->scale = Vector2(540.0f / 3, 180.0f) * 1.5f;
	jump->maxFrame.x = 3;
	jump->ChangeAnim(ANISTATE::LOOP, 0.1f);
	jump->frame.x = 0;
	jump->SetParentRT(*col);

	fall = new ObImage(L"Player\\Fall.png");
	fall->scale = Vector2(540.0f / 3, 180.0f) * 1.5f;
	fall->maxFrame.x = 3;
	fall->ChangeAnim(ANISTATE::LOOP, 0.1f);
	fall->frame.x = 0;
	fall->SetParentRT(*col);

	attack1 = new ObImage(L"Player\\Attack1.png");
	attack1->scale = Vector2(1260.0f / 7, 180.0f) * 1.5f;
	attack1->maxFrame.x = 7;
	attack1->ChangeAnim(ANISTATE::ONCE, 0.1f);
	attack1->frame.x = 0;
	attack1->SetParentRT(*col);

	attack2 = new ObImage(L"Player\\Attack2.png");
	attack2->scale = Vector2(1260.0f / 7, 180.0f) * 1.5f;
	attack2->maxFrame.x = 7;
	attack2->ChangeAnim(ANISTATE::ONCE, 0.1f);
	attack2->frame.x = 0;
	attack2->SetParentRT(*col);

	hit = new ObImage(L"Player\\Take_Hit.png");
	hit->scale = Vector2(1260.0f / 4, 180.0f) * 1.5f;
	hit->maxFrame.x = 4;
	hit->ChangeAnim(ANISTATE::ONCE, 0.1f);
	hit->frame.x = 0;
	hit->SetParentRT(*col);

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
}

void Player::Action()
{
	// 공격
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
	} else if (state == STATE::ATTACK1 && attack1->frame.x == attack1->maxFrame.x - 4) {
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
		}
		else {
			if (b_jump && state != STATE::IDLE) Change_State(STATE::IDLE);
			move.x = 0.0f;
		}
		if (INPUT->KeyDown(VK_SPACE) && b_jump) {
			Change_State(STATE::JUMP);
			move.y = 300.0f;
			b_jump = false;
		}
	}
	CAM->position.x += move.x * DELTA;
	col->MoveWorldPos(move * DELTA);
}

void Player::Fall_Down()
{
	if (col->GetWorldPos().y > -300.0f) {
		gravity += 400.0f * DELTA;
		if (gravity > move.y && state != STATE::FALL && b_attack) {
			Change_State(STATE::FALL);
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
		attack1->frame.x = 0;
		attack1->visible = true;
	}
	else {
		b_act_atk1 = false;
		attack1->visible = false;
	}
	if (state == STATE::ATTACK2) {
		attack2->frame.x = 0;
		attack2->visible = true;
	}
	else {
		b_act_atk2 = false;
		attack2->visible = false;
	}
	if (state == STATE::Hit) {
		hit->frame.x = 0;
		hit->visible = true;
	}
	else hit->visible = false;
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
	// cout << attack2->frame.x << endl;
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
}
