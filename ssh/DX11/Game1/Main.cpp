#include "stdafx.h"
#include "Main.h"
void Main::Init()
{
	bg = new BackGround();
	player = new Player(100, 30, 5);
	warrior = new Enemy(Enemy_Type::Warrior, 100, 30, 0);
	wizard = new Enemy(Enemy_Type::Wizard, 100, 20, 0);

	warrior->col->SetWorldPos(Vector2(-300.0f, -300.0f));
	wizard->col->SetWorldPos(Vector2(300.0f, -300.0f));
}

void Main::Release()
{
	
}


void Main::Update()
{
	player->Fall_Down();
	player->Action();
	if (!player->b_dead) {
		warrior->Action(player->col->GetWorldPos());
		wizard->Action(player->col->GetWorldPos());
	}

	if (warrior->b_dead) warrior->Respawn(player->col->GetWorldPos());
	if (wizard->b_dead) wizard->Respawn(player->col->GetWorldPos());

	if (!player->b_act_atk1 && !player->b_act_atk2) {
		warrior->b_invicible = false;
		wizard->b_invicible = false;
	}

	bg->Update();
	player->Update();
	warrior->Update();
	wizard->Update();
}

void Main::LateUpdate()
{
	// 워리어 to 플레이어
	if (warrior->atk1_col->Intersect(player->col) && warrior->b_act_atk1) {
		player->Hit(warrior->Get_Dmg());
	}
	// 메이지 to 플레이어
	if (wizard->atk1_col->Intersect(player->col) && wizard->b_act_atk1) {
		player->Hit(wizard->Get_Dmg());
	}
	// 플레이어 to 워리어
	if(player->atk1_col->Intersect(warrior->col) && player->b_act_atk1) {
		warrior->Hit(player->Get_Dmg());
	}
	if (player->atk2_col->Intersect(warrior->col) && player->b_act_atk2) {
		warrior->Hit(player->Get_Dmg());
	}
	// 플레이어 to 메이지
	if (player->atk1_col->Intersect(wizard->col) && player->b_act_atk1) {
		wizard->Hit(player->Get_Dmg());
	}
	if (player->atk2_col->Intersect(wizard->col) && player->b_act_atk2) {
		wizard->Hit(player->Get_Dmg());
	}
}



void Main::Render()
{
	bg->Render();
	player->Render();
	warrior->Render();
	wizard->Render();
}

void Main::ResizeScreen()
{
}


int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game1");
	App.SetInstance(instance);
	App.InitWidthHeight(928.0f, 793.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}
