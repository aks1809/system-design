#include <iostream>

using namespace std;

class Singleton {
    private:
        Singleton() {}
        static Singleton *instance;
    public:
        static Singleton * getInstance(){
            if(!instance) instance = new Singleton();
            return instance;
        }
        
        void viewMessage(){
            cout<<"This is my message";
        }
};

Singleton *Singleton::instance = nullptr;

int main() {
    Singleton *instance1 = Singleton::getInstance();
    Singleton *instance2 = Singleton::getInstance();
    
    if(instance1 == instance2) {
        cout<<"Equal";
    }else cout<<"Unequal";
    
    instance1->viewMessage();

    return 0;
}
