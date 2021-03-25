#include "header/battle.hpp"
#include "header/entities/engimon.hpp"
#include "header/skilldatabase.hpp"
#include "header/entities/species.hpp"
#include "header/entities/attributes/elementtype.hpp"
#include "header/entities/attributes/skill.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <set>

using namespace std;

Battle::Battle(Engimon *e1, Engimon *e2){
    float sum_e1 = 0;
    float sum_e2 = 0;
    vector<Skill> skillList_e1 = e1->getSkillList();
    vector<Skill> skillList_e2 = e2->getSkillList();
    set<ElementType> elements_e1 = e1->getElement();
    set<ElementType> elements_e2 = e2->getElement();
    for (unsigned i = 0; i < skillList_e1.size(); i++){
        sum_e1 += skillList_e1[i].getBasePower()*skillList_e1[i].getMasteryLevel();

    }
    for (unsigned j = 0; j < skillList_e2.size(); j++){
        sum_e2 += skillList_e2[j].getBasePower()*skillList_e2[j].getMasteryLevel();
    }
    float adv1,adv2;
    if (elements_e1.size() == 1){
        if (elements_e2.size() == 1){
            auto it_e1 = elements_e1.begin();
            auto it_e2 = elements_e2.begin();
            ElementType type1_1 = *it_e1;
            ElementType type2_1 = *it_e2;

            adv1 = getElementAdvantage(type1_1, type2_1);
            adv2 = getElementAdvantage(type2_1, type1_1);

        } else{ // kalau e2 punya 2 elemen
            auto it_e1 = elements_e1.begin();
            auto it_e2 = elements_e2.begin();
            ElementType type1_1 = *it_e1;
            ElementType type2_1 = *it_e2;
            ElementType type2_2 = *(++it_e2);

            if (getElementAdvantage(type1_1, type2_1) >= getElementAdvantage(type1_1, type2_2)){
                adv1 = getElementAdvantage(type1_1, type2_1);
            } else{
                adv1 = getElementAdvantage(type1_1, type2_2);
            }

            if (getElementAdvantage(type1_1, type2_1) >= getElementAdvantage(type1_1, type2_2)){
                adv2 = getElementAdvantage(type1_1, type2_2);
            } else{
                adv2 = getElementAdvantage(type1_1, type2_1);
            }
        }
    }
    else{
        if (elements_e2.size() == 1){ // kalau e1 punya 2 elemen
            auto it_e1 = elements_e1.begin();
            auto it_e2 = elements_e2.begin();
            ElementType type1_1 = *it_e1;
            ElementType type1_2 = *(++it_e1);
            ElementType type2_1 = *it_e2;

            if (getElementAdvantage(type1_1, type2_1) >= getElementAdvantage(type1_2, type2_1)){
                adv1 = getElementAdvantage(type1_1, type2_1);
            } else{
                adv1 = getElementAdvantage(type1_2, type2_1);
            }

            if (getElementAdvantage(type1_1, type2_1) >= getElementAdvantage(type1_2, type2_1)){
                adv2 = getElementAdvantage(type1_2, type2_1);
            } else{
                adv2 = getElementAdvantage(type1_1, type2_1);
            }
        } else{
            auto it_e1 = elements_e1.begin();
            auto it_e2 = elements_e2.begin();
            ElementType type1_1 = *it_e1;
            ElementType type1_2 = *(++it_e1);
            ElementType type2_1 = *it_e2;
            ElementType type2_2 = *(++it_e2);

            if (getElementAdvantage(type1_1, type2_1) >= getElementAdvantage(type1_2, type2_1)){
                if (getElementAdvantage(type1_1, type2_1) >= getElementAdvantage(type1_1, type2_2)){
                    adv1 = getElementAdvantage(type1_1, type2_2);
                }else{
                    adv1 = getElementAdvantage(type1_1, type2_1);
                }
            }
            // else {
            // if (getElementAdvantage(type1_1, type2_1) < getElementAdvantage(type1_2, type2_1)) {
                if (getElementAdvantage(type1_1, type2_1) >= getElementAdvantage(type1_1, type2_2)){
                    adv2 = getElementAdvantage(type1_2, type2_1);
                }else{
                    adv2 = getElementAdvantage(type1_1, type2_1);
                }
            // }
            // Comment : ??????
        }
    }

    //
    // getElementAdvantage(elem_e1,elem_e2)
    // getElementAdvantage(elem_e2,elem_e2)
    sum_e1 += e1->getLevel() * adv1;
    sum_e2 += e2->getLevel() * adv2;
    advantage1 = sum_e1;
    advantage2 = sum_e2;

    // cout << "Power Engimon 1 : " << sum_e1 << endl;
    // cout << "Power Engimon 2 : " << sum_e2 << endl;

    // nek kalah mati raiso buyback
    // int num = getBattleWinner(sum_e1,sum_e2);
    if (sum_e1 > sum_e2){
        winnerNumber = 1;
    } else if (sum_e1 < sum_e2){
        winnerNumber = 2;
    } else{
        winnerNumber = 0;
    }
    // if (num == 1){
    //     // cout << e1->getName() << " menang melawan " << e2->getName() << endl;
    // } else if (num == 2){
    //     cout << e2->getName() << " menang melawan " << e1->getName() << endl;
    // } else{
    //     cout << " Pertandingan seri " << endl;
    // }

    // kalau penyimpanan engimon sek cukup iso masukke
    // entuk exp nek menang
    // dapat skill

}

int Battle::getBattleWinner(){
    return winnerNumber;
}


float Battle::getElementAdvantage(ElementType elem1, ElementType elem2){
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

float Battle::getEngimon1Power() {
    return advantage1;
}

float Battle::getEngimon2Power() {
    return advantage2;
}
