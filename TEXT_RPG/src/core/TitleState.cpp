#include <iostream>
#include "TitleState.h"
#include "GameManager.h"
#include "ExploreState.h"

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

	std::string str = "village";
	if (input == 1)
		manager.pushState(std::make_unique<ExploreState>(str));

	if (input == 2)
		manager.quit();
}

void TitleState::exit(GameManager& manager)
{

}
