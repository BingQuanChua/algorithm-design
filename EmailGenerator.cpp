#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char all[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

string charGenerator(int l);
string alphaGenerator(int l);
string domainGenerator();

int main() {
    // [A-Za-z0-9]{4}\.[A-Za-z0-9]{5}@[A-Za-z]{4}\.(com|my|org)
    string email;
    email += charGenerator(4);    
    email += ".";
    email += charGenerator(5);  
    email += "@";
    email += alphaGenerator(4);
    email += ".";
    email += domainGenerator();
    cout << email << endl;
    return 0;
}

string charGenerator(int l) {
    string ans;
    for (int i = 0; i < l; i++) {
        ans += all[rand()%62];
    }
    return ans;
}

string alphaGenerator(int l) {
    string ans;
    for (int i = 0; i < l; i++) {
        ans += alphabet[rand()%52];
    }
    return ans;
}

string domainGenerator() {
    string domain[] = {"com", "my", "org"};
    return domain[rand()%2];
}