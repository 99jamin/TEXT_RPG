#pragma once
#include "Command.h"
#include <random>
#include <string>

class FleeCommand : public Command
{

public:

	void execute(Entity& user, Entity& target) override
	{
		m_fleeSuccess = false; 
		fleeDescription = "도망에 실패했다.";

		static std::mt19937 gen(std::random_device{}());
		static std::uniform_int_distribution<int> dis(0, 9);

		int result = dis(gen);
		if (result < 8)
		{
			// ���� ����
			fleeDescription = "도망에 성공했다.";
			m_fleeSuccess = true;
		}
	}


	std::string getDescription() const override
	{
		return fleeDescription;
	}

	bool isFleeSuccess() const { return m_fleeSuccess; }

private:

	bool m_fleeSuccess = false;
	std::string fleeDescription = "도망에 실패했다.";


};
