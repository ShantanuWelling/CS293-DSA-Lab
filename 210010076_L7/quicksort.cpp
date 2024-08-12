#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

#include <random>

// If you are using the updated planner.cpp, then you simply need to
// sort the list of TrainInfoPerStation objects in stnInfoList.  The
// function that calls Quicksort in planner.cpp (i.e. printStationInfo)
// will then automatically pretty-print the sorted list.
//
// USING THE UPDATED planner.cpp FILE IS STRONGLY RECOMMENDED
//
// Notice that there is a variable K in Quicksort that is to be used as
// described in the problem statement in problems_statement.pdf
// Specifically, if the first call to Quicksort has an argument list of
// n TrainInfoPerStation objects, you can't use additional storage space
// for more than n/K TrainInfoPerStation objects overall (across all
// recursive calls), you must implement random choice for pivot (i.e.
// each element in the list being sorted should be equally likely to
// be chosen as pivot), and each call to finding a random pivot
// within the list being sorted must take time within O(K), regardless
// of how long the list to be sorted is.
//
// In the function signature of Quicksort, stnInfoList is a list of
// TrainInfoPerStation objects that is to be sorted. In the updated
// planner.cpp file, this list (unsorted) is already prepared for you,
// and you need to simply ensure that the list is sorted (see note
// below about sorting order) when Quicksort returns.
//
// A note about the sorting order:
//
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next).  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200
//
//
// Based on how we saw some of you were trying to approach the problem
// in the lab of Sep 23, we are providing another function QuicksortSimple
// with a slightly extended signature. In addition to the list stnInfoList,
// which is passed as the first argument to QuicksortSimple, there are two
// integer parameters "start" and "end", just like in the usual Quicksort
// of an array (as in Prof. Naveen Garg's lectures, for example).
// How do we interpret these "start" and "end" variables in this case,
// when we are trying to sort a list?
// Well, here is one way of thinking about this: If we start
// counting elements of the list starting from stnInfoList and
// chasing "next" pointers until nullptr is reached, the corresponding
// elements can be thought of as elements of a (virtual) array indexed
// from 0 onwards.
// Then, the call to Quicksort must sort the part of the list
// consisting of elements at indices start, start+1, ... until end
// of the above virtual array.
// The whole point of this assignment is to have you do this without
// converting the whole list to an array.
//
// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument.  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.

