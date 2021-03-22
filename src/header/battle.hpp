

class Battle {
private:
    Engimon* engimon1;
    Engimon* engimon2;
public:
    Battle(Engimon e1, Engimon e2);

    int getBattleWinner();
};
