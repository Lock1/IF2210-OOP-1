

class Battle {
private:
    Engimon* engimon1;
    Engimon* engimon2;
public:
    Battle(Engimon e1, Engimon e2);

    int getBattleWinner(int power1, int power2);
    int getElementAdvantange(ElementType elem1, ElementType elem2);
};
