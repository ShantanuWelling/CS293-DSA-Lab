#include "sort.h"
#include <iostream>

// Code up the functions defined in sort.cpp

int SorterTree::Partition(Journey *arr,int low, int high){
    int i = (low - 1); 
    Journey piv=arr[high]; //Pivot as the last element -partition algorithm
    for(int j=low;j<=high;j++){
    if (arr[j] < piv) {
        i++;
        Journey temp=arr[j];
        arr[j]=arr[i];
        arr[i]=temp;
   }
}
arr[high]=arr[i+1];
arr[i+1]=piv;
return (i+1);
}

int SorterTree::partn(Journey *arr,int low, int high, Journey *pivotloc){
    Journey temp=*pivotloc; 
    *pivotloc=arr[high]; //Swap pivot with right most element
    arr[high]=temp;
    return Partition(arr,low,high); //Perform partition when pivot is the last element
}

void SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    Journey *pivot;

    if(choice==1){pivot=choose_one(array,start, finish);}
    else if (choice==2){pivot=choose_two(array,start, finish);}
    else if (choice==3){pivot=choose_three(array,start, finish);}

    if(start < finish){
        int pivotind=partn(array,start,finish,pivot);
        Quicksort(start, pivotind - 1);
        Quicksort(pivotind + 1, finish);
    }
}

void SorterTree::QuicksortWithBSTInsert(int start, int finish, BST *Tree)
{   // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    Journey *pivot;
    if (start<finish){
        if(choice==1){pivot=choose_one(array,start, finish);}
        else if (choice==2){pivot=choose_two(array,start, finish);}
        else if (choice==3){pivot=choose_three(array,start, finish);}
        Tree->insert(pivot->getJourneyCode(),pivot->getPrice());
    }
    if(start < finish){
        int pivotind=partn(array,start,finish,pivot);
        QuicksortWithBSTInsert(start, pivotind - 1, Tree);
        QuicksortWithBSTInsert(pivotind + 1, finish, Tree);
    }
    return;
}

void SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<"\tJourney Price:"<<array[i].getPrice()<<std::endl;
    }
}
