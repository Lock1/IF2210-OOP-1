// Player class

#ifndef SPECIES_HPP
#define SPECIES_HPP

#include "attributes/elementtype.hpp"
#include "attributes/skill.hpp"
#include <string>
#include <set>

class Species {
    protected:
        int speciesID;
        std::string speciesName;
        Skill baseSkill;
        std::set<ElementType> elements;
        std::string interactionDescription;
        char speciesChar;

    public:
        Species(); // DEBUG
        Species(int id, std::string name, Skill skill, std::string desc, ElementType element1, ElementType element2=NoElement);
        // getter
        std::string getName();
        std::string getDescription();
        Skill getSkill();
        int getSpeciesID();
        char getSpeciesChar();
        std::set<ElementType> getElements();
};

#endif