void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> *end=nullptr; //Stores endpointer of current sublist to be sorted
  static listOfObjects<TrainInfoPerStation *>** arr; //array for pivot choosing
  static int currend; //last element in current sublist
  static int currstart=0; //first element in current sublist
  static int n=1; //Total number of elements in entire list
  // Increment recursion level on entering the function
  recursionLevel++;
  
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  
  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    listOfObjects<TrainInfoPerStation *>* currstn=stnInfoList; //Pointer to count total stations
    while(currstn->next!=nullptr){
      currstn=currstn->next;
      n++; //Count total stations
    }
    end=currstn;
    if(n/K==0) { 
      arr=new listOfObjects<TrainInfoPerStation *>*[1]; //Make only 1 space for pivot choosing
      arr[0]=stnInfoList; //Array for pivot choosing
    }
      
    else {
      arr=new listOfObjects<TrainInfoPerStation *>*[n/K]; //Array for pivot choosing
      currstn=stnInfoList; 
      for(int j=0;j<(n/K);j++){//Store elements in array at an interval of k in the original list
        if(j==0){arr[0]=stnInfoList;}
        else{
          for(int i=0;i<K;i++){
            currstn=currstn->next;
            }
          arr[j]=currstn;
          }
        }
    }
    currend=n-1; //set index of end element in first call
  }
  
  // Put your code for the core of Quicksort here

  if(end!=nullptr && stnInfoList!=end && stnInfoList!=end->next && currstart>=0 && currstart<n && currend>=0 && currend<n && currstart!=currend){
  default_random_engine generator;
  uniform_int_distribution<int> distribution(currstart,currend); //Generate uniform number between the indices of current sublist to be sorted
  int index=distribution(generator);
  listOfObjects<TrainInfoPerStation *>* pivot; //pivot
  if(n/K==1){ //Set pivot according to the random number generated
    pivot=arr[0];
    for(int z=1;z<= index;z++){
      //Since n/K is 1 so n can be atmost 2k-1, and index is always less than n so [O(k)] as (2k-1)
      pivot=pivot->next;
    }
  }
  else{
    pivot=arr[index/K];
    for(int z=1;z<= (index%K);z++){ //[O(k)]
      pivot=pivot->next;
    }
  }
  listOfObjects<TrainInfoPerStation *>* pivotind=partition(stnInfoList,pivot,end); //Partition [O(n)]
  int pivotindex=0; //Find pivot index in current sublist [O(n)]
  listOfObjects<TrainInfoPerStation *>* check=arr[0];
  while(check->next!=nullptr){
    if(check==pivotind) break;
    else{pivotindex++;check=check->next;}
  }
  int temp=currstart;
  currstart=pivotindex+1; //Update static parameters before calling quicksort on the sublist
  Quicksort(pivotind->next); //Quicksort sublist ahead of pivot
  end=pivotind->prev; //Update static parameters
  currstart=temp;
  currend=pivotindex-1;
  Quicksort(stnInfoList); //Quicksort sublist before pivot
  }
  // Decrement recursion level before leaving the function
  if(recursionLevel==0){
    delete [] arr; //Reset static parameters before leaving the function
    currstart=0;
    n=1;
    currend=0;
    end=nullptr;
  }
  recursionLevel--;
  return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
  // A few static variable declarations
  static int K = 4; // Parameter to be experimented with
  static int recursionLevel = -1; // This can be used to find out at which
                                  // level of the recursion you are in
  static listOfObjects<TrainInfoPerStation *> *end1=nullptr; //Stores endpointer of current sublist to be sorted
  static listOfObjects<TrainInfoPerStation *>** arr; //array for pivot choosing
  static int n=1; //Total number of elements in entire list
  // Increment recursion level on entering the function
  recursionLevel++;
  
  // If you need to set up additional storage (upto n/K TrainInfoPerStation
  // elements), it's ok to do it *once* using static variables/array.
  // Using the static recursionLevel, you can ensure that the storage
  // allocation is done only the first time Quicksort is called, and not
  // in every recursive call.
  //
  // Note that if you allocate space for upto n/K TrainInfoPerStation in
  // each recursive call, you will end up using much more than n/K space
  // overall.  So you MUST NOT allocate space in each recursive call.
  //
  // A variable/array defined using static is not created afresh in
  // each recursive call.  Instead, a single copy of it is maintained
  // across all recursions.
  
  if (recursionLevel == 0) {
    // Find length of the list stnInfoList, if needed.
    // Allocate additional space for upto n/K TrainInfoPerStation objects
    // if needed.
    // Do other things that you may want to do only at the beginning
    // as a pre-processing step.
    listOfObjects<TrainInfoPerStation *>* currstn=stnInfoList; //Pointer to count total stations
    while(currstn->next!=nullptr){
      currstn=currstn->next;
      n++; //Count total stations
    }
    end1=currstn;
    if(n/K==0) { 
      arr=new listOfObjects<TrainInfoPerStation *>*[1]; //Make only 1 space for pivot choosing
      arr[0]=stnInfoList; //Array for pivot choosing
    }
      
    else {
      arr=new listOfObjects<TrainInfoPerStation *>*[n/K]; //Array for pivot choosing
      currstn=stnInfoList; 
      for(int j=0;j<(n/K);j++){//Store elements in array at an interval of k in the original list
        if(j==0){arr[0]=stnInfoList;}
        else{
          for(int i=0;i<K;i++){
            currstn=currstn->next;
            }
          arr[j]=currstn;
          }
        }
    }
  }
  
  // Put your code for the core of QuicksortSimple here
  if(end1!=nullptr && stnInfoList!=end1 && stnInfoList!=end1->next && start>=0 && start<n && end>=0 && end<n && start!=end){
  default_random_engine generator;
  uniform_int_distribution<int> distribution(start,end); //Generate uniform number between the indices of current sublist to be sorted
  int index=distribution(generator);
  listOfObjects<TrainInfoPerStation *>* pivot; //pivot
  if(n/K==1){ //Set pivot according to the random number generated
    pivot=arr[0];
    for(int z=1;z<= index;z++){
      //Since n/K is 1 so n can be atmost 2k-1, and index is always less than n so [O(k)] as (2k-1)
      pivot=pivot->next;
    }
  }
  else{
    pivot=arr[index/K];
    for(int z=1;z<= (index%K);z++){ //[O(k)]
      pivot=pivot->next;
    }
  }
  listOfObjects<TrainInfoPerStation *>* pivotind=partition(stnInfoList,pivot,end1); //Partition [O(n)]
  int pivotindex=0; //Find pivot index in current sublist [O(n)]
  listOfObjects<TrainInfoPerStation *>* check=arr[0];
  while(check->next!=nullptr){
    if(check==pivotind) break;
    else{pivotindex++;check=check->next;}
  }
  int temp=start;
  QuicksortSimple(pivotind->next,pivotindex+1,end); //Quicksort sublist ahead of pivot
  end1=pivotind->prev; //Update static parameters
  QuicksortSimple(stnInfoList,temp,pivotindex-1); //Quicksort sublist before pivot
  }
  // Decrement recursion level before leaving the function
  if(recursionLevel==0){
    delete [] arr; //Reset static parameters before leaving the function
    n=1;
    end1=nullptr;
  }
  recursionLevel--;
  return;
}

