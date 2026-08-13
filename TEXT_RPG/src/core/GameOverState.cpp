#include "GameOverState.h"
#include "../ui/UIRenderer.h"
#include "../input/InputHandler.h"
#include "TitleState.h"
#include "GameManager.h"
#include "../sound/SoundManager.h"

void GameOverState::enter(GameManager& manager)
{
    SoundManager::play("bgm/gameover.mp3");
}

void GameOverState::update(GameManager& manager)
{

	UIRenderer::printGameOverScreen();

    int input = InputHandler::getInt(1, 2, [&]() { UIRenderer::printGameOverScreen(); });

    if (input == 1)
    {
        UIRenderer::clearLogs();
        manager.changeState(std::make_unique<TitleState>());
    }

    if (input == 2)
        manager.quit();
}

void GameOverState::exit(GameManager& manager)
{
    SoundManager::stop();
}
