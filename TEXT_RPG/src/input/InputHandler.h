#pragma once
#include <iostream>
#include <limits>
#include <functional>
#include "../ui/UIRenderer.h"

class InputHandler
{

public:

	static int getInt(std::function<void()> redraw = nullptr)
	{
		int input;
		
		while (!(std::cin >> input))
		{
			handleInvalidInput(redraw);
		}

		return input;
	}

	static int getInt(int min, int max, std::function<void()> redraw = nullptr)
	{
		int input;

		while (!(std::cin >> input) || input < min || input > max)
		{
			handleInvalidInput(redraw);
		}

		return input;
	}

private:

	static void handleInvalidInput(std::function<void()> redraw)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		UIRenderer::addLog("올바른 선택을 해야한다.");
		if (redraw) redraw();
	}

};