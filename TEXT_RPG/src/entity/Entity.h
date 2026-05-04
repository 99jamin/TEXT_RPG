#pragma once
#include <string>
#include <algorithm>
#include "Idamageable.h"


class Entity : public IDamageable
{
public:
	
	Entity(const std::string& name, int maxHp, int atk, int def);

	void takeDamage(int damage) override;

	virtual void printStatus() const = 0;		

	virtual void dead() = 0;					

	const std::string& getName() const { return m_name; }
	int getCurHp() const { return m_curHp; }
	int getMaxHp() const { return m_maxHp; }
	int getAtk() const { return m_atk; }
	int getDef() const { return m_def; }

	void recoverHp(int amount);

	bool isAlive() const override;


protected:

	void setAtk(int atk) { m_atk = atk; }
	void setDef(int def) { m_def = def; }
	void setCurHp(int hp) { m_curHp = hp; }


private:

	std::string m_name;
	int m_curHp;
	int m_maxHp;
	int m_atk;
	int m_def;

};
