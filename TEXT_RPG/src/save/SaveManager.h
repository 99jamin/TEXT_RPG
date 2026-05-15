#pragma once
#include <string>
#include <vector>
#include <map>
#include "../combat/SkillType.h"
#include "../data/DataTypes.h"
#include <fstream>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Player;
class Map;

class SaveManager
{

public:

	static SaveManager& getInstance()
	{
		static SaveManager instance;
		return instance;
	}

	void loadData();

	void saveData(const Player& player, const Map& map);

	bool hasSave() const { return std::filesystem::exists(filePath); }

	const SaveData::PlayerSaveData& getPlayerData() const { return m_data.player; }

	const std::string& getMapId() const { return m_data.map.currentMapId; }

	const SaveData::MapSaveData& getMapData() const { return m_data.map; }

private:

	const std::string filePath = "saves/save.json";

	void saveLocal();

	SaveData m_data;

};
