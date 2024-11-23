#include <iostream>
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


class ThreeDicePool : public AbstractDice {
public:
    ThreeDicePool(AbstractDice &dice_1, AbstractDice &dice_2, AbstractDice &dice_3) :
        dice_1(dice_1), dice_2(dice_2), dice_3(dice_3) {}
    unsigned roll() override {
        return dice_1.roll() + dice_2.roll() + dice_3.roll();
    }
private:
    AbstractDice &dice_1, &dice_2, &dice_3;
};

// expected aka матьожидание
double expected_value(AbstractDice &d, unsigned number_of_rolls = 1) {
    auto accum = 0llu;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt)
        accum += d.roll();
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}


int main()
{
    Dice cube_1(6, 1);
    Dice cube_2(6, 2);
    Dice cube_3(6, 3);
    
    ThreeDicePool cube_three_pool(cube_1, cube_2, cube_3);

    std::cout << "Random value of one pool: " << cube_1.roll() << " Expected value: " << expected_value(cube_1, 1000) << std::endl;
    std::cout << "Random value of three pool: " << cube_three_pool.roll() << " Expected value: " << expected_value(cube_three_pool, 1000) << std::endl;

    return 0;
}

