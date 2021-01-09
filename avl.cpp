#include <iostream>
#include <string>
#include "Node.cpp"

using namespace std;

class bst {
    
    public:
    struct node *root; 

    node * insert(node *n, string &s) {
        if (n == NULL) {
            // assign node as root 
            n = new node();
            n->d = s;
            n->left = NULL;
            n->right = NULL;
        }
        else {
            if (s.compare(n->d) < 0) {
                n->left = insert(n->left, s);
                n = balance(n);
            }
            else {
                n->right = insert(n->right, s);
                n = balance(n);
            }
        }
        return n;
    }

    node * getSuccessor(node *n) {
        if (n->right == NULL) {
            return n;
        }
        else {
            return getSuccessor(n->right);
        }
    }

    bool searchItem(node *n, string &s) const {
        if (n == NULL) {
            return false; // not found
        }
        else {
            if (s.compare(n->d) == 0) {
                return true;
            }
            else {
                if (s.compare(n->d) < 0) {
                    return searchItem(n->left, s);
                }
                else {
                    return searchItem(n->right, s);
                }
            }
        }
    }

    int getNodeHeight(node *n) {
        if (n == NULL) {
            return 0;
        }
        else {
            int left_h = getNodeHeight(n->left);
            int right_h = getNodeHeight(n->right);
            return max(left_h, right_h) + 1;
        }
    }

    int getBalanceFactor(node *n) {
        int left_h = getNodeHeight(n->left);
        int right_h = getNodeHeight(n->right);
        return right_h - left_h;
    }
    
    node * balance(node *n) {
        int bF = getBalanceFactor(n);
        if (bF < -1) {
            if (getBalanceFactor(n->left) < 0) {
                n = rightRotate(n);
            }
            else {
                n = leftRightRotate(n);
            }
        }
        else {
            if (bF > 1) {
                if (getBalanceFactor(n->right) < 0) {
                    n = rightLeftRotate(n);
                }
                else {
                    n = leftRotate(n);
                }
            }
        }
        return n;
    }

    node * leftRotate(node *n) {
        node *temp = n->right;
        n->right = temp->left;
        temp->left = n;
        return temp;
    }

    node * rightRotate(node *n) {
        node *temp = n->left;
        n->left = temp->right;
        temp->right = n;
        return temp;
    }

    node * leftRightRotate(node *n) {
        node *temp = n->left;
        n->left = leftRotate(temp);
        return rightRotate(n);
    }

    node * rightLeftRotate(node *n) {
        node *temp = n->right;
        n->right = rightRotate(temp);
        return leftRotate(n);
    }

    void show(node *n, int lvl)
    {
        int i;
        if (n != NULL)
        {
            if (n == root)
                cout << "Root: " << n->d << endl;
            else
            {
                cout << n->d << endl;
            }
            cout << lvl << "L: ";
            show(n->left, lvl + 1);
            cout << "\n" << lvl << "R: ";
            show(n->right, lvl + 1);
        }
    }

    bst() {
        root = NULL;
    }
};   

    