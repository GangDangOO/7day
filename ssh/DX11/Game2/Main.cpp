#include "stdafx.h"
#include "Main.h"

void Main::Init()
{
	/*coin = new ObImage(L"coin.bmp");
	coin->scale = Vector2(500, 500);*/

	pl = new Player();

	sonic = new ObImage(L"run.bmp");
	sonic->scale = Vector2(100.0f, 200.0f) ;
	sonic->space = SPACE::SCREEN;
	sonic->maxFrame.x = 4;
	sonic->ChangeAnim(ANISTATE::LOOP, 0.1f);
	sonic->collider = COLLIDER::RECT;

	sonic->SetWorldPos(Vector2(100.f, 100.0f));
}

void Main::Release()
{
}


void Main::Update()
{
	ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
	ImGui::SliderAngle("rotation", &sonic->rotation);
	if (ImGui::Button("reverseLR"))
	{
		sonic->reverseLR = !sonic->reverseLR;
	}
	if (sonic->IntersectScreenMouse(INPUT->GetMouseScreenPos()))
	{
		sonic->color.w = RANDOM->Float(0.0f, 0.5f);
	}
	
	sonic->Update();
}

void Main::LateUpdate()
{

}
void Main::Render()
{
	sonic->Render();
}

void Main::ResizeScreen()
{

}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    App.SetAppName(L"Game2");
    App.SetInstance(instance);
	App.InitWidthHeight(224.0f*2.0f, 800.0f);
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	WIN->DeleteSingleton();
	SafeDelete(main);
	return wParam;
}
