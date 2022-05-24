#pragma once
class BackGround
{
private:
	ObImage* bg[10];
public:
	BackGround();
	~BackGround();
	void Update();
	void Render();
};

