#include "stdafx.h"

Enemy::Enemy()
{
	col = new ObRect();

	col->scale = Vector2(100.0f, 100.0f);
	col->SetWorldPosY(300.0f);
}

Enemy::~Enemy()
{
	SafeDelete(col);
}

void Enemy::Update()
{
	col->Update();
	if (damagingTime > 0.0f)
	{
		damagingTime -= DELTA;
		col->color.w = RANDOM->Float(0.0f, 0.5f);
	}
	else
	{
		col->color.w = 0.5f;
	}
	
}

void Enemy::Render()
{
	col->Render();
}

void Enemy::TakeDamage(int damage)
{
	hp -= damage;
	damagingTime = 0.5f;
	if (hp < 0)
	{
		col->visible = false;
	}
}
