#include "../header/entities/species.hpp"
#include <set>
using namespace std;

Species::Species() : baseSkill(99, 1, "hoha", Electric) {
	// Do Nothing
	// DEBUG ONLY
}
Species::Species(string name, Skill skill, ElementType element1, ElementType element2) : baseSkill(skill) {
	// TODO : Add proper skill creation
	// this->name = name;
	// this->baseSkill = skill;
	// this->elements = new ElementType[2];
	// elements[0] = element1;
	// elements[1] = element2;
}

Species::~Species() {
	// Do Nothing
}


string Species::getName() {
	return speciesName;
}

Skill Species::getSkill() {
	return baseSkill;
}

set<ElementType> Species::getElements() {
	return elements;
}
