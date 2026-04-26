#pragma once
#include "../entity/Player.h"
#include "../entity/Monster.h"
#include "CombatResult.h"
#include "DefendCommand.h"
#include "FleeCommand.h"
#include "MonsterAtkCommand.h"
#include "SkillCommandFactory.h"
#include <iostream>

class CombatSystem
{

public:

	CombatSystem(Player& player, std::vector<Monster*>monsters)
		:m_player(player),m_monsters(monsters)
	{
		m_isRunning = true;
	}

	CombatResult combatStart()
	{
		while (m_isRunning)
		{
			playerTurn();

			if (!m_isRunning) break;

			for (auto& e : m_monsters)
			{
				monsterTurn(*e);
			}
		}

		return m_result;
	}

	/// <summary>
	/// 커맨드 패턴을 더 살리려면 사실, 커맨드 패턴을 정하기만 하고 실행은 한 문단에서 하는게 맞지 않나?
	/// 지금 그냥 switch문으로 행동을 나누는게 커맨드 패턴의미가 없는 것 같고, 모든 커맨드 패턴을 다 알고있는 것도 맞는 지 잘 모르겠다. 커맨드 클래스만 알고 다형성을 살려서 실행만 시키는게 맞지 않나?
	/// </summary>
	void playerTurn()
	{
		m_player.recoverStamina(1);  // 추가

		//굼니 커맨드 실행.
		if (m_player.isChargingGumni())
		{
			auto cmd = createSkillCommand(SkillType::Gumni);
			cmd->execute(m_player, *m_monsters[0]);
			checkMonsters();
			return;
		}

		// 독 데미지 처리
		if (m_player.isPoisoned())
			m_player.takeDamage(POISON_DAMAGE);


		if (!m_player.isAlive())
		{
			m_result = CombatResult::Defeat;
			combatEnd();
			return;
		}

		int input;
		std::cout << "1.공격하기\n2.방어하기\n3.도망가기\n4.아이템";
		std::cin >> input;

		switch (input)
		{

		case 1:
		{
			
			int count = 0;
			std::vector<SkillType> skills = m_player.getSkills();
			for (auto& e : skills)		//TODO: 스태미너 없으면 스킬 비활성화.
			{
				std::cout << ++count << "." << toString(e) << std::endl;
			}

			std::cin >> input;
			SkillType selected = skills[input - 1];
			auto skill = createSkillCommand(selected);
			skill->execute(m_player, *m_monsters[0]);
			m_player.consumeStamina(skill->getStaminaCost());

			//TODO: 모든 커맨드 패턴을 command로 통일해서 사용할때, 사용 후에 부가적인 후처리 처리

			checkMonsters();

			break;
		}

		case 2:
		{
			DefendCommand().execute(m_player, *m_monsters[0]);
			break;
		}
			
		case 3:
		{
			//TODO: 도망 커맨드 실행할 때 플래그 확인작업이 분리되어야 하면, 차라리 컴뱃시스템을 포인터로 넘겨주고 combatend함수를 직접 호출하도록 하는 것도 좋아보임. (근데 그러면 컴뱃과 커맨드가 서로서로 알고있는 관계가 되어버림.)
			//아니면 커맨드 타입의 execute함수 자체에 반환값을 줘서, 도망, 전투 유지 등으로 구분?
			FleeCommand fleecommand;
			fleecommand.execute(m_player, *m_monsters[0]);
			if (fleecommand.isFleeSuccess())
			{
				m_result = CombatResult::Fled;
				combatEnd();
			}
			break;
		}
			

		case 4:
		{
			//Item
			break;
		}

		}
	}

	void monsterTurn(Monster& monster)
	{
		MonsterAtkCommand().execute(monster, m_player);

		m_player.endDefend();

		if (!m_player.isAlive())
		{
			m_result = CombatResult::Defeat;
			combatEnd();
		}
	}

	void combatEnd()
	{
		m_isRunning = false;
	}


private:

	Player& m_player;
	std::vector<Monster*> m_monsters;
	bool m_isRunning = true;

	//전투 결과
	CombatResult m_result = CombatResult::Victory;

	//상태이상
	static constexpr int POISON_DAMAGE = 5;

	//몬스터 사망 체크
	void checkMonsters()
	{
		m_monsters.erase(
			std::remove_if(m_monsters.begin(), m_monsters.end(),
				[](Monster* m) { return !m->isAlive(); }),
			m_monsters.end()
		);

		if (m_monsters.empty())
		{
			m_result = CombatResult::Victory;
			combatEnd();
		}
	}
};
