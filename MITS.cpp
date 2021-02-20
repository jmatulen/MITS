/// MITS.cpp : This file contains the 'main' function. Program execution begins and ends there.
///
/// author: Josh Matulenas
/// 
/// MITS makes use of a vector to store target list rather than c++'s list,
/// because we need the more efficient sorting algorithm provided for vectors.
/// the std::sort algorithm is guaranteed to be O(N(log(N))), WORST case. (https://www.cplusplus.com/reference/algorithm/sort/), list.sort() is NlogN on average.
/// Since our vectors will be most defilitely utilizing cache, its damn fast, even though the algo makes copies.
/// Compared to a list or forward_list, them not being contiguous in memory really kills
/// the performance by introducing cache misses. Vectors also are much more efficient with pushing new elements,
/// that list is. https://baptiste-wicht.com/posts/2012/11/cpp-benchmark-vector-vs-list.html#:~:text=For%20a%20vector%20std%3A%3A,member%20function%20sort%20is%20used.&text=We%20can%20see%20that%20sorting,poor%20usage%20of%20the%20cache.&text=This%20time%20the%20list%20is%20faster%20than%20the%20vector.
/// MITS doesnt use any queues due to the program needing to search all possible threats the weapons can target, some may be skipped over. LIFO doesnt allow this efficiently.
/// In conclusion the vector was the best choice for the container for our data.
#include "MITS.h"
#include <random>
#include <iostream>
#include <algorithm>
int main()
{
    int timesteps = 0;
    MITS* mits = new MITS;

    std::cout << "Enter number of timesteps: "; 
    std::cin >> timesteps; 
    std::cout << "\n";
   
    while (!std::cin) { //while not proper input
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Enter number of timesteps: ";
        std::cin >> timesteps;
        std::cout << "\n";
    }

    for (int i = 0; i < timesteps; i++) {

        mits->genTargets();
        mits->prioritizeTargets();
        mits->assignTargets();
    }
    delete mits;
    return 0;
}
/**
*   Randomly create 0-4 new targets
*/
void MITS::genTargets()
{
    int numTargets = 0;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 4); // define the range
    numTargets = distr(gen);

    for (int i = 0; i < numTargets; i++) {

        Target newTarget = Target(0, false);
        this->_targets.push_back(newTarget);
    }
}
/**
*   Assign a target for current timestep to each wepon, based on threat
*/
void MITS::assignTargets()
{
    this->type1.setStatus(false);   //reset weapons for next timestep
    this->type2.setStatus(false);
    this->type3.setStatus(false);
    this->type4.setStatus(false);

    for (int t = 0; t < this->_targets.size(); t++) {

        if (this->_targets[t].isEngaged() || this->_targets[t].getThreat() < 10) {

            continue;   //if target is engaged or not a threat, go onto the next target
        }
        else if (!this->type1.isEngaged() && (this->_targets[t].getType() == this->type1.getType())) {  //engage target if weapon is able to

                std::cout << "Weapon: 1 Engaging Target: "
                << this->_targets[t];

                if (this->type1.engageTarget(this->_targets[t])) {  //if target was destroyed

                    std::cout << "Target: "
                              << this->_targets[t]
                              << "was destroyed by Weapon: 1!"
                              << '\n' << '\n';

                    this->_targets.erase(this->_targets.begin() + t);   //remove from target list
                    t--;    //decrement iteration counter, since erase resizes the vector. If we dont, algo skips next target inadevertently
                }
                else {
                     std::cout << "Weapon 1 Failed to destroy target!"
                               << '\n';
                }
        }
        else if (!this->type2.isEngaged() && (this->_targets[t].getType() == this->type2.getType())) {  //engage target if weapon is able to

                std::cout << "Weapon: 2 Engaging Target: "
                          << this->_targets[t];

                if (this->type2.engageTarget(this->_targets[t])) {  //if target was destroyed

                    std::cout << "Target: "
                              << this->_targets[t]
                              << "was destroyed by Weapon: 2!"
                              << '\n' << '\n';

                    this->_targets.erase(this->_targets.begin() + t);   //remove from target list
                    t--;    //decrement iteration counter, since erase resizes the vector. If we dont, algo skips next target inadevertently
                }
                else {
                    std::cout << "Weapon 2 Failed to destroy target!"
                              << '\n';
                }
        }
        else if (!this->type3.isEngaged() && (this->_targets[t].getType() == this->type3.getType())) {  //engage target if weapon is able to

                std::cout << "Weapon: 3 Engaging Target: "
                          << this->_targets[t];

                if (this->type3.engageTarget(this->_targets[t])) {  //if target was destroyed

                    std::cout << "Target: "
                              << this->_targets[t]
                              << "was destroyed by Weapon: 3!"
                              << '\n' << '\n';

                    this->_targets.erase(this->_targets.begin() + t);   //remove from target list
                    t--;    //decrement iteration counter, since erase resizes the vector. If we dont, algo skips next target inadevertently
                }
                else {

                     std::cout << "Weapon 3 Failed to destroy target!"
                               << '\n';
                }
        }
        else if (!this->type4.isEngaged() && ((this->_targets[t].getType() == this->type4.getType()) ||
                                              (this->_targets[t].getType() == this->type4.getHybridType()))) {  //engage target if weapon is able to

                std::cout << "Weapon: 4 Engaging Target: "
                          << this->_targets[t];

                if (this->type4.engageTarget(this->_targets[t])) {  //if target was destroyed
                    
                    std::cout << "Target: "
                              << this->_targets[t]
                              << "was destroyed by Weapon: 4!"
                              << '\n' << '\n';

                    this->_targets.erase(this->_targets.begin() + t);   //remove from target list
                    t--;    //decrement iteration counter, since erase resizes the vector. If we dont, algo skips next target inadevertently
                }
                else {
                        std::cout << "Weapon 4 Failed to destroy target!"
                                  << '\n';
                }
        }
    }
}
/**
*   Sort target list by threat. This allows for much less loop iterations on target list
*/
void MITS::prioritizeTargets()
{
    std::sort(this->_targets.begin(), this->_targets.end(),
        [](const Target& lhs, const Target& rhs) {
        return rhs < lhs;
    });

    std::cout << "Threat list for current timestep:" << '\n';
    display(std::cout, this->_targets);
}
/**
* Adds or subtracts a random amount of threat to each target.
* Allows threat levels to constantly change, making things more interesting.
*/
void MITS::updateThreats()
{
    for (Target target : this->_targets) {

        target.updateThreat();
    }
}
/**
*   Display target list.
*/
void MITS::display(std::ostream& outs, std::vector<Target> targets) const
{
    for (Target target : targets) {

        outs << target;
    }
}