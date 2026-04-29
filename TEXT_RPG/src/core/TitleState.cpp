#include <iostream>
#include "TitleState.h"
#include "GameManager.h"

void TitleState::enter(GameManager& manager)
{
	std::cout << "====섬그늘====\n";
}

void TitleState::update(GameManager& manager)
{
	int input;
	std::cout << "1. 시작하기\n";
	std::cout << "2. 종료하기\n";
	std::cin >> input;

	if (input == 2)
		manager.quit();
}

void TitleState::exit(GameManager& manager)
{

}
