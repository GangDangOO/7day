#include "stdafx.h"

ShootingBullet::ShootingBullet()
{
	col = new ObRect();
	col->isFilled = false;
	fire = false;
	damage = 0.0f;
}

ShootingBullet::~ShootingBullet()
{
	SafeDelete(col);
}

bool ShootingBullet::Shoot(Vector2 firePos, Vector2 fireDir, float fireForce)
{
	if (!fire)
	{
		fire = true;

		//발사시점에서 플레이어 위치를 받아온다.
		col->SetWorldPos(firePos);
		this->fireDir = fireDir;
		this->scalar = fireForce;
		return true;
	}
	return false;
}

void ShootingBullet::Update()
{
	if (not fire) return;
	Vector2 Velocity = fireDir * scalar;
	col->MoveWorldPos(fireDir * scalar * DELTA);
	col->rotation = Util::DirToRadian(Velocity) - DIV2PI;

	col->Update();
}

void ShootingBullet::Render()
{
	col->Render();
}
