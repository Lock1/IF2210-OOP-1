#include "header/breeding.hpp"
#include <algorithm>

using namespace std;

Breed::Breed(Engimon e1, Engimon e2){
    parent1 = &e1;
    parent2 = &e2;
}

Engimon Breed::startBreeding(string namaAnak){
    if((parent1->getLevel() < 30)||(parent2->getLevel()<30)){
        throw "Level must be >=30";
    }else{
        Skill skill = Skill(0, 0, "", NoElement); 

        bool fromP1 = false, fromP2 = false;
        vector<Skill> skillList_parent1 = parent1->getLearnedSkill();
        vector<Skill> skillList_parent2 = parent2->getLearnedSkill();
        vector<Skill> skillList_child;

        while((!skillList_parent1.empty() && !skillList_parent2.empty()) || skillList_child.size() < 4){
            if(!skillList_parent1.empty()){
                skill = skillList_parent1[0];
                fromP1 = true;
            }else{
                skill = skillList_parent2[0];
                fromP2 = true;
            }

            for(int i=0; i<skillList_parent1.size();i++){
                if(skill.getMasteryLevel()<skillList_parent1[i].getMasteryLevel()){
                    skill = skillList_parent1[i];
                }
            }
            
            for(int i=0; i<skillList_parent2.size();i++){
                if(skill.getMasteryLevel() < skillList_parent2[i].getMasteryLevel()){
                    skill = skillList_parent2[i];
                    fromP2 = true;
                    fromP1 = false;
                }else if((skill.getMasteryLevel() == skillList_parent2[i].getMasteryLevel()) && fromP1){
                    skill.levelUpMastery();
                    fromP2 = true;
                }
            }

            if(fromP1 || (std::find(skillList_parent1.begin(), skillList_parent1.end(), skill) != skillList_parent1.end())){
                skillList_parent1.erase(std::remove(skillList_parent1.begin(), skillList_parent1.end(), 8), skillList_parent1.end());
            } 
            if(fromP2 || (std::find(skillList_parent2.begin(), skillList_parent2.end(), skill) != skillList_parent2.end())){
                skillList_parent2.erase(std::remove(skillList_parent2.begin(), skillList_parent2.end(), 8), skillList_parent2.end());
            }
            skillList_child.push_back(skill);
        }


        
        set<ElementType> parent1_element = parent1->getElement();
        set<ElementType> parent2_element = parent2->getElement();
        ElementType child_element1;
        ElementType child_element2;

        auto it1 = parent1_element.begin(), it2 = parent2_element.begin();
        ElementType el1 = *it1, el2 = *it2;
        int parent1ElementAdvantage = getElementAdvantage(el1, el2);
        int parent2ElementAdvantage = getElementAdvantage(el2, el1);

        fromP1 = false, fromP2 = false;
        if(el1==el2){
            child_element1 = el1;
            fromP1 = true;
        }else{
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

        Species childSpecies;
        if(child_element2 != NoElement){
            // anak ga boleh punya species sama kayak parent(?)
        }else{
            if(fromP1){
                childSpecies = Species(parent1->getSpeciesID(), namaAnak, skillList_child[0], parent1->getDescription(), child_element1, NoElement);
            }else{
                childSpecies = Species(parent2->getSpeciesID(), namaAnak, skillList_child[0], parent2->getDescription(), child_element2, NoElement);
            }
        }

        Position pos = new Position(0, 0);
        Engimon child = new Engimon(childSpecies, false, pos);

        for(int i=1; i<skillList_child.size();i++){
            child.addSkill(skillList_child[i]);
        }
        parent1->setLevel(parent1->getLevel() - 30);
        parent2->setLevel(parent2->getLevel() - 30);

        return child;
    }
}

int Breed::getElementAdvantage(ElementType elem1, ElementType elem2){
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
    else if (elem1 == Water)
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