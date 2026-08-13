#pragma once
#include <iostream>
#include <limits>
#include <functional>
#include "../ui/UIRenderer.h"
#include "../sound/SoundManager.h"
#include <conio.h>

class InputHandler
{

public:

	static int getInt(int min, int max, std::function<void()> redraw = nullptr)
	{
		while (true)
		{
			int ch = _getch();
			if (ch >= '0' + min && ch <= '0' + max)
			{
				SoundManager::playSFX("sfx/enter.wav");
				return ch - '0';
			}
			UIRenderer::addLog("올바른 선택을 해야한다.");
			if (redraw) redraw();
		}
	}

private:

};