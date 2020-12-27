// Simple email address generator
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

static char all[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
static char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void generateEmail(string filename, int num);
string charGenerator(int l);
string alphaGenerator(int l);
string domainGenerator();
bool duplicateValidate(string str, vector<string> &vect);

int main() {
    srand(time(NULL));
    generateEmail("setA", 100);
    // generateEmail("setB", 100000);
    // generateEmail("setC", 500000); 

    return 0;
}

// generates email data, also generates a .txt file for reference
void generateEmail(string filename, int num) {
    ofstream file; 
    file.open(filename + ".txt");

    // declare a string vector
    vector<string> vect;
    // email format: [A-Za-z0-9]{4}\.[A-Za-z0-9]{5}@[A-Za-z]{4}\.(com|my|org)
    string email;
    int count = 1;
    // Generate specified number of email addresses
    while(count <= num){
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
            file << email << endl;
            count++;
        }
        else{
            continue; // data not recorded
        }
    }

    for(int i = 0; i < vect.size(); i++){
        cout << vect[i] << endl;
    }

    // close file
    file.close();

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
