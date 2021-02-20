#pragma once
#include "Target.h"
class Weapon {
private:
	char _weaponType1;
	char _weaponType2;
	bool _engaged;
	int _successRate;
public:
	Weapon()=delete;
	Weapon(char weaponType1, char weaponType2, bool engadged, int successRate) :
		_weaponType1{ weaponType1 }, _weaponType2{ weaponType2 }, 
		_engaged{ engadged }, _successRate{ successRate }
	{
	}
	~Weapon() = default;
	char getType() const;
	char getHybridType() const;
	bool engageTarget(Target target);
	void setStatus(bool status);
	bool isEngaged() const;
};
