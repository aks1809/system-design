#include <iostream>

using namespace std;

// Interface
class Robot {
    public:
        virtual ~Robot() = default;
        virtual void doStuff() const = 0;
        virtual Robot* copy() const = 0;
};

class Chitti : public Robot{
    public:
        Chitti(){
            cout<<"Chitti constructor called\n";
        }
        void doStuff() const override {
            cout<<"My name is chitti\n";
        }
        Robot* copy() const override {
            return new Chitti(*this);
        }
};

int main() {
    Chitti* robot1 = new Chitti();
    robot1->doStuff();
    Robot* robot2 = robot1->copy();
    robot2->doStuff();
    return 0;
}
