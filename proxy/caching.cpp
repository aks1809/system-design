#include <iostream>
#include <unordered_map>

using namespace std;

class WebPage {
    public:
        virtual ~WebPage() = default;
        virtual string getRequest(string url) = 0;
};

class RealPage : public WebPage{
    public:
        string getRequest(string url) override{
            // fetch something off internet
            cout<<"Fetching response without proxy\n";
            return "Response: " + url;
        }
};

class ProxyPage : public WebPage {
    private:
        unordered_map<string, string> um;
        RealPage* realpage = new RealPage();
    public:
        string getRequest(string url){
            auto prevResponse = um.find(url);
            if(prevResponse!=um.end()){
                // response found cached
                cout<<"Found cached response\n";
                return um[url];
            }else{
                // cache this response
                string response = realpage->getRequest(url);
                um[url] = response;
                return response;
            }
        }
};

int main() {
    WebPage* webPage = new ProxyPage();
    cout<<webPage->getRequest("www.google.com")<<"\n";
    cout<<webPage->getRequest("www.yahoo.com")<<"\n";
    cout<<webPage->getRequest("www.google.com")<<"\n";
    return 0;
}
