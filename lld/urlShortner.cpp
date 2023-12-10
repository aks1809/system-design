#include <iostream>
#include <unordered_map>

using namespace std;

class URLShortner{
    private:
        unordered_map<string, string> short2long;
        unordered_map<string, string> long2short;
        string getRandomString(int len){
            const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            string res = "";
            for(int i=0;i<len;i++){
                res+=chars[rand()%chars.size()];
            }
            return res;
        }
        
    public:
        string shortenURL(string longURL) {
            auto i=long2short.find(longURL);
            if(i!=long2short.end()){
                return long2short[longURL];
            }else{
                string shortURL = getRandomString(6);
                short2long[shortURL] = longURL;
                long2short[longURL] = shortURL;
                return shortURL;
            }
        }
        
        string lenthenURL(string shortURL) {
            auto i=short2long.find(shortURL);
            if(i!=short2long.end()) return short2long[shortURL];
            else {
                return "NO URL FOUND";
            }
        }
};

int main() {
    URLShortner *urlShortner = new URLShortner();
    string url = "www.google.com";
    cout<<urlShortner->shortenURL(url)<<"\n";
    cout<<urlShortner->lenthenURL(urlShortner->shortenURL(url))<<"\n";
    cout<<urlShortner->lenthenURL("www.yahoo.com")<<"\n";
    return 0;
}
