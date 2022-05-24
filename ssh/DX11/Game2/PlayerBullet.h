#pragma once
class PlayerBullet : public ShootingBullet
{
private:
	int			level;
public:
	ObImage * PB[3];
	
	PlayerBullet();
	~PlayerBullet();

	virtual void Update()override;
	virtual void Render()override;

	int  GetLevel() { return level; }
	void ChangeLevel(int level);
};

