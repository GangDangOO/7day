#include "stdafx.h"
#include "Main.h"
void Main::Init()
{
	bg = new BackGround();
	player = new Player(100, 10, 5);
	warrior = new Enemy(Enemy_Type::Warrior, 100, 10, 0);
	wizard = new Enemy(Enemy_Type::Wizard, 100, 10, 0);

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
	warrior->Action();
	wizard->Action();

	if (!player->b_act_atk1 && !player->b_act_atk2) {
		warrior->Invicible_Off();
		wizard->Invicible_Off();
	}

	bg->Update();
	player->Update();
	warrior->Update();
	wizard->Update();
}

void Main::LateUpdate()
{
	if(player->atk1_col->Intersect(warrior->col) && player->b_act_atk1) {
		warrior->Hit(player->Get_Dmg());
	}
	if (player->atk2_col->Intersect(warrior->col) && player->b_act_atk2) {
		warrior->Hit(player->Get_Dmg());
	}
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
