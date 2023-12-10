#include <iostream>

using namespace std;

enum LogLevel {
    INFO,
    DEBUG,
    ERROR,
    RANDOM
};

class Logger {
    public:
        virtual ~Logger() = default;
        virtual void log(LogLevel level, string msg) = 0;
};

class ErrorLogger : public Logger {
    private:
        Logger* successor;
    public:
        ErrorLogger(Logger* successor){
            this->successor = successor;
        }
        void log(LogLevel level, string msg) override{
            if(level == ERROR){
                cout<<"ERROR: "<<msg<<"\n";
            }else if(successor){
                successor->log(level, msg);
            }else{
                cout<<"Handler not available\n";
            }
        }
};

class DebugLogger : public Logger {
    private:
        Logger* successor;
    public:
        DebugLogger(Logger* successor){
            this->successor = successor;
        }
        void log(LogLevel level, string msg) override{
            if(level == DEBUG){
                cout<<"DEBUG: "<<msg<<"\n";
            }else if(successor){
                successor->log(level, msg);
            }else{
                cout<<"Handler not available\n";
            }
        }
};

class InfoLogger : public Logger {
    private:
        Logger* successor;
    public:
        InfoLogger(Logger* successor){
            this->successor = successor;
        }
        void log(LogLevel level, string msg) override{
            if(level == INFO){
                cout<<"INFO: "<<msg<<"\n";
            }else if(successor){
                successor->log(level, msg);
            }else{
                cout<<"Handler not available\n";
            }
        }
};

int main() {
    Logger* logger = new InfoLogger(new DebugLogger(new ErrorLogger(NULL)));
    logger->log(RANDOM, "This is info log");
    return 0;
}   
