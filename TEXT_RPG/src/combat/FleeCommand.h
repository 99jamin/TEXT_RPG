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
		static std::uniform_int_distribution<int> dis(0, 9);

		m_fleeSuccess = dis(gen) < 8;

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

	bool m_fleeSuccess = false;
};
