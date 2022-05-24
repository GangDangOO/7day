#include "stdafx.h"
#include "Main.h"
void Main::Init()
{
	bg = new BackGround();
	player = new Player(100, 10, 5);
	enemy = new Enemy(Enemy_Type::Warrior, 100, 10, 0);
	cout << enemy->Get_Hp() << endl;
}

void Main::Release()
{
	
}


void Main::Update()
{
	player->Fall_Down();
	player->Action();
	enemy->Action();

	if (!player->b_act_atk1 && !player->b_act_atk2) {
		enemy->Invicible_Off();
	}

	bg->Update();
	player->Update();
	enemy->Update();
}

void Main::LateUpdate()
{
	if(player->atk1_col->Intersect(enemy->col) && player->b_act_atk1) {
		enemy->Hit(player->Get_Dmg());
	}
	if (player->atk2_col->Intersect(enemy->col) && player->b_act_atk2) {
		enemy->Hit(player->Get_Dmg());
	}
}



void Main::Render()
{
	bg->Render();
	player->Render();
	enemy->Render();
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
