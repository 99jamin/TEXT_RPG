#include "src/core/GameManager.h"
#include "src/core/TitleState.h"


int main()
{
	GameManager manager;

	manager.pushState(std::make_unique<TitleState>());

	manager.run();

	return 0;
}