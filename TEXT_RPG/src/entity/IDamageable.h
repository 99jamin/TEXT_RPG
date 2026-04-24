#pragma once

class IDamageable
{

public:
	virtual void takeDamage(int damage) = 0;
	virtual bool isAlive() const = 0;
};