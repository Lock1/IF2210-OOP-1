#include "../header/entities/species.hpp"
#include <set>
using namespace std;

Species::Species() : baseSkill(99, 1, "hoha", Electric) {
	// Do Nothing
	// DEBUG ONLY
}
Species::Species(int id, string name, Skill skill, string desc, ElementType element1, ElementType element2) :
		baseSkill(skill) {
	speciesID = id;
    speciesName = name;
    elements.insert(element1);
	if (element2 != NoElement)
		elements.insert(element2);
    interactionDescription = desc; // TODO : Strip bar and check

	// Char evaluator
	if (elements.find(Water) != elements.end()) {
		if (elements.find(Ground) != elements.end())
			speciesChar = 'b';
		else if (elements.find(Ice) != elements.end())
			speciesChar = 'z';
		else
			speciesChar = 'w';
	}
	else if (elements.find(Fire) != elements.end()) {
		if (elements.find(Electric) != elements.end())
			speciesChar = 'r';
		else
			speciesChar = 'f';
	}
	else if (elements.find(Ice) != elements.end())
		speciesChar = 'i';
	else if (elements.find(Electric) != elements.end())
		speciesChar = 'e';
	else if (elements.find(Ground) != elements.end())
		speciesChar = 'g';
}


bool Species::isTileCompatible(TileType type) {
    bool isAbleToTraverseSea = (elements.find(Water) != elements.end()) || (elements.find(Ice) != elements.end());
    bool isAbleToTraverseGrass = (elements.find(Fire) != elements.end())
                                    || (elements.find(Ground) != elements.end())
                                    || (elements.find(Electric) != elements.end());
    if (isAbleToTraverseSea && (type == Sea))
        return true;
    else if (isAbleToTraverseGrass && (type == Grass))
        return true;
    else
        return false;
}

string Species::getName() {
	return speciesName;
}

string Species::getDescription() {
	return interactionDescription;
}

char Species::getSpeciesChar() {
	return speciesChar;
}

Skill Species::getSkill() {
	return baseSkill;
}

int Species::getSpeciesID() {
	return speciesID;
}

set<ElementType> Species::getElements() {
	return elements;
}
