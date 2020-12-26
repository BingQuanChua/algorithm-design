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
        for (int i = 0; i < 100; i++) {
        cout << charGenerator(4) + "." + charGenerator(5) + "@" + alphaGenerator(4) + "." + domainGenerator() << endl;
    }
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
    return domain[rand()%3];
}