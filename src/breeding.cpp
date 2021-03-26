#include "header/breeding.hpp"
#include <algorithm>

using namespace std;

Breed::Breed(Engimon *e1, Engimon *e2) : EngimonInteraction(e1, e2) {

}

Engimon* Breed::startBreeding(SpeciesDatabase& speciesDB) {
    int errorCode = 1;
    if((e1->getLevel() < 30) || (e2->getLevel() < 30)){
        throw errorCode;
    }else{
        Skill skillTemp = Skill(0, 0, "", NoElement);

        vector<Skill> skillList_parent1 = e1->getSkillList();
        vector<Skill> skillList_parent2 = e2->getSkillList();
        vector<Skill> skillList_child;

        bool fromP1 = false, fromP2 = false;
        while((!skillList_parent1.empty() || !skillList_parent2.empty()) && skillList_child.size() < 4) {
            fromP1 = false;
            fromP2 = false;
            // if(!skillList_parent1.empty()){
            //     skillTemp = skillList_parent1[0];
            //     fromP1 = true;
            // }else if (!skillList_parent2.empty()) {
            //     skillTemp = skillList_parent2[0];
            //     fromP2 = true;
            // }

            for(unsigned i=0; i<skillList_parent1.size();i++){
                if(skillTemp.getMasteryLevel()<skillList_parent1[i].getMasteryLevel()){
                    skillTemp = skillList_parent1[i];
                    fromP1 = true;
                }
            }


            for(unsigned i=0; i<skillList_parent2.size();i++){
                if(fromP1 && !fromP2 && skillTemp == skillList_parent2[i]){
                    // If skill matches, check mastery level both parent skill
                    if (skillTemp.getMasteryLevel() == skillList_parent2[i].getMasteryLevel()) {
                        skillTemp.levelUpMastery();
                        fromP2 = true;
                    }
                    // else if (skillTemp.getMasteryLevel() < skillList_parent2[i].getMasteryLevel()) {
                    //     skillTemp = skillList_parent2[i];
                    //     fromP2 = true;
                    // }
                }
                else if(skillTemp.getMasteryLevel() < skillList_parent2[i].getMasteryLevel()){
                    skillTemp = skillList_parent2[i];
                    fromP2 = true;
                    fromP1 = false;
                }
            }

            if (not skillList_parent1.empty()) {
                if (fromP1 || (std::find(skillList_parent1.begin(), skillList_parent1.end(), skillTemp) != skillList_parent1.end())) {
                    skillList_parent1.erase(std::find(skillList_parent1.begin(), skillList_parent1.end(), skillTemp));
                }
            }

            if (not skillList_parent2.empty()) {
                if(fromP2 || (std::find(skillList_parent2.begin(), skillList_parent2.end(), skillTemp) != skillList_parent2.end())) {
                    skillList_parent2.erase(std::find(skillList_parent2.begin(), skillList_parent2.end(), skillTemp));
                }
            }

            skillList_child.push_back(skillTemp);
        }



        set<ElementType> parent1_element = e1->getElements();
        set<ElementType> parent2_element = e2->getElements();
        ElementType child_element1 = NoElement;
        ElementType child_element2 = NoElement;

        auto it1 = parent1_element.begin(), it2 = parent2_element.begin();
        ElementType el1 = *it1;
        ElementType el2 = *it2;
        float parent1ElementAdvantage = getElementAdvantage(el1, el2);
        float parent2ElementAdvantage = getElementAdvantage(el2, el1);

        bool advantageBranch = false;
        fromP1 = false, fromP2 = false;
        if(el1==el2){
            child_element1 = el1;
            fromP1 = true;
        }else{
            advantageBranch = true;
            if(parent1ElementAdvantage>parent2ElementAdvantage) {
                child_element1 = el1;
                fromP1 = true;
            }
            else if(parent1ElementAdvantage<parent2ElementAdvantage) {
                child_element1 = el2;
                fromP2 = true;
            }
            else{
                child_element1 = el1;
                child_element2 = el2;
            }
        }

        // Species childSpecies = speciesDB.getSpecies(child_element1, child_element2);
        // if(child_element2 != NoElement){
        //     // anak ga boleh punya species sama kayak parent(?)
        // }else{
        //     if(fromP1){
        //         childSpecies = Species(e1->getSpeciesID(), namaAnak, skillList_child[0], e1->getDescription(), child_element1, NoElement);
        //     }else{
        //         childSpecies = Species(e2->getSpeciesID(), namaAnak, skillList_child[0], e2->getDescription(), child_element2, NoElement);
        //     }
        // }

        // Species resolving
        Species childSpecies;
        if (advantageBranch) {
            if (fromP1) {
                childSpecies = speciesDB.getSpecies(e1->getSpeciesID());
            }
            else if (fromP2) {
                childSpecies = speciesDB.getSpecies(e2->getSpeciesID());
            }
            else
                childSpecies = speciesDB.getSpecies(child_element1, child_element2);
        }
        else if (fromP1) {
            // If both parent equal element
            childSpecies = speciesDB.getSpecies(e1->getSpeciesID());
        }

        Engimon *child = new Engimon(childSpecies, false, Position(0, 0), 1);

        vector<Skill>& childBaseSkill = child->getSkillListRef();
        for(unsigned i=0 ; i < skillList_child.size() ; i++){
            if (not child->addSkill(skillList_child[i])) {
                while (childBaseSkill[0].getMasteryLevel() < skillList_child[i].getMasteryLevel())
                    childBaseSkill[0].levelUpMastery();
            }
        }

        child->addParentName(e1->getEngimonName());
        child->addParentName(e2->getEngimonName());

        child->addParentSpecies(*e1);
        child->addParentSpecies(*e2);

        e1->breedingLevelDown();
        e2->breedingLevelDown();

        return child;
    }
}

float Breed::getElementAdvantage(ElementType elem1, ElementType elem2){
    if (elem1 == Fire)
    {
        if (elem2 == Fire){
            return 1;
        }
        else if (elem2 == Water){
            return 0;
        }
        else if (elem2 == Electric){
            return 1;
        }
        else if (elem2 == Ground){
            return 0.5;
        }
        else if (elem2 == Ice){
            return 2;
        }
        else{
            return 0;
        }
    }
    else if (elem1 == Water)
    {
        if (elem2 == Fire){
            return 2;
        }
        else if (elem2 == Water){
            return 1;
        }
        else if (elem2 == Electric){
            return 0;
        }
        else if (elem2 == Ground){
            return 1;
        }
        else if (elem2 == Ice){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if (elem1 == Electric)
    {
        if (elem2 == Fire){
            return 1;
        }
        else if (elem2 == Water){
            return 2;
        }
        else if (elem2 == Electric){
            return 1;
        }
        else if (elem2 == Ground){
            return 0;
        }
        else if (elem2 == Ice){
            return 1.5;
        }
        else{
            return 0;
        }
    }
    else if (elem1 == Ground)
    {
        if (elem2 == Fire){
            return 1.5;
        }
        else if (elem2 == Water){
            return 1;
        }
        else if (elem2 == Electric){
            return 2;
        }
        else if (elem2 == Ground){
            return 1;
        }
        else if (elem2 == Ice){
            return 0;
        }
        else{
            return 0;
        }
    }
    else if (elem1 == Ice)
    {
        if (elem2 == Fire){
            return 0;
        }
        else if (elem2 == Water){
            return 1;
        }
        else if (elem2 == Electric){
            return 0.5;
        }
        else if (elem2 == Ground){
            return 2;
        }
        else if (elem2 == Ice){
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
            return 0;
        }
}
