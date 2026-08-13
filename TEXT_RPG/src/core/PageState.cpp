#include "PageState.h"
#include "../ui/UIRenderer.h"
#include "GameManager.h"
#include "../sound/SoundManager.h"
#include <conio.h>
#include "../data/DataManager.h"

PageState::PageState(const std::vector<PageData>& pages, const std::string& bgm, std::function<void(GameManager&)> onFinish)
	:	m_pages(pages), m_bgm(bgm), m_onFinish(onFinish)
{

}

void PageState::enter(GameManager& manager)
{
	SoundManager::play(m_bgm);
}

void PageState::update(GameManager& manager)
{
	UIRenderer::printPageScreen(m_pages[m_currentPage].art, m_pages[m_currentPage].lines);

	_getch();

	m_currentPage++;

	if (m_currentPage >= int(m_pages.size()) && m_onFinish)
		m_onFinish(manager);
}

void PageState::exit(GameManager& manager)
{
	SoundManager::stop();
}
