#include "stdafx.h"
#include "Main.h"
void Main::Init()
{
	bg = new BackGround();
	player = new Player(100, 2000, 5);
	warrior = new Enemy(Enemy_Type::Warrior, 100, 30, 0);
	wizard = new Enemy(Enemy_Type::Wizard, 100, 20, 0);
	huntress = new Enemy(Enemy_Type::Huntress, 100, 10, 0);

	warrior->col->SetWorldPos(Vector2(-300.0f, -300.0f));
	wizard->col->SetWorldPos(Vector2(300.0f, -290.0f));
	huntress->col->SetWorldPos(Vector2(400.0f, -300.0f));
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
		huntress->Action(player->col->GetWorldPos());
	}

	if (warrior->b_dead) warrior->Respawn(player->col->GetWorldPos());
	if (wizard->b_dead) wizard->Respawn(player->col->GetWorldPos());
	if (huntress->b_dead) huntress->Respawn(player->col->GetWorldPos());

	if (!player->b_act_atk1 && !player->b_act_atk2) {
		warrior->b_invicible = false;
		wizard->b_invicible = false;
		huntress->b_invicible = false;
	}

	bg->Update();
	player->Update();
	warrior->Update();
	wizard->Update();
	huntress->Update();
}

void Main::LateUpdate()
{
	// 워리어 to 플레이어
	if (!warrior->b_dead)
		if (warrior->atk1_col->Intersect(player->col) && warrior->b_act_atk1) {
			player->Hit(warrior->Get_Dmg());
		}
		else if (warrior->atk2_col->Intersect(player->col) && warrior->b_act_atk2) {
			if (warrior->col->GetWorldPos().x > player->col->GetWorldPos().x) player->Hit(warrior->Get_Dmg(), Vector2(-800.0f, 200.0f));
			else player->Hit(warrior->Get_Dmg(), Vector2(800.0f, 200.0f));
		}
	// 메이지 to 플레이어
	if (!wizard->b_dead)
		if (wizard->atk1_col->Intersect(player->col) && wizard->b_act_atk1) {
			player->Hit(wizard->Get_Dmg());
		}
	else if (wizard->atk2_col->Intersect(player->col) && wizard->b_act_atk2) {
		player->Hit(wizard->Get_Dmg());
	}
	// 아쳐 to 플레이어
	if (!huntress->b_dead)
		for (int i = 0; i < 5; i++) {
			if (huntress->arrow_col[i]->Intersect(player->col) && huntress->b_arrow_act[i]) {
				player->Hit(huntress->Get_Dmg());
				cout << "히트 " << huntress->b_arrow_act[i] << endl;
			}
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
	// 플레이어 to 아쳐
	if (player->atk1_col->Intersect(huntress->col) && player->b_act_atk1) {
		huntress->Hit(player->Get_Dmg());
	}
	if (player->atk2_col->Intersect(huntress->col) && player->b_act_atk2) {
		huntress->Hit(player->Get_Dmg());
	}
}



void Main::Render()
{
	bg->Render();
	player->Render();
	warrior->Render();
	wizard->Render();
	huntress->Render();
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
