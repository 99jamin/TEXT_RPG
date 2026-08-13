#pragma once

class IDamageable
{

public:
	virtual int takeDamage(int damage) = 0;
	virtual int takeFixedDamage(int amount) = 0;
	virtual bool isAlive() const = 0;
};