// Simple email address generator
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

char all[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

string charGenerator(int l);
string alphaGenerator(int l);
string domainGenerator();
bool duplicateValidate(string str, vector<string> &vect);

int main() {
    // declare a string vector
    vector<string> vect;
    // [A-Za-z0-9]{4}\.[A-Za-z0-9]{5}@[A-Za-z]{4}\.(com|my|org)
    string email;
    int count = 1;
    // Generate 10000 email address
    while(count <= 10000){
        email ="";
        email += charGenerator(4);
        email += ".";
        email += charGenerator(5);
        email += "@";
        email += alphaGenerator(4);
        email += ".";
        email += domainGenerator();
        // if no duplicate string is found, add string to the vector
        if (duplicateValidate(email,vect)){
            vect.push_back(email);
            count++;
        }
        else{}
        }

    for(int i = 0; i < vect.size(); i++){
        cout << vect[i] << endl;
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

bool duplicateValidate(string str, vector<string> &vect){
    // return false if duplicate string is found
    if(find(vect.begin(), vect.end(), str) != vect.end())
        return false;
    else
        return true;
}
