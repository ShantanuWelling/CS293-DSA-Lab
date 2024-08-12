#ifndef SORT_H
#define SORT_H
#endif

#include <stdlib.h>
#include "tree.cpp"
#include "choose.h"

class SorterTree
{
private:   
  Journey* array;
  BST* tree;
  int choice; // Choice of pivot function to use
  int l; // Total number of entries
  int comparisons; // Total number of comparisons performed
  
public:
  SorterTree(int choice, int l,Journey *arr, int comp){ // Define valid constructor
    this->choice=choice;
    this->l=l;
    array=arr;
    this->comparisons=comp;
  };
  int Partition(Journey *arr,int low, int high);
  void Quicksort(int start, int finish); // Sort the array according to the stored values
  void QuicksortWithBSTInsert(int start, int finish, BST * Tree); // May need extra parameters depending on implementation
  void printArray();
  int partn(Journey *arr,int low, int high, Journey *pivotloc);
  bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST
  BST* getTree(); // returns pointer to the tree of pivots
  ~SorterTree(); // Destructor
};
