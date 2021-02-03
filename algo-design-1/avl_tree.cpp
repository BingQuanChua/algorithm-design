#include <iostream>
#include <chrono>
#include <fstream>
#include "avl.cpp"
#include <vector>
#include <algorithm> 
using namespace std;

bst insertEmailToTree(string &filename, bst tree);
void searchEmailAddresses(string &filename, bst tree);

int main() {

    int choice;
    bool quit = false;

    do {
        bst avl_tree;
        string filename;
    
        cout << "****************************************************************" << endl;
        cout << "                      AVL Binary Search Tree                    " << endl;
        cout << "****************************************************************" << endl;
        cout << "Please select one of the datasets below to be insert into a BST:" << endl;
        cout << "1.Dataset A(100 items)" << endl;
        cout << "2.Dataset B(100,000 items)" << endl;
        cout << "3.Dataset C(500,000 items)" << endl;
        cout << "4.Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: filename = "Data Set A";
                    break;
            case 2: filename = "Data Set B";
                    break;
            case 3: filename = "Data Set C";
                    break;
            default: quit = true;
                     break;
        }

        if(!quit) { // if not exiting
            avl_tree = insertEmailToTree(filename, avl_tree);
            int action;
            bool exit = false;
            string search;

            do {
                cout << endl << "****************************************************************" << endl;
                cout << "Please select one of the actions below to be done to the new AVL Tree:" << endl;
                cout << "1.Search 10 emails that can be found" << endl;
                cout << "2.Search 10 emails that cannot be found" << endl;
                cout << "3.Show AVL Tree" << endl;
                cout << "4.Exit" << endl;
                cout << "Enter your choice: ";
                cin >> action;
                cout << endl;

                switch(action) {
                    case 1: search = filename + "(Found)";
                            searchEmailAddresses(search, avl_tree);
                            break;
                    case 2: search = filename + "(Cannot Found)";
                            searchEmailAddresses(search, avl_tree);
                            break;
                    case 3: avl_tree.show(avl_tree.root, 1);
                            break;
                    default: exit = true;
                             break;
                }
                cout << endl;
            }while (!exit);
        }
    }while(!quit);
    cout << "****************************************************************" << endl;
    return 0;  
}

bst insertEmailToTree(string &filename, bst tree) {
    string email;
    ifstream file("datasets/" + filename + ".txt");
    
    //
    vector<string> vec;
    while(getline(file, email)) {
        vec.push_back(email);
    }
    sort(vec.begin(), vec.end());
    int size = vec.size();

    auto start = chrono::system_clock::now();
    tree.root = tree.insert(tree.root, vec.at(size/2));
    tree.root = tree.insert(tree.root, vec.at(size/2-1));
    for(int i = 0; i < size/2-1; i++) {
        tree.root = tree.insert(tree.root, vec.at(i));
        tree.root = tree.insert(tree.root, vec.at(size-1-i));
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double> duration = end - start;
    cout << endl << "Duration for inserting " + filename + ": " << duration.count() << "s" << endl;
    
    file.close();
    return tree;
}

void searchEmailAddresses(string &filename, bst tree) {
    string email;
    ifstream file("Search Datasets/" + filename + ".txt");

    auto start = chrono::system_clock::now();
    while(getline(file, email)) {
        if(tree.searchItem(tree.root, email)) {
            cout << email << "\tcan be found!" << endl;
        }
        else {
            cout << email << "\tcannot be found" << endl;
        }
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double> duration = end - start;
    cout << endl << "Duration for searching emails in " + filename + ": " << duration.count() << "s" << endl;
}
