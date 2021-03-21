#include "../header/entities/species.hpp"
using namespace std;

Species::Species(string name, Skill skill, ElementType element1, ElementType element2=NoElement) {
	this->name = name;
	this->baseSkill = skill;
	this->elements = new ElementType[2];
	elements[0] = element1;
	elements[1] = element2;
}

Species::~Species() {
	// Do Nothing
}

string Species::getName() {
	return this->name;
}

Skill Species::getSkills() {
	return this->baseSkill;
}

ElementType* Species::getElements() {
	return this->elements;
}