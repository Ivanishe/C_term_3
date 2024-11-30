#include <iostream>
#include <fstream>
#include <random>

// сделаем абстрактный класс случайной величины из которой будем полиморфизмом строить остальные классы
struct AbstractDice {
    virtual ~AbstractDice() {}
    virtual unsigned roll() = 0;
};

class Dice : public AbstractDice {
public:
    Dice(unsigned max, unsigned seed):
        max(max), dstr(1, max), reng(seed) { }

    unsigned roll() override {
        return dstr(reng);
    }

private:
    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};

class PenaltyDice : public AbstractDice {
public:
    PenaltyDice(AbstractDice &dice) :
        dice(dice) {}
    unsigned roll() override {
        auto first = dice.roll(), second = dice.roll();
        return first <= second ? first : second;
    }
private:
    AbstractDice &dice;
};

class BonusDice : public AbstractDice {
public:
    BonusDice(AbstractDice &dice) :
    dice(dice) {}
    unsigned roll() override {
        auto first = dice.roll(), second = dice.roll();
        return first >= second ? first : second;
    }
private:
    AbstractDice &dice;
};

class DoubleDice : public PenaltyDice, public BonusDice {
public:
    DoubleDice(AbstractDice& dice) :
        PenaltyDice(dice), BonusDice(dice) {}
    unsigned roll() {
        return (PenaltyDice::roll() + BonusDice::roll()) / 2;
    }
};

// expected aka матьожидание
double expected_value(AbstractDice &d, unsigned number_of_rolls = 1) {
    auto accum = 0llu;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
        accum += d.roll();
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

double value_probability(AbstractDice &d, unsigned value, unsigned number_of_rolls = 1) {
    unsigned accum = 0;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
        if (d.roll() == value) accum += 1;
    }
    return static_cast<double>(accum) / number_of_rolls;
}

int main()
{
    int max = 100, number_of_rolls = 1000000;
    
    Dice alpha(max, 1214);
    DoubleDice dice(alpha);
    
    std::cout << expected_value(dice, number_of_rolls) << std::endl;
    
//    std::ofstream outputFile("third.csv");
//    if (!outputFile.is_open()) {
//        std::cerr << "Failed to open the file." << std::endl;
//        return 1;
//    }
//
//    outputFile << "Target\tStandart\tThree\tPenalty\tBonus" << std::endl;
//
//    for (int target = 1; target < max; target++) {
//        outputFile << target << "\t" << value_probability(alpha, target, number_of_rolls) << "\t" <<
//        value_probability(three, target, number_of_rolls) << "\t" <<
//        value_probability(penalty, target, number_of_rolls) << "\t" <<
//        value_probability(bonus, target, number_of_rolls) << std::endl;
//    }
//
//    outputFile.close();
//
//    std::cout << "Data written to third.csv successfully." << std::endl;
    return 0;
}
