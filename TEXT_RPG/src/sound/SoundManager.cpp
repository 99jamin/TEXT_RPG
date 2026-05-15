#include "SoundManager.h"

bool SoundManager::s_isPlaying = false;

void SoundManager::play(const std::string& filename, bool loop)
{
    stop();
    std::wstring wfile(filename.begin(), filename.end());
    std::wstring openCmd = L"open \"" + wfile + L"\" type mpegvideo alias bgm";
    mciSendString(openCmd.c_str(), NULL, 0, NULL);
    mciSendString(loop ? L"play bgm repeat" : L"play bgm", NULL, 0, NULL);
    s_isPlaying = true;
}

void SoundManager::stop()
{
    if (!s_isPlaying) return;
    mciSendString(L"stop bgm", NULL, 0, NULL);
    mciSendString(L"close bgm", NULL, 0, NULL);
    s_isPlaying = false;
}

void SoundManager::playSFX(const std::string& filename)
{
    std::wstring wfile(filename.begin(), filename.end());
    PlaySound(wfile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}
