//13519206
#include "header/skilldatabase.hpp"
#include "header/config.hpp"

SkillDatabase::SkillDatabase() {
	skillList = new Skill[MAX_SKILL_LIST];
	nSkill = 0;
}

SkillDatabase::~SkillDatabase() {
	delete[] skillList;
}

//void SkillDatabase::loadSkillDatabase() {}

void SkillDatabase::addSkill(const Skill& newSkill) {
	skillList[nSkill] = newSkill;
	nSkill++;
}

bool SkillDatabase::isCompatible(Engimon engimonTarget, int skillID) {
	bool found = false;
    int i = 0;
    while(!found && i<nSkill){
        if(skillList[i].getSkillID() == skillID) found = true;
        i++;
    }
    bool compatible = engimonTarget.getSkill().isElementCompatible(engimonTarget.getElement());
    return found && compatible;

     
}