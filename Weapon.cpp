#include "Weapon.h"
#include <random>

char Weapon::getType() const
{
	return this->_weaponType1;
}
char Weapon::getHybridType() const
{
	return this->_weaponType2;
}
bool Weapon::isEngaged()const
{
	return this->_engaged;
}
void Weapon::setStatus(bool status)
{
	this->_engaged = status;
}
bool Weapon::engageTarget(Target target)
{
	this->_engaged = true;
	target.engage();
	int roll = 0;
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 100); // define the range
	roll = distr(gen);
	if (roll < this->_successRate) {

		target.setStatus(false);
		return true;
	}
	else {
		return false;
	}
}