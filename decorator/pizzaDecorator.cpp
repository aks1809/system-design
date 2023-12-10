#include <iostream>

using namespace std;

// Interface
class Pizza {
    public:
        virtual ~Pizza() = default;
        virtual int price() const = 0;
};

class BasePizza : public Pizza {
    public:
        BasePizza(){
            cout<<"Base Pizza constructor\n";
        }
        int price() const override{
            return 100;
        }
};

class MushroomToppings : public Pizza {
    Pizza* basePizza;
    public:
        MushroomToppings(Pizza* basePizza) {
            cout<<"MushroomToppings constructor\n";
            this->basePizza = basePizza;
        }
        int price () const override{
            return 10+basePizza->price();
        }
};

class PaneerToppings : public Pizza {
    Pizza* basePizza;
    public:
        PaneerToppings(Pizza* basePizza) {
            cout<<"PaneerToppings constructor\n";
            this->basePizza = basePizza;
        }
        int price () const override{
            return 20+basePizza->price();
        }
};

int main() {
    Pizza* pizza = new PaneerToppings(new MushroomToppings(new PaneerToppings(new BasePizza())));
    cout<<pizza->price();
    return 0;
}
