#include "EndingState.h"
#include "../ui/UIRenderer.h"
#include "ExploreState.h"
#include "GameManager.h"
#include "../sound/SoundManager.h"
#include <conio.h>
#include "../data/DataManager.h"

EndingState::EndingState()
{
	m_pages = DataManager::getInstance().getEndingData();
}

void EndingState::enter(GameManager& manager)
{
	SoundManager::play("bgm/ending.mp3");
}

void EndingState::update(GameManager& manager)
{
	UIRenderer::printPageScreen(m_pages[m_currentPage].art, m_pages[m_currentPage].lines);

	_getch();

	m_currentPage++;

	if (m_currentPage >= int(m_pages.size()))
		manager.quit();
}

void EndingState::exit(GameManager& manager)
{
	SoundManager::stop();
}

