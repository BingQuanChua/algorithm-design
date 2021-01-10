#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "LinkedList.cpp"

template <typename T>

class HashTableChaining
{
    vector<LinkedList<T>> hashtable;

    int hashfunction (string email)
    {
        int i = 0;
        for(int j=0; email[j] ;j++)
            i = i + int(email[j]);
        return i % hashtable.size();
    }

    public:
    HashTableChaining (int size)
    {
        hashtable.resize (size*0.9);
    }

    int size()
    {
        return hashtable.size();
    }

    void insertEmail (T newEmail)
    {
        int index = hashfunction(newEmail);
        hashtable[index].insert(newEmail);
    }

    void searchEmail (T newEmail)
    {
        int index = hashfunction(newEmail);
        if (hashtable[index].find(newEmail) == true)
            cout << newEmail << " can be found in index " << index << endl;
        else
            cout << newEmail << " cannot be found" << endl;
    }

    friend ostream& operator<< (ostream& os, HashTableChaining<T>& ht)
    {
        for (int i = 0; i < ht.size(); i++)
          os << i << " = " << ht.hashtable[i] << endl;
        return os;
    }
};

int main()
{
      vector<string> email;
      vector<string> foundEmail;
      string temp;
      string temp2;
      string insertEmail;
      string searchEmail;
      int insertChoice;
      int searchChoice;
      fstream fileName;
      fstream foundFile;

      cout << "Welcome to Hash Table (Chaining) Program" << endl << endl;
      cout << "Please choose a dataset to insert: " << endl;
      cout << "1. Data Set A - 100 items" << endl;
      cout << "2. Data Set B - 100,000 items" << endl;
      cout << "3. Data Set C - 500,000 items" << endl;
      cout << "Please enter 1, 2 or 3 only: ";
      cin >> insertChoice;
      cout << endl;

      while (insertChoice < 1 || insertChoice > 3)
      {
          cout << "Invalid number !!" << endl;
          cout << "Please enter 1, 2 or 3 only: ";
          cin >> insertChoice;
          cout << endl;
      }

      cout << "Please choose a dataset to search: " << endl;
      cout << "1. Data Set I (Can be found)" << endl;
      cout << "2. Data Set II (Cannot be found)" << endl;
      cout << "Please enter 1 or 2 only: ";
      cin >> searchChoice;
      cout << endl;

      while (searchChoice < 1 || searchChoice > 2)
      {
          cout << "Invalid number !!" << endl;
          cout << "Please enter 1 or 2only: ";
          cin >> searchChoice;
          cout << endl;
      }

      if(insertChoice == 1)
      {
          insertEmail = "datasets/Data Set A.txt";
          if(searchChoice == 1)
            searchEmail = "Search Datasets/Data Set A(Found).txt";
          else
            searchEmail = "Search Datasets/Data Set A(Cannot Found).txt";
      }
      else if (insertChoice == 2)
      {
          insertEmail = "datasets/Data Set B.txt";
          if(searchChoice == 1)
            searchEmail = "Search Datasets/Data Set B(Found).txt";
          else
            searchEmail = "Search Datasets/Data Set B(Cannot Found).txt";
      }
      else
      {
          insertEmail = "datasets/Data Set C.txt";
          if(searchChoice == 1)
            searchEmail = "Search Datasets/Data Set C(Found).txt";
          else
            searchEmail = "Search Datasets/Data Set C(Cannot Found).txt";
      }


      fileName.open(insertEmail, ios :: in);

      if(fileName)
      {
          while(getline(fileName, temp))
          {
              email.push_back(temp);
          }

          HashTableChaining <string> hashtable (email.size());

          auto start = chrono::system_clock::now();
          for(int i =0; i < email.size();i++)
          {
              hashtable.insertEmail(email[i]);
          }
          auto end = chrono::system_clock::now();
          chrono::duration<double> insertDuration = end - start;
          cout << endl;
          if(insertChoice == 1)
          {
             cout << hashtable << endl;
          }
          cout << "Insert Duration: " << insertDuration.count() << "s\n\n";

          foundFile.open(searchEmail, ios::in);

          if(foundFile)
          {
              while(getline(foundFile, temp2))
              {
                  foundEmail.push_back(temp2);
              }

              auto start = chrono::system_clock::now();
              for(int i =0; i < foundEmail.size();i++)
              {
                  hashtable.searchEmail(foundEmail[i]);
              }
              auto end = chrono::system_clock::now();
              chrono::duration<double> searchDuration = end - start;
              cout << "\nSearch Duration: " << searchDuration.count() << "s\n";

              foundFile.close();
          }
          else
          {
              cout << "The file cant be read" << endl;
          }
          fileName.close();
      }
      else
      {
          cout << "The file cant be read" << endl;
      }
      return 0;

}

