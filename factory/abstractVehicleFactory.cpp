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

class VehicleFactoryInterface {
    public:
        virtual ~VehicleFactoryInterface() = default;
        virtual Vehicle* getInstance() const = 0;
};

// Create luxury vehicle factory
class LuxuryVehicleFactory : public VehicleFactoryInterface {
    public:
        LuxuryVehicleFactory(){
            cout<<"LuxuryVehicleFactory constructor invoked\n";
        }
        Vehicle* getInstance() const override {
            // option to choose from different luxury vehicles if multiple
            return new LuxuryVehicle();
        }
};

class EconomyVehicleFactory : public VehicleFactoryInterface {
    public:
        EconomyVehicleFactory(){
            cout<<"EconomyVehicleFactory constructor invoked\n";
        }
        Vehicle* getInstance() const override {
            // option to choose from different economy vehicles if multiple
            return new EconomyVehicle();
        }
};

class VehicleFactory {
    public:
        VehicleFactory(){
            cout<<"Vehicle Factory constructor invoked\n";
        }
        VehicleFactoryInterface* getVehicle(string type) {
            if(type=="Luxury"){
                return new LuxuryVehicleFactory();
            }else {
                return new EconomyVehicleFactory();
            }
        }
};

int main() {
    VehicleFactory* vehicleFactory = new VehicleFactory();
    VehicleFactoryInterface* grabbedVehicleType = vehicleFactory->getVehicle("Luxury");
    Vehicle* actualVehicle = grabbedVehicleType->getInstance();
    actualVehicle->printType();
    return 0;
}
