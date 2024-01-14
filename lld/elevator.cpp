#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

enum State {
    UP,
    DOWN,
    IDLE
};

struct Request{
    int floor;
    State state;
    public:
        Request(int floor, State state){
            this->floor = floor;
            this->state = state;
        }
};

class Elevator{
    private:
        int currentFloor;
        queue<Request> requests;
        State state;
    public:
        Elevator(){
            currentFloor=0;
            state=IDLE;
        }
        void move(){
            if(!requests.empty()){
                Request currentRequest = requests.front();
                requests.pop();
                 if (currentFloor < currentRequest.floor) {
                    // UP
                    currentFloor = currentRequest.floor;
                    state = UP;
                } else if (currentFloor > currentRequest.floor) {
                    // DOWN
                    currentFloor = currentRequest.floor;
                    state = DOWN;
                } else {
                    state = IDLE;
                }
            }else{
                state=IDLE;
            }
        }
        void addRequest(int floor){
            Request request(floor, IDLE);
            requests.push(request);
        }
        int getCurrentFloor(){
            return currentFloor;
        }
};

class ElevatorManager{
    private:
        vector<Elevator*> elevators;
    public:
        ElevatorManager(int num){
            elevators.resize(num, new Elevator());
        }
        void requestElevator(int elevatorIndex, int floor){
            elevators[elevatorIndex]->addRequest(floor);
        }
        void requestFloor(int floor){
            // check closest elevator
            int minIndex=-1;
            int minDistance=INT_MAX;
            for(int i=0;i<elevators.size();i++){
                if(abs(elevators[i]->getCurrentFloor()-floor)<minDistance){
                    minDistance = abs(elevators[i]->getCurrentFloor()-floor);
                    minIndex = i;
                }
            }
            cout<<"Elevator index: "<<minIndex<<" will serve your request\n";
            elevators[minIndex]->addRequest(floor);
        }
        void move(){
            for(auto &i:elevators){
                i->move();
            }
        }
        void viewCurrentState(){
            int index=0;
            for(auto i:elevators){
                cout<<"Index: "<<index<<", elevator floor: "<<i->getCurrentFloor()<<"\n";
                index++;
            }
        }
};

int main() {
    ElevatorManager* elevatorManager = new ElevatorManager(3);
    elevatorManager->viewCurrentState();
    elevatorManager->requestElevator(0, 4);
    elevatorManager->requestElevator(1, 3);
    elevatorManager->requestElevator(2, 6);
    elevatorManager->viewCurrentState();
    elevatorManager->move();
    elevatorManager->viewCurrentState();
    elevatorManager->requestFloor(1);
    elevatorManager->move();
    elevatorManager->viewCurrentState();
    return 0;
}
