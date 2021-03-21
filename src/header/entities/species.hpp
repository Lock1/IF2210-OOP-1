// Player class

#ifndef SPECIES_HPP
#define SPECIES_HPP

#include <string>
#include "attributes/elementtype.hpp"
#include "attributes/skill.hpp"

class Species {
private:
    std::string name;
    Skill baseSkill;
    ElementType* elements;

public:
    Species(std::string name, Skill skill, ElementType element1, ElementType element2);
    ~Species();

    // getter
    std::string getName();
    Skill getSkills();
    ElementType* getElements();
};

#endif
