#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

char randomGenerator(int choice) {
    // 1:[A-Za-z0-9], 2:[A-Za-z]
    int r;
    srand(time(NULL));
    switch(choice) {
        case 1: r = rand()%3+1;
                switch(r) {
                    case 1: return char(rand()%26+65);
                    case 2: return char(rand()%26+97);
                    case 3: return char(rand()%10+48);
                }
        case 2: r = rand()%2+1;
                switch(r) {
                    case 1: return char(rand()%26+65);
                    case 2: return char(rand()%26+97);
                }
        default: cout << "Forgot to enter a choice!" << endl;
                 return '~';
    }
}

int main() {
    // [A-Za-z0-9]{4}\.[A-Za-z0-9]{5}@[A-Za-z]{4}\.(com|my|org)
    
    
}