//Partition function
listOfObjects<TrainInfoPerStation *> * Planner::partition(listOfObjects<TrainInfoPerStation *> *l, listOfObjects<TrainInfoPerStation *> *pivot, listOfObjects<TrainInfoPerStation *> *end ){
    int firstdayofpiv; //Find first train day of pivot
    for(int i=0;i<7;i++){
      if(pivot->object->daysOfWeek[i]){firstdayofpiv=i;break;}
    } 
  
    listOfObjects<TrainInfoPerStation *> *left=l; //Left most element
    listOfObjects<TrainInfoPerStation *> *right=pivot->next; //Element next of pivot
    while(left!=nullptr && left!=pivot && right!=nullptr && right!=end->next){//Keep comparing left and right and swapping them
      int firstleft;
      int firstright;
      for(int i=0;i<7;i++){//First train day of left
            if(left->object->daysOfWeek[i]){firstleft=i;break;}
          }
      for(int i=0;i<7;i++){//First train day of right
            if(right->object->daysOfWeek[i]){firstright=i;break;}
          }
      bool leftswap=false, rightswap=false; //Bool if left or right is to be swapped
      //If satisfy swapping condition set these bools to true
      //If both are true perform swap and update both to next
      //Else if any is false update them to next
      if((firstleft>firstdayofpiv) || (left->object->depTime>pivot->object->depTime && (firstleft==firstdayofpiv))) leftswap=true;
      if((firstright<firstdayofpiv) || (right->object->depTime<pivot->object->depTime && (firstright==firstdayofpiv))) rightswap=true;
      if(leftswap && rightswap){
        swap(left->object,right->object);
        left=left->next;
        right=right->next;
      }
      else{
        if(!leftswap) left=left->next;
        if(!rightswap) right=right->next;
      }
    }
    //While loop exited: 2 conditions
    //If left of pivot is exhausted and right hasn't been iterated completely
    //Or left not iterated completely and right exhausted
    //Then iterate through the other half and swap with pivot or swaploc which keeps updating to next after each swap
    if((left==pivot || left==nullptr) && right!=nullptr && right!=end->next){
      listOfObjects<TrainInfoPerStation *> *nleft=pivot->next; //Iterator for the other half
      listOfObjects<TrainInfoPerStation *> *swaploc=pivot; //Swap location initialized to pivot
      while (nleft!=nullptr && nleft!=end->next){
        int newfleft;
        for(int i=0;i<7;i++){//Find first train day of iterator
            if(nleft->object->daysOfWeek[i]){newfleft=i;break;}
          }
        if((newfleft<firstdayofpiv)||(nleft->object->depTime<pivot->object->depTime && (newfleft==firstdayofpiv))){
          swap(nleft->object,swaploc->object);
          if(swaploc==pivot) pivot=nleft; //If swapped with pivot, update pivot pointer
          swaploc=swaploc->next; //Update swaploc and iterator
          nleft=nleft->next;
        }
        else nleft=nleft->next; //If not swapped, update iterator
      }
      swap(swaploc->object,pivot->object); //Finally swap pivot with the last swaploc
      pivot=swaploc; //Update pivot pointer
    }//Same for the other half case, just reverse direction and iterations
    else if (left!=nullptr && left!=pivot && (right==nullptr || right==end->next)){
      listOfObjects<TrainInfoPerStation *> *nright=pivot->prev;
      listOfObjects<TrainInfoPerStation *> *swaploc=pivot;
      while (nright!=nullptr && nright!=left->prev){
        int newright;
        for(int i=0;i<7;i++){
            if(nright->object->daysOfWeek[i]){newright=i;break;}
          }
        if((newright>firstdayofpiv)||(nright->object->depTime>pivot->object->depTime && (newright==firstdayofpiv))){
          swap(nright->object,swaploc->object);
          if(swaploc==pivot) pivot=swaploc;
          swaploc=swaploc->prev;
          nright=nright->prev;
        }
        else nright=nright->prev;
      }
      swap(swaploc->object,pivot->object);
      pivot=swaploc;
    }
    return pivot; //Finally return pivot
}

#endif

//Used one extra listOfObjects<TrainInfoPerStation *> variable as static int
//Used one extra listOfObjects<TrainInfoPerStation *> variable as pivot
//Used one extra listOfObjects<TrainInfoPerStation *> variable as iterator in quicksort to find length of initial list
//Used 2 extra listOfObjects<TrainInfoPerStation *> variable as iterator in partition
//Total a constant number of extra variables
//Used floor(n/K) variables in array instead of ceil(n/K)