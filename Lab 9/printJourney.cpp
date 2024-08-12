#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{
  // insert your code here
  listOfObjects<TrainInfoPerStation *> *res=nullptr; //Final output list of trains 
  int srcind = stnNameToIndex.get(srcStnName)->value; //Index of source station
  int desind = stnNameToIndex.get(destStnName)->value; //Index of destination station
  listOfObjects<int> *jind=nullptr; //List of journey code (BFS Queue)
  listOfObjects<int> *stnind=nullptr; //List of station index (BFS Queue)
  listOfObjects<int> *resjc=nullptr; //Resultant list of journey codes of direct journeys between source and destination
  int arrsize=0; //Size of the BFS queue
  int rc=0; //Size of resjc
  
  //Each station of stnind queue corresponds to the respective element
  //of jind queue (which stores journey index of the train that connects
  // it to the source station). Enqueue and dequeue operations are performed
  // on both queues simultaneously.
  listOfObjects<StationConnectionInfo *> *itr= adjacency[srcind].toStations; //Initial iterator
  if(itr==nullptr) {cout<<"No direct journeys available"<<endl; return;} //If no edges from station
  
  while(true){//Iterate over adjacent stations from source station (level 1)
    listOfObjects<TrainInfoPerStation *> *trainitr=itr->object->trains; //Iterate over trains of adjacent stations
    if(trainitr!=nullptr){
    while(true){
      if(stnind==nullptr){ //Initialize BFS queue of stations
        stnind= new listOfObjects<int>(itr->object->adjacentStnIndex);
      }
      else{ // Add station to BFS Queue of stations
        listOfObjects<int>* temp1= stnind;
        stnind=stnind->next;
        stnind= new listOfObjects<int>(itr->object->adjacentStnIndex);
        stnind->prev=temp1;
        temp1->next=stnind;
      }
      if(jind==nullptr){ //Initialize BFS queue of journeycodes
        jind= new listOfObjects<int>(trainitr->object->journeyCode);
      }
      else{ // Add journeycode of the corresponding station's trains to BFS queue of journeycodes
        listOfObjects<int>* temp2= jind;
        jind=jind->next;
        jind= new listOfObjects<int>(trainitr->object->journeyCode);
        jind->prev=temp2;
        temp2->next=jind;
      }
      arrsize++; //Update size of BFS queue
      if(trainitr->next==nullptr){break;} //If trainlist exhausted then break
      else trainitr=trainitr->next; //Else move on to process the next train of the same station
    }
    }
    if(itr->next==nullptr){break;} //If toStations list exhausted then break
    else itr=itr->next; //Else move on to process the next adjacent station
  }
  //Maintain pointers to last element of BFS queues for enqueue operation
  listOfObjects<int> * currj= jind; //Pointer to last element of journeycode BFS queue
  listOfObjects<int> * currs= stnind; //Pointer to last element of station BFS queue
  while(jind->prev!=nullptr){//Go to the start of BFS queue for further operations
    jind=jind->prev;
  }
  while(stnind->prev!=nullptr){//Go to the start of BFS queue for further operations
    stnind=stnind->prev;
  }
  while(arrsize>0){//until queue is not empty, process the adjacent
  // stations of the first element of the queue and enqueue them only if they
  // have the same journeycode as the first element
    if(stnind->object==desind){//If first element is the destination, add that journeycode to the resultant list of journeycodes
      if(resjc==nullptr){
        resjc= new listOfObjects<int>(jind->object);
      }
      else{
        listOfObjects<int> * temp5=resjc;
        resjc=resjc->next;
        resjc= new listOfObjects<int>(jind->object);
        resjc->prev=temp5;
        temp5->next=resjc;
      }
      rc++; //Increment count of resjc
    }
    else{//Process the adjacent stations
      listOfObjects<StationConnectionInfo *> *itr1= adjacency[stnind->object].toStations;//Iterate over adjacent stations
      if(itr1!=nullptr) {
        while(true){//Iterate over all trains of adjacent stations
          listOfObjects<TrainInfoPerStation *> *trainitr1=itr1->object->trains;
          if(trainitr1!=nullptr){
            while(true){
              if(trainitr1->object->journeyCode==jind->object){//If journeycode matches that of the parent station, enqueue it
                listOfObjects<int> *temp3=currs;
                currs=currs->next;
                currs= new listOfObjects<int>(itr1->object->adjacentStnIndex);
                currs->prev=temp3;
                temp3->next=currs;
                listOfObjects<int> *temp4=currj;
                currj=currj->next;
                currj= new listOfObjects<int>(trainitr1->object->journeyCode);
                currj->prev=temp4;
                temp4->next=currj;
                arrsize++;//Increment BFS queue size
              }
              if(trainitr1->next==nullptr){break;} //If trainlist exhausted then break
              else trainitr1=trainitr1->next; //Else move on to process the next train of the same station
            }
          }
          if(itr1->next==nullptr){break;}//If toStations list exhausted then break
          else itr1=itr1->next; //Else move on to process the next adjacent station
        }
      }
    }
    jind=jind->next; //Move on to the next element of the queue
    stnind=stnind->next; //Similar to dequeue
    arrsize--; //Decrement queue size
  }
  
  if(rc==0){cout<<"No direct journeys available"<<endl; return;} //If resjc empty, no direct journey exists
  
  //Since we have a list of journeycodes, find corresponding journeys from source station
  //and add it to the final list to be printed
  listOfObjects<TrainInfoPerStation *> *iter= stationInfo[srcind];
  while(resjc->prev!=nullptr){
    resjc=resjc->prev; //Go to the start of resjc to perform further operations
  }
  while(true){//Iterate over all journeys from source station
    while(true){//Iterate over journeycodes of resjc to find a matching trainInfoPerStation
      if(resjc->object==iter->object->journeyCode){//if match found
        if(res==nullptr){// Add journey to the final output list
          res= new listOfObjects<TrainInfoPerStation *>(iter->object);
        }
        else{
          listOfObjects<TrainInfoPerStation *>* temp=res;
          res=res->next;
          res= new listOfObjects<TrainInfoPerStation *>(iter->object);
          res->prev=temp;
          temp->next=res;
        }
        while(resjc->prev!=nullptr){//Go to the start of resjc for the next loop
          resjc=resjc->prev;
        }
        break; //Since found and unique, break
      }
      if(resjc->next==nullptr){//If complete resjc exhausted
        while(resjc->prev!=nullptr){//Go to start of resjc for next loop
          resjc=resjc->prev;
        }
        break; //Break
      }
      else resjc=resjc->next; //else iterate over elements of resjc
    }
    if(iter->next==nullptr){break;}//If journeys from source station list exhausted then break
    else iter=iter->next; //else iterate over journeys from source station list
  }
  while(res->prev!=nullptr){
    res=res->prev; //go to the start of output list to call print on it
  }
  printStationInfo(res);//print journeys

  // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
  // for the source station and then we can print it out by invoking
  // printStationInfo that we had used in Lab 7.
  // printStationInfo is a private member function of the Planner class
  // It is declared in planner.h and implemented in planner.cpp
  
  return;
}

#endif
