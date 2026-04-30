#pragma once
#include "RoomType.h"
#include "../data/DataTypes.h"
#include <string>
#include <vector>

class Room
{
	
public:

	Room(const RoomData& data)
		:m_id(data.id), m_type(data.type), m_text(data.text), m_actionText(data.actionText),
		m_monsterId(data.monsterId), m_itemId(data.itemId), m_itemCount(data.itemCount)
	{

	}

	bool isVisited() const { return visited; }
	const RoomType& getRoomType() const { return m_type; }
	const std::string& getRoomId() const { return m_id; }
	const std::string& getText() const { return m_text; }
	const std::string& getActionText() const { return m_actionText; }
	const std::string& getMonsterId() const { return m_monsterId; }
	const std::string& getItemId() const { return m_itemId; }
	int getItemCount() const { return m_itemCount; }


	void visit()
	{
		//visited = true;
	}

private:

	bool visited = false;

	RoomType m_type;
	std::string m_id;
	std::string m_text;
	std::string m_actionText;
	std::string m_monsterId;
	std::string m_itemId;
	int m_itemCount;
};