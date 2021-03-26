// Species database implementation
#include "header/speciesdatabase.hpp"
#include "header/skilldatabase.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

SpeciesDatabase::SpeciesDatabase() {

}

void SpeciesDatabase::loadSpeciesDatabase(string filename, SkillDatabase& skillDB) {
    ifstream speciesFile = ifstream(filename);
    if (speciesFile.is_open()) {
        int speciesID;
        string speciesName;
        string interactionDescription;
        string typeString;
        while (!speciesFile.eof()) {
            speciesFile >> speciesID;
            speciesFile >> speciesName;
            speciesFile >> typeString;
            ElementType firstType = stringToElement(typeString);
            speciesFile >> typeString;
            ElementType secondType = stringToElement(typeString);
            speciesFile >> interactionDescription;

            for (unsigned int i = 0; i < interactionDescription.length(); i++)
                if (interactionDescription[i] == '-')
                    interactionDescription[i] = ' ';

            if (secondType != NoElement)
                addSpecies(Species(speciesID, speciesName, skillDB.getSkill(speciesID), interactionDescription, firstType, secondType));
            else
                addSpecies(Species(speciesID, speciesName, skillDB.getSkill(speciesID), interactionDescription, firstType));
        }

        speciesFile.close();
    }
    else
        throw filename;
}

ElementType SpeciesDatabase::stringToElement(std::string target) {
    if (target == "Ground")
        return Ground;
    else if (target == "Electric")
        return Electric;
    else if (target == "Fire")
        return Fire;
    else if (target == "Water")
        return Water;
    else if (target == "Ice")
        return Ice;
    else
        return NoElement;
}

void SpeciesDatabase::addSpecies(Species newSpecies) {
    speciesDatabase.push_back(newSpecies);
}

unsigned int SpeciesDatabase::getSpeciesCount() {
    return speciesDatabase.size();
}

Species SpeciesDatabase::getSpecies(int speciesID) {
    for (unsigned int i = 0; i < speciesDatabase.size(); i++)
        if (speciesDatabase[i].getSpeciesID() == speciesID)
            return speciesDatabase[i];
    throw speciesID;
}

Species SpeciesDatabase::getSpecies(ElementType type1, ElementType type2) {
    for (unsigned int i = 0; i < speciesDatabase.size(); i++) {
        set<ElementType> types = speciesDatabase[i].getElements();
        if (types.find(type1) != types.end() && types.find(type2) != types.end())
            return speciesDatabase[i];
    }
    throw type1;
}
