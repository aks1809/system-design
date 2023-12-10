#include <iostream>

using namespace std;

// Interface
class Vehicle {
    public:
        virtual ~Vehicle() = default;
        virtual void printType() const = 0;
};

// Create concrete classes for 2 type of vehicles
class LuxuryVehicle : public Vehicle {
    public:
        LuxuryVehicle(){
            cout<<"LuxuryVehicle constructor invoked\n";
        }
        void printType() const override {
            cout<<"I am Luxury\n";
        }
};

class EconomyVehicle : public Vehicle {
    public:
        EconomyVehicle(){
            cout<<"EconomyVehicle constructor invoked\n";
        }
        void printType() const override {
            cout<<"I am Economy\n";
        }
};

// Create factory
class VehicleFactory {
    public:
        VehicleFactory(){
            cout<<"Vehicle Factory constructor invoked\n";
        }
        Vehicle* getVehicle(string carType) {
            if(carType=="Luxury"){
                return new LuxuryVehicle();
            }else {
                return new EconomyVehicle();
            }
        }
};

int main() {
    VehicleFactory* vehicleFactory = new VehicleFactory();
    Vehicle* grabbedVehicle = vehicleFactory->getVehicle("Luxury");
    grabbedVehicle->printType();
    return 0;
}
