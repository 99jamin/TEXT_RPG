#pragma once
#include <string>
#include <vector>
#include <map>
#include "../combat/SkillType.h"
#include "../data/DataTypes.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class SaveManager
{

public:

	static SaveManager& getInstance()
	{
		static SaveManager instance;
		return instance;
	}

	void loadData()
	{
		if (!hasSave())
			return;

		std::ifstream file(filePath);
		if (!file.is_open())
			return; // 세이브 파일 없음

		json j = json::parse(file);

		m_data.player.hp = j["player"]["hp"];
		m_data.player.stamina = j["player"]["stamina"];
		m_data.player.poisoned = j["player"]["poisoned"];
		m_data.player.inventory = j["player"]["inventory"].get<std::map<std::string, int>>();

		for (auto& id : j["player"]["skills"])
			m_data.player.skills.push_back(fromId(id.get<std::string>()));

		m_data.map.currentMapId = j["map"]["currentMapId"];
		m_data.map.currentX = j["map"]["currentX"];
		m_data.map.currentY = j["map"]["currentY"];
		m_data.map.mapClearData = j["map"]["mapClearData"].get<std::map<std::string, std::vector<std::string>>>();
	}
	
	void saveData(const Player& player, const Map& map)
	{
		// 데이터 뽑아서 m_data에 저장
		m_data.player.hp = player.getCurHp();
		m_data.player.stamina = player.getStamina();
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

	bool hasSave() const
	{
		return std::filesystem::exists(filePath);
	}
	
	const SaveData::PlayerSaveData& getPlayerData() const
	{
		return m_data.player;
	}

	const std::string& getMapId() const
	{
		return m_data.map.currentMapId;
	}

	const SaveData::MapSaveData& getMapData() const
	{
		return m_data.map;
	}

private:

	const std::string filePath = "saves/save.json";

	void saveLocal()
	{
		std::vector<std::string> skillId;
		for (auto& e : m_data.player.skills)
			skillId.push_back(toId(e));

		// JSON 직렬화
		json j;
		j["player"]["hp"] = m_data.player.hp;
		j["player"]["stamina"] = m_data.player.stamina;
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

	SaveData m_data;

};
