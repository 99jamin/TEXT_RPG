#pragma once
#include "PlayerCommand.h"
#include <random>
#include <string>

class FleeCommand : public PlayerCommand
{

public:

	void execute(Player& player, std::vector<Monster*>& monsters, int monsterIndex, std::function<void(LogLine)> logCallback = nullptr) override
	{
		static std::mt19937 gen(std::random_device{}());
		static std::uniform_int_distribution<int> dis(0, FLEE_THRESHOLD+1);

		m_fleeSuccess = dis(gen) < FLEE_THRESHOLD;

		if (logCallback)
		{
			m_log.clear();

			if (m_fleeSuccess)
				m_log.push_back(LogSegment("도주했다.", Color::WHITE));
			else
				m_log.push_back(LogSegment("도주에 실패했다.", Color::WHITE));

			logCallback(m_log);
		}
	}

	bool isFleeSuccess() const { return m_fleeSuccess; }

private:
	LogLine m_log;
	bool m_fleeSuccess = false;
	static constexpr int FLEE_THRESHOLD = 8;
};
