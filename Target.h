#pragma once
#include <cstdint>
#include <iostream>
class Target {
private:
int _threatScore;
char _type;
bool _engaged;

public:
	Target() = delete;
	Target(int threat, bool engaged) :
		_threatScore{ threat }, _engaged{ engaged }
	{
		genThreat();
		genType();
	}
	~Target() = default;
	Target& operator=(const Target& rhs) = default;
	bool operator<(const Target& rhs) const; 
	void display(std::ostream& outs) const;
	int getThreat() const;
	char getType() const;
	void engage();
	void setStatus(const bool& status);
	bool isEngaged() const;
	void genThreat();
	void genType();
	void updateThreat();

	friend std::ostream& operator<< (std::ostream& outs, const Target& prt)
	{
		prt.display(outs);

		return outs;
	}
};