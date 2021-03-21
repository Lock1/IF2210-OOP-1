// Player class

#ifndef SPECIES_HPP
#define SPECIES_HPP

#include "attributes/elementtype.hpp"
#include "attributes/skill.hpp"
#include <string>
#include <set>

class Species {
    private:
        std::string speciesName;
        Skill baseSkill;
        std::set<ElementType> elements;

    public:
        Species(); // DEBUG
        Species(std::string name, Skill skill, ElementType element1, ElementType element2);
        ~Species();

        // getter
        std::string getName();
        Skill getSkill();
        std::set<ElementType> getElements();
};

#endif
