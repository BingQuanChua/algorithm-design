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

void generateEmail(string filename, int num);
string charGenerator(int l);
string alphaGenerator(int l);
string domainGenerator();
bool duplicateValidate(string &str, vector<string> &vect);

int main() {
    srand(time(NULL));
    bool exit = false;
    int choice = 0;

    do{
    cout << "****************" << endl;
    cout << "Data Generation" << endl;
    cout << "****************" << endl;
    cout << "Please select one of the datasets below:\n1.Dataset A(100 items)\n2.Dataset B(100,000 items)\n3.Dataset C(500,000 items)\n4.Exit" << endl;
    cout << "Enter your choice: ";
    // Prompt user to enter their choice
    cin >> choice;
    cout << endl;

    switch (choice)
    {
        case 1:
                //Dataset A
                generateEmail("Data Set A", 100);
            break;
        case 2:
                //Dataset B
                generateEmail("Data Set B", 100000);
            break;
        case 3:
                //Dataset C
                generateEmail("Data Set C", 500000);
            break;
        case 4:
            exit = true;
            break;
        default:
            cout<<"Error! Invalid input...Please enter choice from 1 - 4"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
    }
    cout << endl;
    } while ( !exit );

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
    auto start = chrono::system_clock::now();
    // Generate specified number of email addresses
    while(count <= num){
        email = "";
        email += charGenerator(4);
        email += ".";
        email += charGenerator(5);
        email += "@";
        email += alphaGenerator(4);
        email += ".";
        email += domainGenerator();
        // if no duplicate string is found, add string to the vector
        if (duplicateValidate(email,vect)){
            if(count != 1) {
                file << endl;
            }
            vect.push_back(email);
            file << email;
            count++;
        }
        else{
            continue; // data not recorded
        }
    }

    auto end = chrono::system_clock::now();
    chrono::duration<double> duration = end - start;

    for(int i = 0; i < vect.size();i++){
        cout << vect[i] << endl;
    }
    cout << "\nDuration for generating " + filename + " " << duration.count() << "s" << endl;
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
        ans += all[rand()%52];
    }
    return ans;
}

string domainGenerator() {
    string domain[] = {"com", "my", "org"};
    return domain[rand()%3];
}

bool duplicateValidate(string &str, vector<string> &vect){
    // return false if duplicate string is found
    if(find(vect.begin(), vect.end(), str) != vect.end())
        return false;
    else
        return true;
}
