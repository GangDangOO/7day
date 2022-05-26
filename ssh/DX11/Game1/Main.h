#pragma once

class Main : public Scene
{
private:
	BackGround* bg;
	Player*		player;
	Enemy*		warrior;
	Enemy*		wizard;
	Enemy*		huntress;
public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;

};
