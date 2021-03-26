// SpeciesDatabase class
// Need creating species database with constraint
// - Every species have 1 unique skill

// TODO : Extra, potential templating

#ifndef SPECIESDATABASE_HPP
#define SPECIESDATABASE_HPP

#include "entities/attributes/skill.hpp"
#include "entities/species.hpp"
#include "skilldatabase.hpp"
#include <string>
#include <vector>

class SpeciesDatabase {
    private:
        std::vector<Species> speciesDatabase;

        ElementType stringToElement(std::string target);
    public:
        SpeciesDatabase();

        void loadSpeciesDatabase(std::string filename, SkillDatabase& skillDB);
        // Load species from database file, will throw filename if can't find file
        void addSpecies(Species newSpecies);
        // Add species to database
        Species getSpecies(int speciesID);
        // Return species with same species ID, will throw speciesID if not found
        Species getSpecies(ElementType type1, ElementType type2);
        // Return species with element type matches, will throw type1 if not found
        unsigned int getSpeciesCount();
        // Get current species count
};

#endif
