#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
using namespace std;

template <typename T>
class PriorityQueue {
    vector<T> vect;
    //return the index of parent
    int parentIndex(int index){
        return (index-1)/2;
    }
    // return the index of left child
    int leftChildIndex(int index){
        return (2*index) + 1;
    }
    // return the index of right child
    int rightChildIndex(int index){
        return (2*index) + 2;
    }

    public:
    void enqueue(T element){
        vect.push_back(element);
        heap_Enqueue(vect.size()-1);
    }

    T dequeue(){
        T dequeued_element = vect[0];
        vect[0] = vect[vect.size()-1];
        vect.pop_back();
        heap_Dequeue(0);
        return dequeued_element;
    }

    void heap_Enqueue(int index){
        int parent_index = parentIndex(index);
        if (index > 0 && vect[parent_index] < vect[index]){
            swap(vect[index],vect[parent_index]);
            heap_Enqueue(parent_index);
        }
    }

    void heap_Dequeue(int index){
        int leftChild_index = leftChildIndex(index);
        int rightChild_index = rightChildIndex(index);
        int maxIndex;
        //if left and right nodes are not empty
        if (rightChild_index < vect.size()){
            if(vect[leftChild_index] > vect[rightChild_index]){
                maxIndex = leftChild_index;
            }
            else{
                maxIndex = rightChild_index;
            }
            if(vect[index] > vect[maxIndex]){
                maxIndex = index;
            }
        }
        //if left node not empty
        else if(leftChild_index < vect.size()){
            if (vect[leftChild_index] > vect[index]){
                maxIndex = leftChild_index;
            }
            else{
                maxIndex = index;
            }
        }

        else{
            maxIndex = index;
        }

        if (maxIndex != index) {
          swap (vect[index], vect[maxIndex]);
          heap_Dequeue(maxIndex);
        }
    }

    void show() {
        for (int i = 0; i < vect.size(); i++)
          cout << vect[i] << " ";
        cout << endl;
    }
};

bool getEmail(string fileName, vector<string> &vect)
{
    // open the file
    ifstream inFile(fileName.c_str());
    // Check if object is valid
    if(!inFile)
    {
        cout << "Unable to open the File : " << fileName << endl;
        return false;
    }
    string email="";
    // Read the next line from file until it reaches the end
    while (getline(inFile, email))
    {
        // email contains string of length > 0 then save it in vector
        if(email.size() > 0)
            vect.push_back(email);
    }
    //close the file
    inFile.close();
    return true;
}

void priorityQueue(vector<string> &vect){
    int n = vect.size();
    int partOfData = vect.size()*0.10;
    PriorityQueue<string> pq;
    // Print the vector contents
    if(n <= 100){
        cout << "Below are the email addresses in this dataset:" << endl;
        for (int i = 0; i < n; i++){
            cout<<vect[i]<<endl;
        }
    }
    //take the start time to insert all data into the priority queue
    auto start_Enqueue = chrono::system_clock::now();
    if(n <= 100){
        cout << "\nEnqueue\t\t\t: PriorityQueue\n";
        for (int i = 0; i < n; i++) {
            cout << vect[i] << "\t: ";
            pq.enqueue (vect[i]);
            pq.show();
            cout << endl;
        }
    }
    else{
        for (int i = 0; i < n; i++)
            pq.enqueue (vect[i]);
    }
    //take the end time to insert all data into the priority queue
    auto end_Enqueue = chrono::system_clock::now();

    //take the start time to dequeue 10% of the data
    auto start_Dequeue = chrono::system_clock::now();
    if(n <= 100){
        cout << "\nDequeue\t\t\t: PriorityQueue\n";
        for (int i = 0; i < partOfData; i++) {
            cout << pq.dequeue() << "\t: ";
            pq.show();
            cout << endl;
        }
    }

    else{
        for (int i = 0; i < partOfData; i++)
            pq.dequeue();
    }
    //take the end time to dequeue 10% of the data
    auto end_Dequeue = chrono::system_clock::now();
    //Calculate the duration
    chrono::duration<double> duration_Enqueue = end_Enqueue - start_Enqueue;
    chrono::duration<double> duration_Dequeue = end_Dequeue - start_Dequeue;
    cout << "Duration to insert all data into the priority queue: " << duration_Enqueue.count() << "s" << endl;
    cout << "Duration to dequeue 10% of the data: " << duration_Dequeue.count() << "s" << endl;

}

int main()
{
    vector<string> vectA;
    vector<string> vectB;
    vector<string> vectC;
    int choice = 0;
    bool exit = false;
    bool result_1 = getEmail("C:\\Users\\Ivan\\Desktop\\Datasets\\Data Set A.txt", vectA);
    bool result_2 = getEmail("C:\\Users\\Ivan\\Desktop\\Datasets\\Data Set B.txt", vectB);
    bool result_3 = getEmail("C:\\Users\\Ivan\\Desktop\\Datasets\\Data Set C.txt", vectC);

    do{
    cout << "***************************************" << endl;
    cout << "Priority Queue and Heap Implementation" << endl;
    cout << "***************************************" << endl;
    cout << "Please select one of the datasets below:\n1.Dataset A(100 items)\n2.Dataset B(100,000 items)\n3.Dataset C(500,000 items)\n4.Exit" << endl;
    cout << "Enter your choice: ";
    // Prompt user to enter their choice
    cin >> choice;
    cout << endl;

    switch (choice)
    {
        case 1:
            if(result_1)
                //Dataset A
                priorityQueue(vectA);
            break;
        case 2:
            if(result_2)
                //Dataset B
                priorityQueue(vectB);
            break;
        case 3:
            if(result_3)
                //Dataset C
                priorityQueue(vectC);
            break;
        case 4:
            exit = true;
            break;
        default:
            cout<<"Error! Invalid input...Please enter choice from 0 - 4"<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
    }
    cout << endl;
    } while ( !exit );
    return 0;
}

