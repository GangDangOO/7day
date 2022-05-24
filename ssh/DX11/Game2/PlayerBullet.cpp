#include "stdafx.h"

PlayerBullet::PlayerBullet()
{
	col->scale.x = 100.0f;
	col->scale.y = 50.0f;

	for (int i = 0; i < 3; i++)
	{
		PB[i] = new ObImage(L"PlayeBullet.png");
		PB[i]->SetParentRT(*col);
		PB[i]->maxFrame.x = 4;
		PB[i]->ChangeAnim(ANISTATE::LOOP, 0.1f);
	}
	col->scale.x = 50.0f;
	PB[1]->visible = false;
	PB[2]->visible = false;
	PB[0]->scale.x = 50.0f;
	PB[0]->scale.y = 100.0f;
	PB[1]->scale.x = 50.0f;
	PB[1]->scale.y = 100.0f;
	PB[2]->scale.x = 50.0f;
	PB[2]->scale.y = 100.0f;
	level = 0;
}

PlayerBullet::~PlayerBullet()
{
	SafeDelete(PB[0]);
}


void PlayerBullet::Update()
{
	ShootingBullet::Update();
	if (not fire) return;
	PB[0]->Update();
	PB[1]->Update();
	PB[2]->Update();
}

void PlayerBullet::Render()
{
	ShootingBullet::Render();
	if (not fire) return;
	PB[0]->Render();
	PB[1]->Render();
	PB[2]->Render();
}

void PlayerBullet::ChangeLevel(int level)
{
	if (level == 0)
	{
		col->scale.x = 50.0f;
		damage = 10;
		PB[0]->visible = true;
		PB[0]->SetLocalPos(Vector2(0.0f, 0.0f));
		PB[1]->visible = false;
		PB[2]->visible = false;
	}
	else if (level == 1)
	{
		col->scale.x = 100.0f;
		damage = 20;
		PB[0]->visible = true;
		PB[0]->SetLocalPos(Vector2(-25.0f, 0.0f));
		PB[1]->visible = true;
		PB[1]->SetLocalPos(Vector2(25.0f, 0.0f));
		PB[2]->visible = false;
	}
	else if (level == 2)
	{
		col->scale.x = 150.0f;
		damage = 30;
		PB[0]->visible = true;
		PB[0]->SetLocalPos(Vector2(0.0f, 0.0f));
		PB[1]->visible = true;
		PB[1]->SetLocalPos(Vector2(-50.0f, 0.0f));
		PB[2]->visible = true;
		PB[2]->SetLocalPos(Vector2(50.0f, 0.0f));
	}
}
