#include "Target.h"
#include <iomanip>
#include <random>

bool Target::operator < (const Target& rhs) const 
{
	int cmp = rhs._threatScore - this->_threatScore;
	if (cmp == 0) {
		return false;
	}
	return cmp > 0;
}
void Target::display(std::ostream& outs) const
{

	outs << std::left << std::setw(2)
		<< "TYPE" << " "
		<< std::right << std::setw(2)
		<< this->getType()
		<< std::left << std::setw(2)
		<< ", THREAT SCORE" << ": "
		<< std::right << std::setw(5)
		<< this->getThreat()
		<< "\n";
}
void Target::genThreat()
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(-100, 100); // define the range
	this->_threatScore = distr(gen);
}
int Target::getThreat() const
{
	return this->_threatScore;
}
void Target::genType()
{
	int type;
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 3); // define the range
	type = distr(gen);
	switch (type)
	{
	case 1:
		this->_type = 'A';
		break;
	case 2:
		this->_type = 'S';
		break;
	case 3:
		this->_type = 'U';
		break;
	default:
		break;
	}
}
void Target::engage()
{
	this->_engaged = true;
}
void Target::setStatus(const bool& status)
{
	this->_engaged = status;
}
bool Target::isEngaged() const
{
	return this->_engaged;
}
char Target::getType() const
{
	return this->_type;
}
void Target::updateThreat()
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::normal_distribution<float> distr(20.0, 2.0);
	
	int change = (int)round(distr(rd));
	if (this->_threatScore > 80) {
		this->_threatScore = this->_threatScore - change;
	}
	if(this->_threatScore <80){
		this->_threatScore = this->_threatScore + change;
	}
}