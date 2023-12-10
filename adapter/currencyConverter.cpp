#include <iostream>

using namespace std;

class CurrencyConvertor{
    public:
        virtual ~CurrencyConvertor() = default;
        virtual float getConversion() = 0;
};

class OldValue {
    public:
        float getValue() const{
            return 20;
        }
};

class CurrencyConvertorAdapter : public CurrencyConvertor{
    OldValue* oldValue;
    public:
        CurrencyConvertorAdapter(OldValue* oldValue){
            this->oldValue = oldValue;
        }
        float getConversion(){
            float valueInINR = oldValue->getValue();
            return valueInINR*80;
        }
};

int main() {
    CurrencyConvertor* currencyConvertor = new CurrencyConvertorAdapter(new OldValue());
    cout<<currencyConvertor->getConversion();
    return 0;
}
