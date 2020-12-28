// Simple email address generator
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
using namespace std;

static char all[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
static char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void generateEmail(string filename, int num);
bool searchDuplicate(string array[], int start, int end, string target);
void insertSorted(string array[], int n, string key);
string charGenerator(int l);
string alphaGenerator(int l);
string domainGenerator();
// bool duplicateValidate(string str, vector<string> &vect);

int main() {
    srand(time(NULL));
    generateEmail("setA", 10);
    // generateEmail("setB", 100000);
    // generateEmail("setC", 500000); 
    return 0;
}

// generates email data, also generates a .txt file for reference
void generateEmail(string filename, int num) {
    ofstream file; 
    file.open(filename + ".txt");

    // array of string
    string emailSet[num] = "0";
    // email format: [A-Za-z0-9]{4}\.[A-Za-z0-9]{5}@[A-Za-z]{4}\.(com|my|org)
    string email;
    int count = 1;
    auto start = chrono::system_clock::now();
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
        cout << email << endl;
        // if no duplicate string is found, add string to the array
        if (!searchDuplicate(emailSet, 0, count-1, email)){ // check duplicates
            cout << "no duplicate.." << endl;
            insertSorted(emailSet, count-1, email);
            cout << "email inserted" << endl;
            count++;
        }
        else {
            cout << "duplicated" << endl;
        }
    }

    for (string &email : emailSet) {
        file << email << endl;
    }
    
    auto end = chrono::system_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Duration for generating " + filename + " " << duration.count() << "s" << endl;
    // close file
    file.close();

}

// search for duplicates
// modified binary search for strings
bool searchDuplicate(string array[], int start, int end, string target) {
    if (end == 0) {
        return false; // empty array
    }
    while (start <= end) {
        int middle = start+(end-1)/2;

        if (target.compare(array[middle]) == 0) {
            return true; // string is found, duplicate exists
        }

        if (target.compare(array[middle]) > 0)  {
            start = middle + 1;
        }
        else {
            end = middle - 1;
        }
    }
    return false; // string not found, duplicate does not exists
}

// insert into sorted array
void insertSorted(string array[], int n, string key) {
    int i;
    for (i = n-1; i >= 0 && key.compare(array[i]) < 0; i--) {
        array[i+1] = array[i];
    }
    array[i+1] = key;
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

/*
bool duplicateValidate(string str, vector<string> &vect){
    // return false if duplicate string is found
    if(find(vect.begin(), vect.end(), str) != vect.end())
        return false;
    else
        return true;
}
*/
