#include "SaveManager.h"
#include "../entity/Player.h"
#include "../map/Map.h"
#include <iostream>

void SaveManager::loadData()
{
	try
	{
		if (!hasSave())
			return;

		std::ifstream file(filePath);

		if (!file.is_open())
		{
			throw std::runtime_error("파일을 열 수 없음: " + filePath);
		}

		json j = json::parse(file);

		m_data.player.hp = j["player"]["hp"];
		m_data.player.atk = j["player"]["atk"];
		m_data.player.def = j["player"]["def"];
		m_data.player.stamina = j["player"]["stamina"];
		m_data.player.fleshCount = j["player"]["fleshCount"];
		m_data.player.poisoned = j["player"]["poisoned"];
		m_data.player.inventory = j["player"]["inventory"].get<std::map<std::string, int>>();

		for (auto& id : j["player"]["skills"])
			m_data.player.skills.push_back(fromId(id.get<std::string>()));

		m_data.map.currentMapId = j["map"]["currentMapId"];
		m_data.map.currentX = j["map"]["currentX"];
		m_data.map.currentY = j["map"]["currentY"];
		m_data.map.mapClearData = j["map"]["mapClearData"].get<std::map<std::string, std::vector<std::string>>>();
	}
	catch (const std::exception& e)
	{
		std::cerr << "[SaveManager] 데이터 로딩 실패: " << e.what() << std::endl;
		std::exit(1);
	}
	
}

void SaveManager::saveData(const Player& player, const Map& map)
{
	// 데이터 뽑아서 m_data에 저장
	m_data.player.hp = player.getCurHp();
	m_data.player.atk = player.getAtk();
	m_data.player.def = player.getDef();
	m_data.player.stamina = player.getStamina();
	m_data.player.fleshCount = player.getFleshCount();
	m_data.player.poisoned = player.isPoisoned();
	m_data.player.inventory = player.getInven();
	m_data.player.skills = player.getSkills();

	m_data.map.currentX = map.getCurrentX();
	m_data.map.currentY = map.getCurrentY();
	m_data.map.currentMapId = map.getId();
	m_data.map.mapClearData[m_data.map.currentMapId] = map.getClearRooms();

	// m_data를 JSON으로 직렬화 후 파일 저장
	saveLocal();
}

void SaveManager::saveLocal()
{
	std::vector<std::string> skillId;
	for (auto& e : m_data.player.skills)
		skillId.push_back(toId(e));

	// JSON 직렬화
	json j;
	j["player"]["hp"] = m_data.player.hp;
	j["player"]["atk"] = m_data.player.atk;
	j["player"]["def"] = m_data.player.def;
	j["player"]["stamina"] = m_data.player.stamina;
	j["player"]["fleshCount"] = m_data.player.fleshCount;
	j["player"]["poisoned"] = m_data.player.poisoned;
	j["player"]["inventory"] = m_data.player.inventory;
	j["player"]["skills"] = skillId;
	j["map"]["currentMapId"] = m_data.map.currentMapId;
	j["map"]["currentX"] = m_data.map.currentX;
	j["map"]["currentY"] = m_data.map.currentY;
	j["map"]["mapClearData"] = m_data.map.mapClearData;

	// 파일 저장
	std::ofstream file(filePath);
	file << j.dump(4);
}
