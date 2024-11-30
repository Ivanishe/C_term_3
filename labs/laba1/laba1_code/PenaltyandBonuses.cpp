//#include <iostream>
//#include <fstream>
//#include <random>
//
//// сделаем абстрактный класс случайной величины из которой будем полиморфизмом строить остальные классы
//struct AbstractDice {
//    virtual ~AbstractDice() {}
//    virtual unsigned roll() = 0;
//};
//
//class Dice : public AbstractDice {
//public:
//    Dice(unsigned max, unsigned seed):
//        max(max), dstr(1, max), reng(seed) { }
//
//    unsigned roll() override {
//        return dstr(reng);
//    }
//
//private:
//    unsigned max;
//    std::uniform_int_distribution<unsigned> dstr;
//    std::default_random_engine reng;
//};
//
//
//class ThreeDicePool : public AbstractDice {
//public:
//    ThreeDicePool(AbstractDice &dice_1, AbstractDice &dice_2, AbstractDice &dice_3) :
//        dice_1(dice_1), dice_2(dice_2), dice_3(dice_3) {}
//    unsigned roll() override {
//        return dice_1.roll() + dice_2.roll() + dice_3.roll();
//    }
//private:
//    AbstractDice &dice_1, &dice_2, &dice_3;
//};
//
//class PenaltyDice : public AbstractDice {
//public:
//    PenaltyDice(AbstractDice &dice) :
//        dice(dice) {}
//    unsigned roll() override {
//        auto first = dice.roll(), second = dice.roll();
//        return first <= second ? first : second;
//    }
//private:
//    AbstractDice &dice;
//};
//
//class BonusDice : public AbstractDice {
//public:
//    BonusDice(AbstractDice &dice) :
//    dice(dice) {}
//    unsigned roll() override {
//        auto first = dice.roll(), second = dice.roll();
//        return first >= second ? first : second;
//    }
//private:
//    AbstractDice &dice;
//};
//
//double value_probability(AbstractDice &d, unsigned value, unsigned number_of_rolls = 1) {
//    unsigned accum = 0;
//    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
//        if (d.roll() == value) accum += 1;
//    }
//    return static_cast<double>(accum) / number_of_rolls;
//}
//
//int main()
//{
//    int max = 100, three_max = 6, number_of_rolls = 1000000;
//    
//    Dice alpha(max, 1214);
//    Dice beta(three_max, 12423414);
//    Dice gamma(three_max, 122414);
//    Dice theta(three_max, 213123);
//
//    ThreeDicePool three(beta, gamma, theta);
//    
//    BonusDice bonus(alpha);
//    PenaltyDice penalty(alpha);
//    
////    for(int value = 1; value < max; value++)
////    {
////        std::cout << value << " " << value_probability(alpha, value, 1000) << " " <<
////        value_probability(bonus, value, 1000000) << " " << value_probability(penalty, value, 1000000) << std::endl;
////    }
//    std::ofstream outputFile("second.csv");
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
//    std::cout << "Data written to second.csv successfully." << std::endl;
//    return 0;
//}
//
//
