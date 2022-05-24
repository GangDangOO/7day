#pragma once
#define PLBULLET 30

struct Player
{
	ObImage *		LR;
	ObImage *		boost;
	ObRect *		col;
	bool			isBoosting;
	float			LRKey;
	Vector2			dir;
	PlayerBullet	bullet[PLBULLET];
	int				level;

	Player();
	~Player();
	void Update();
	void Render();
};

