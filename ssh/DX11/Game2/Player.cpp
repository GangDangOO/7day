#include "stdafx.h"


Player::Player()
{
	col = new ObRect();
	col->pivot = OFFSET_T;
	col->isFilled = false;
	col->scale = Vector2(224.0f / 7.0f, 40.0f) * 2.5f;

	LR = new ObImage(L"LeftRight.png");
	LR->scale = Vector2(224.0f / 7.0f, 40.0f) * 2.5f;
	LR->pivot = OFFSET_T;
	LR->maxFrame.x = 7;
	LR->SetParentRT(*col);

	boost = new ObImage(L"Start.png");
	boost->scale = Vector2(352.0f / 11.0f, 120.0f) * 2.5f;
	boost->pivot = OFFSET_T;
	boost->maxFrame.x = 11;
	boost->ChangeAnim(ANISTATE::LOOP, 0.1f);
	boost->visible = false;
	boost->SetParentRT(*col);
	isBoosting = false;

	LRKey = 0.0f;
	level = 0;
}

Player::~Player()
{
	SafeDelete(col);
	SafeDelete(LR);
	SafeDelete(boost);
}

void Player::Update()
{
	ImGui::SliderFloat("PlayerAlpha", &LR->color.w, 0.0, 1.0);
	ImGui::SliderInt("PlayerLevel", &level, 0, 2);

	//LR->color.w = RANDOM->Float(0.0f, 0.5f);

	dir = Vector2(0.0f, 0.0f);
	if (INPUT->KeyPress(VK_LEFT))
	{
		LRKey -= DELTA * 3.0f;
		LRKey = Util::saturate(LRKey, -3.0f, 3.0f);
		dir.x = -1.0f;
	}
	else if (INPUT->KeyPress(VK_RIGHT))
	{
		LRKey += DELTA * 3.0f;
		LRKey = Util::saturate(LRKey, -3.0f, 3.0f);
		dir.x = 1.0f;
	}
	else
	{
		if (LRKey < -DELTA * 1.5f)
		{
			LRKey += DELTA * 1.5f;
		}
		else if (LRKey > DELTA * 1.5f)
		{
			LRKey -= DELTA * 1.5f;
		}
		else
		{
			LRKey = 0.0f;
		}
	}


	if (INPUT->KeyPress(VK_UP))
	{
		dir.y = 1.0f;
	}
	else if (INPUT->KeyPress(VK_DOWN))
	{
		dir.y = -1.0f;
	}

	if (INPUT->KeyPress(VK_SPACE))
	{
		if (not isBoosting)
		{
			boost->frame.x = 0;
			boost->visible = true;
			LR->visible = false;
		}
		isBoosting = true;
		App.deltaScale = 3.0f;
	}
	else
	{
		if (isBoosting)
		{
			boost->visible = false;
			LR->visible = true;
			LRKey = 0.0f;
		}
		isBoosting = false;
		App.deltaScale = 1.0f;
	}
	if (INPUT->KeyDown(VK_LCONTROL))
	{
		for (int i = 0; i < PLBULLET; i++)
		{
			if (!bullet[i].fire)
			{
				if (level != bullet[i].GetLevel())
				{
					//bullet[i].level = level;
					bullet[i].ChangeLevel(level);
				}

				bullet[i].Shoot(col->GetWorldPos(),  UP, 200);
				break;
			}
		}
	}


	dir.Normalize();
	col->MoveWorldPos(dir * 200.0f * DELTA);
	LR->frame.x = (int)(LRKey + 3.0f);

	col->Update();
	LR->Update();
	boost->Update();
	for (int i = 0; i < PLBULLET; i++)
	{
		bullet[i].Update();
	}
	
}

void Player::Render()
{
	col->Render();
	LR->Render();
	boost->Render();
	for (int i = 0; i < PLBULLET; i++)
	{
		bullet[i].Render();
	}
}
