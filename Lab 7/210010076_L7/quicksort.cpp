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
listOfObjects<TrainInfoPerStation *> * partition(listOfObjects<TrainInfoPerStation *> *l, listOfObjects<TrainInfoPerStation *> *pivot){
  // set pivot as h element 
    int firstdayofpiv;
    for(int i=0;i<7;i++){
      if(pivot->object->daysOfWeek[i]){firstdayofpiv=i;break;}
    } 
  
    // similar to i = l-1 for array implementation 
    listOfObjects<TrainInfoPerStation *> *i = l->prev; 
  
    // Similar to "for (int j = l; j <= h- 1; j++)" 
    /*for (listOfObjects<TrainInfoPerStation *> *j = l; j != pivot; j = j->next) 
    { 
        if (j->data <= x) 
        { 
            // Similar to i++ for array 
            i = (i == NULL)? l : i->next; 
  
            swap(&(i->data), &(j->data)); 
        } 
    } 
    i = (i == NULL)? l : i->next; // Similar to i++ 
    swap(&(i->data), &(h->data)); 
    return i;
  */ 
} 

listOfObjects<TrainInfoPerStation *> *pivotchooser(int k, int n, listOfObjects<TrainInfoPerStation *> *firststn){
  listOfObjects<TrainInfoPerStation *>* arr[n/k];
  listOfObjects<TrainInfoPerStation *>* currstn=firststn;
  for(int j=0;j<(n/k);j++ ){
    if(j==0){arr[0]=firststn;}
    else{
      for(int i=0;i<k){
        currstn=currstn->next
        }
      arr[j]=currstn;
      }
    }
  //choose random element of array
  //choose random number between 1 and k  
}
void Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
  // Put your code here.

}

void swap(listOfObjects<TrainInfoPerStation *> *s1, listOfObjects<TrainInfoPerStation *> *s2 ){
  TrainInfoPerStation *temp=new TrainInfoPerStation(s2->object->journeyCode,s2->object->stopSeq,s2->object->arrTime,s2->object->depTime);
  s2->object->depTime=s1->object->depTime;
  s2->object->arrTime=s1->object->arrTime;
  s2->object->stopSeq=s1->object->stopSeq;
  s2->object->journeyCode=s1->object->journeyCode;
  for(int i=0;i<7;i++){
    temp->daysOfWeek[i]=s2->object->daysOfWeek[i];
    s2->object->daysOfWeek[i]=s1->object->daysOfWeek[i];
    s1->object->daysOfWeek[i]=temp->daysOfWeek[i];
  }
  s1->object->depTime=temp->depTime;
  s1->object->arrTime=temp->arrTime;
  s1->object->stopSeq=temp->stopSeq;
  s1->object->journeyCode=temp->journeyCode;
}
