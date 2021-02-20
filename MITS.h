#pragma once
#include "Target.h"
#include "Weapon.h"
#include <vector>
class MITS {
private:
	std::vector<Target> _targets;
	std::vector<Target>::iterator it;
	Weapon type1 = Weapon('S', '\0',false, 96);
	Weapon type2 = Weapon('U', '\0', false, 98);
	Weapon type3 = Weapon('A', '\0', false, 90);
	Weapon type4 = Weapon('S', 'A', false, 88);
public:
	MITS() = default;
	~MITS() = default;
	void display(std::ostream& outs, std::vector<Target> targets) const;
	void genTargets();
	void prioritizeTargets();
	void updateThreats();
	void assignTargets();
};