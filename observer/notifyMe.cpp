#include <iostream>
#include <vector>

using namespace std;

class Observer;

class Observable {
    public:
        virtual ~Observable() = default;
        virtual void update(const Observer* obs) const = 0;
};

class Observer {
    public:
        virtual ~Observer() = default;
        virtual void add(Observable* obs) = 0;
        virtual void del(Observable* obs) = 0;
        virtual void notify() const = 0;
        virtual void addStocks(int stock) = 0;
};

class Iphone : public Observer {
    private:
        int stocks = 0;
        vector<Observable*> subscribed = {};
    public:
        Iphone() {
            cout<<"Iphone constructor\n";
        }
        void add(Observable* obs) override{
            cout<<"Adding obervable to observation list\n";
            subscribed.push_back(obs);
        }
        void del(Observable* obs) override{
            cout<<"Deleting observable from observation list\n";
            subscribed.pop_back();
        }
        void notify() const override {
            cout<<"Notify all the listeners\n";
            for(auto i:subscribed){
                i->update(this);
            }
        }
        void addStocks(int stocks) override {
            this->stocks+=stocks;
            if(this->stocks!=0){
                notify();
            }
        }
};

class MobileClient : public Observable {
    public:
        MobileClient(){
            cout<<"MobileClient constructor\n";
        }
        void update(const Observer* obs) const override {
            cout<<"Update called for MobileClient, "<<obs<<"\n";
        }
};

class TelevisionClient : public Observable {
    public:
        TelevisionClient(){
            cout<<"TelevisionClient constructor\n";
        }
        void update(const Observer* obs) const override {
            cout<<"Update called for TelevisionClient, "<<obs<<"\n";
            if(dynamic_cast<const Iphone*>(obs)) {
                cout<<"Yes";
            }else{
                cout<<"No";
            }
        }
};

int main() {
    MobileClient* mobileClient = new MobileClient();
    TelevisionClient* televisionClient = new TelevisionClient();
    Iphone* iphone = new Iphone();
    iphone->add(mobileClient);
    iphone->add(televisionClient);
    cout<<"Clients added\n";
    iphone->addStocks(100);
    return 0;
}   
