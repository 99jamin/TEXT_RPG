#pragma once
#define NOMINMAX
#include <windows.h>
#include <mmsystem.h>
#include <string>
#pragma comment(lib, "winmm.lib")

class SoundManager
{
public:
    static void play(const std::string& filename, bool loop = true);
    static void stop();
    static void playSFX(const std::string& filename);

private:
    static bool s_isPlaying;
};