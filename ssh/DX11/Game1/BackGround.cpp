#include "stdafx.h"

BackGround::BackGround()
{
	bg[0] = new ObImage(L"Background_layers\\Layer_0011_0.png");
	bg[1] = new ObImage(L"Background_layers\\Layer_0010_1.png");
	bg[2] = new ObImage(L"Background_layers\\Layer_0009_2.png");
	bg[3] = new ObImage(L"Background_layers\\Layer_0008_3.png");
	bg[4] = new ObImage(L"Background_layers\\Layer_0006_4.png");
	bg[5] = new ObImage(L"Background_layers\\Layer_0005_5.png");
	bg[6] = new ObImage(L"Background_layers\\Layer_0003_6.png");
	bg[7] = new ObImage(L"Background_layers\\Layer_0002_7.png");
	bg[8] = new ObImage(L"Background_layers\\Layer_0001_8.png");
	bg[9] = new ObImage(L"Background_layers\\Layer_0000_9.png");
	for (int i = 0; i < 10; i++) {
		bg[i]->scale = Vector2(928.0f, 793.0f);
		bg[i]->space = SPACE::SCREEN;
	}
}

BackGround::~BackGround()
{
	for (int i = 0; i < 10; i++) {
		SafeDelete(bg[i]);
	}
}

void BackGround::Update()
{

	
	for (int i = 0; i < 10; i++) {
		bg[i]->uv.x = 0.0f + (CAM->position.x / 928.0f) * i * 0.1f;
		bg[i]->uv.z = 1.0f + (CAM->position.x / 928.0f) * i * 0.1f;
		bg[i]->Update();
	}
}

void BackGround::Render()
{
	for (int i = 0; i < 10; i++) {
		bg[i]->Render();
	}
}
