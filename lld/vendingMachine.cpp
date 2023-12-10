#include <iostream>
#include <vector>

using namespace std;

struct Product{
    string name;
    string code;
    float price;
    int quantity;
    
    Product(string name, string code, float price, int quantity){
        this->name = name;
        this->code = code;
        this->price = price;
        this->quantity = quantity;
    }
};

class VendingMachine {
    private:
        vector<Product> products;
        float totalAmount;
    public:
        VendingMachine(vector<Product> products){
            this->products = products;
            totalAmount = 0.0;
        }
        void viewProducts(){
            for(auto i:products){
                cout<<"Name: "<<i.name<<", Code: "<<i.code<<", Price: "<<i.price<<", Quantity: "<<i.quantity<<"\n";
            }
        }
        void addAmount(float amount){
            totalAmount+=amount;
            cout<<"Current balance = Rs. "<<totalAmount<<"\n";
        }
        void dispenseProduct(string code){
            for(auto &i:products){
                if(i.code==code){
                    if(i.quantity<1){
                        cout<<"Product: "<<i.name<<" is out of stock\n";
                        return;
                    }
                    if(i.price>totalAmount){
                        cout<<"Insufficient amount, please add more\n";
                        return;
                    }
                    totalAmount-=i.price;
                    i.quantity--;
                    cout<<"Dispensing product: "<<i.name<<"\n";
                    cout<<"Current balance = Rs. "<<totalAmount<<"\n";
                    return;
                }
            }
            cout<<"Invalid code, try again\n";
        }
        void getRefund(){
            cout<<"Refunding amount: "<<totalAmount<<"\n";
            totalAmount=0.0;
        }
};

int main() {
    vector<Product> products = {
        {"Cola", "001", 1.50, 5},
        {"Chips", "002", 1.00, 10},
        {"Candy", "003", 0.75, 8}
    };
    VendingMachine *vendingMachine = new VendingMachine(products);
    vendingMachine->viewProducts();
    vendingMachine->addAmount(1.75);
    vendingMachine->dispenseProduct("002");
    vendingMachine->viewProducts();
    vendingMachine->dispenseProduct("001");
    return 0;
}
