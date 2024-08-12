#include <stdlib.h>
#include <iostream>
#include <cassert>
#include "sort.cpp"
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<<"Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)
    int N=num_entries;
    Journey input[N];
    for(int i=0; i<N;i++){
        int jc,price;
        cin>>jc>>price;
        input[i]=Journey(jc,price);
    }
    
    cout<<"Enter 0 for Quicksort test"<<endl;
    cout<<"Enter 1 for Quicksort with BST insert test"<<endl;
    cout<<"Enter 2 for Get Imbalance test"<<endl;
    int inp;
    cin>>inp;
    if (inp==0){
        SorterTree *b= new SorterTree(pivot_chooser,N,input);
        b->Quicksort(0,N-1);
        b->printArray();
    }
    else if (inp==1){
        SorterTree *b= new SorterTree(pivot_chooser,N,input);
        BST newtree;
        b->QuicksortWithBSTInsert(0,N-1,&newtree);
        b->printArray();
        cout<<endl;
        newtree.printBST("");
    }
    else if(inp==2){
        SorterTree *b= new SorterTree(pivot_chooser,N,input);
        BST newtree;
        b->QuicksortWithBSTInsert(0,N-1,&newtree);
        cout<<endl;
        newtree.printBST("");
        cout<<endl;
        cout<<"Imbalance is: "<<newtree.getImbalance()<<endl;
    }
    else cout<<"Invalid command"<<endl;
}
