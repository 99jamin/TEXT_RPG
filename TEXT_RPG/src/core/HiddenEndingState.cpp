#include "HiddenEndingState.h"
#include "../ui/UIRenderer.h"
#include "ExploreState.h"
#include "GameManager.h"
#include "../sound/SoundManager.h"
#include <conio.h>
#include "../data/DataManager.h"

HiddenEndingState::HiddenEndingState()
{
	m_pages = DataManager::getInstance().getHiddenEndingData();
}

void HiddenEndingState::enter(GameManager& manager)
{
	SoundManager::play("bgm/hiddenending.mp3");
}

void HiddenEndingState::update(GameManager& manager)
{
	UIRenderer::printPageScreen(m_pages[m_currentPage].art, m_pages[m_currentPage].lines);

	_getch();

	m_currentPage++;

	if (m_currentPage >= int(m_pages.size()))
		manager.quit();
}

void HiddenEndingState::exit(GameManager& manager)
{
	SoundManager::stop();
}

