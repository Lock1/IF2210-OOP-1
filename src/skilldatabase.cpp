//13519206
#include "header/skilldatabase.hpp"
#include "header/config.hpp"

SkillDatabase::SkillDatabase() : skillDatabase() {

}

void SkillDatabase::addSkill(Skill& newSkill) {
	skillList.push_back(newSkill);
}

// TODO : Engimon
bool SkillDatabase::isCompatible(Engimon engimonTarget, int skillID) {
	bool found = false;
	Skill searchedSkill;
    int i = 0;
    while(!found && i<skillCount){
        if(skillList[i].getSkillID() == skillID) {
		searchedSkill = skillList[i];
		found = true;
	}
        i++;
    }
	// TODO : Add multielement checking
    bool compatible = searchedSkill.isElementCompatible(engimonTarget.getElement());
    return found && compatible;


}
