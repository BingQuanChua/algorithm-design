#include <iostream>
#include <string>
using namespace std;

struct node {
    string d;
    struct node *left;
    struct node *right;

    // deallocate memory to prevent memory leak
    ~node() {
        delete left;
        delete right;
    }
};