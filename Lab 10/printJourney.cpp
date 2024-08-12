#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

//Function to convert day to corresponding string for printing
string dayconv(int a){
  if(a==0){
    return "Sun";
  }
  else if(a==1){
    return "Mon";
  }
  else if(a==2){
    return "Tue";
  }
  else if(a==3){
    return "Wed";
  }
  else if(a==4){
    return "Thu";
  }
  else if(a==5){
    return "Fri";
  }
  else if(a==6){
    return "Sat";
  }
  return "";
}

//Node class of stations to be printed
class node{
public:
  string first; //Station name
  int day1;     //Departure day from that station
  int day2;     //Arrival day to that station
  int dep1;     //Departure time
  int arr1;     //Arrival time
  int jourc;    //Corresponding journeycode
  node(string a, int c, int d1, int d2, int de1, int a2){//Default constructor
    first=a;
    jourc=c;
    day1=d1;
    day2=d2;
    dep1=de1;
    arr1=a2;
  }
  node(){;}//Empty constructor
};
//Queuenode class for BFS queue
class queuenode{
public:
  int curday; //Current day of that object
  int startday; //Startday of the journey
  int currstnind; //Station index of current station
  int currjc;     //Current journeycode
  TrainInfoPerStation* stninfo; //Traininfo of that station
  StationConnectionInfo* prevstn=nullptr, *currstn=nullptr; 
  //Connection info of previous and current stations similar to parent relationship in BFS tree
  listOfObjects<node> *stoplist=nullptr;//List of stop stations
  int numstops; //Number of stops taken
  listOfObjects<int> *transtime=nullptr; //List of transit times between stops
  //Default constructor
  queuenode(TrainInfoPerStation* stn, StationConnectionInfo* pre, StationConnectionInfo* cur, int cd, int jc){
    stninfo=stn;
    prevstn=pre;
    currstn=cur;
    curday=cd;
    currstnind=cur->adjacentStnIndex;
    currjc=jc;
  }
  queuenode(){;}//Empty constructor
};


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{ maxTransitTime*=100; //Assuming maxTransitTime was in hours (and integer), convert it to HHMM format
  int srcind = stnNameToIndex.get(srcStnName)->value; //Get station index of source station
  int desind = stnNameToIndex.get(destStnName)->value; //Get station index of destination station
  int arrsize=0; //Size of bfs queue
  listOfObjects<queuenode> *bfs=nullptr; //BFS queue
  StationConnectionInfo* src; //Source station connectioninfo list
  listOfObjects<StationConnectionInfo *> *itr= adjacency[srcind].toStations; //Iterator over toStations of source
  int countr=0; //Maintains count of possible valid journeys
  if(itr==nullptr) {cout<<"NO POSSIBLE JOURNEYS"<<endl; return;}//If no stations, return
  listOfObjects<StationConnectionInfo *> *finder = adjacency[itr->object->adjacentStnIndex].fromStations;
  //Finder finds the connectionInfo of source station
  while(true){
    if(finder->object->adjacentStnIndex==srcind){
      src=finder->object;
      break;
    }
    if(finder->next==nullptr) break;
    else finder=finder->next;
  }
  while(true){//Iterate over adjacent stations from source station (level 1)
    listOfObjects<TrainInfoPerStation *> *trainitr=itr->object->trains; //Iterate over trains of adjacent stations
    while(true){
      TrainInfoPerStation *obj=nullptr;//Traininfo obj of source station corresponding to journey code of train iterator
      listOfObjects<TrainInfoPerStation*> *srcitr= stationInfo[srcind];//Iterator to find obj
      while(true){//Find obj
        if(srcitr->object->journeyCode==trainitr->object->journeyCode){
          obj=srcitr->object;
        }
        if(srcitr->next==nullptr) break;
        else srcitr=srcitr->next;
      }
      for(int i=0; i<7; i++){//Iterate over all days of trainitr
        if(trainitr->object->daysOfWeek[i]){//If there is train
          queuenode *b= new queuenode(trainitr->object,src,itr->object,i, obj->journeyCode);
          //Insert corresponding queuenode into BFS queue
          b->startday=i;//Set startday of journey
          b->numstops=maxStopOvers; //Set maximum stop limit
          node a(srcStnName,trainitr->object->journeyCode,b->startday,-1,obj->depTime,-1);
          //Insert into stoplist, the first stop i.e. source station (but not included in numstops as
          // it is only for printing purposes)
          b->stoplist=new listOfObjects<node>(a);
          if(bfs==nullptr){//If bfs queue is empty, add queuenode to it
            bfs=new listOfObjects<queuenode>(*b);
          }
          else{//else append to the list
            listOfObjects<queuenode>* temp= bfs;
            bfs=bfs->next;
            bfs= new listOfObjects<queuenode>(*b);
            bfs->prev=temp;
            temp->next=bfs;
          }
          arrsize++;//Increment size of bfs queue
        }
      }
      if(trainitr->next==nullptr){break;} //If trainlist exhausted then break
      else trainitr=trainitr->next; //Else move on to process the next train of the same station
    }
    if(itr->next==nullptr){break;} //If toStations list exhausted then break
    else itr=itr->next; //Else move on to process the next adjacent station
  }
  //Complete processing first level of BFS queue
  listOfObjects<queuenode> *lastbfs=bfs;//Pointer to last node of BFS queue
  while(bfs->prev!=nullptr){//Go to start of BFS queue for dequeue & processing operations
    bfs=bfs->prev;
  }
  while(arrsize>0){//while BFS queue isn't empty
    if(bfs->object.currstnind==desind){//If object to be dequeued is destination station
      listOfObjects<node> *k= bfs->object.stoplist; //Add last stop to stoplist
      while(k->next!=nullptr){
        k=k->next;
      }
      listOfObjects<node> *temp= k;
      k=k->next;
      string prevstn =temp->object.first; //Previous stop
      int prevjc= temp->object.jourc; //Journey code of previous stop
      listOfObjects<TrainInfoPerStation*> *looper= stationInfo[stnNameToIndex.get(prevstn)->value];
      //Get arrival time at previous stop
      int arrtim=-2;
      int currentd; //Current day
      while(true){//Find arrival time of previous stop
        if(looper->object->journeyCode==prevjc){arrtim=looper->object->arrTime;}
        if(looper->next==nullptr) break;
        else looper=looper->next;
      }
      //Create node and add to stoplist
      node *a= new node(destStnName,bfs->object.currjc,-1,temp->object.day2,0,arrtim);
      k=new listOfObjects<node>(*a);
      k->prev=temp;
      temp->next=k;
      while(k->prev!=nullptr){//Go to start of k
        k=k->prev;
      }
      listOfObjects<int> *tt=bfs->object.transtime; //tt is list of transit time to be printed
      listOfObjects<node> *t2=k;
      cout<<endl<<endl<<"Possible Journey"<<endl;
      countr++; //Since possible journey found, increment counter
      if(k->next->next==nullptr){//If direct journey
        string da1=dayconv(k->object.day1); //convert day to string and print
        string da2=dayconv(k->next->object.day2); 
        cout<<"From: "<<k->object.first<<" To: "<<k->next->object.first<<endl;
        cout<<"Journey code: "<<k->object.jourc<<endl;
        cout<<"Day & Time of Departure from "<<k->object.first<<" : "<<da1<<" "<<k->object.dep1<<endl;
      }
      else{//Print stoplist in loop
      while(k->next!=nullptr){
        string da1=dayconv(k->object.day1);
        string da2=dayconv(k->next->object.day2);
        cout<<"From: "<<k->object.first<<" To: "<<k->next->object.first<<endl;
        cout<<"Journey code: "<<k->object.jourc<<endl;
        if(t2==k){
        }
        else{
        if(k->next->object.arr1==-1) cout<<"Day & Time of Arrival to "<<k->object.first<<" : "<<da2<<" Starts"<<endl;
        else cout<<"Day & Time of Arrival to "<<k->object.first<<" : "<<da2<<" "<<k->next->object.arr1<<endl;
        }
        cout<<"Day & Time of Departure from "<<k->object.first<<" : "<<da1<<" "<<k->object.dep1<<endl;
        if(tt!=nullptr){cout<<"Transit time: "<<tt->object<<endl;tt=tt->next;}//Print transit time
        k=k->next;
      }
      cout<<endl<<endl;
      }
    }
    else{//If not destination station, iterate over adjacent stations of first queuenode
      listOfObjects<StationConnectionInfo *> *itr1= adjacency[bfs->object.currstnind].toStations;
      if(itr1!=nullptr){
        while(true){//Iterate over all trains
          listOfObjects<TrainInfoPerStation *> *trainitr1=itr1->object->trains;
          if(trainitr1!=nullptr){
            while(true){
              if(trainitr1->object->journeyCode==bfs->object.currjc){//If along same journeycode
                //insert into bfs
                int cd;//Current day
                //If arrival time and adjacent station is more than departure time, current day
                // is same and the day of the BFS object
                if(trainitr1->object->arrTime>bfs->object.stninfo->depTime){
                  cd=bfs->object.curday;
                }
                else {cd=(bfs->object.curday+1)%7;} //Else it is next day
                listOfObjects<TrainInfoPerStation *> *passer; //Traininfoperstation argument to be passed into new node to be inserted into BFS queue
                //Iterator over from Stations of adjacent station to get traininfo of predecessor station
                listOfObjects<StationConnectionInfo*> *itrfromstat= adjacency[itr1->object->adjacentStnIndex].fromStations;
                while(true){
                  if(itrfromstat->object->adjacentStnIndex==bfs->object.currstnind){//If it is BFS object's stationindex
                    //Iterate over trains of that station
                    listOfObjects<TrainInfoPerStation*> *traincheckr=itrfromstat->object->trains;
                    while(true){
                      if(traincheckr->object->journeyCode==bfs->object.currjc){//If journey code matches
                        passer= new listOfObjects<TrainInfoPerStation*>(traincheckr->object);//Set passer
                      }
                      if(traincheckr->next==nullptr){
                        break;
                      }
                      else traincheckr=traincheckr->next;
                    }
                  }

                  if(itrfromstat->next==nullptr){
                    break;
                  }
                  else itrfromstat=itrfromstat->next;
                }
                //Initialize new queuenode to be inserted into BFS queue
                queuenode *b=new queuenode(passer->object,bfs->object.currstn,itr1->object,cd, trainitr1->object->journeyCode);
                b->startday=bfs->object.startday; //Set startday
                listOfObjects<node> *cop=bfs->object.stoplist; 
                //Copy of bfs object's stoplist into the stoplist of the new node to be added into the queue
                //Since along the same journeycode,no new stop is being added to the stoplist
                listOfObjects<node> *sl; //Stoplist
                bool ghj=true; //Bool checker for first addition to sl
                while(true){
                  if(ghj){//if sl is empty
                    b->stoplist=new listOfObjects<node>(cop->object);//Add to stoplist
                    sl=b->stoplist;//Set pointer of sl to b's stoplist
                    ghj=false; //Flip bool
                  }
                  else{//Append to stop list
                    listOfObjects<node>*temp9=sl;
                    sl=sl->next;
                    sl=new listOfObjects<node>(cop->object);
                    sl->prev=temp9;
                    temp9->next=sl;
                  }
                  if(cop->next==nullptr) break;
                  else cop=cop->next;
                }
                b->numstops=bfs->object.numstops; //Copy numstops since they remain same
                listOfObjects<int> *copy2=bfs->object.transtime; //Copy transittime list of BFS queue object to the new vertex to be inserted
                listOfObjects<int> *bt; //b transittime list
                bool abc=true; //Bool checker for first addition to bt
                if(copy2==nullptr){//if BFS object transittime list is empty
                  b->transtime=nullptr;
                }
                else{
                while(true){
                  if(abc){//If bt is empty
                    b->transtime=new listOfObjects<int>(copy2->object); //Add to transittime list
                    bt=b->transtime; //Set pointer of bt to transittime of b
                    abc=false; //Flip bool
                  }
                  else{//Append to transit time list
                    listOfObjects<int>*temp5=bt;
                    bt=bt->next;
                    bt=new listOfObjects<int>(copy2->object);
                    bt->prev=temp5;
                    temp5->next=bt;
                  }
                  if(copy2->next==nullptr) {break;}
                  else copy2=copy2->next;
                }}//Finally add to the BFS queue
                listOfObjects<queuenode> *temp=lastbfs; 
                lastbfs=lastbfs->next; //Update pointer to last element of BFS queue
                lastbfs=new listOfObjects<queuenode>(*b);
                lastbfs->prev=temp;
                temp->next=lastbfs;
                arrsize++; //Increment BFS queue size
              }
              else if(bfs->object.numstops>0){//If journey code not same and stops still left 
                listOfObjects<TrainInfoPerStation*> *check=stationInfo[bfs->object.currstnind]; //Iterate over trains of BFS object
                TrainInfoPerStation *obj; //Traininfo of train from BFS object to adjacent station with new journey code
                while (true){ //Find obj
                  if(check->object->journeyCode==trainitr1->object->journeyCode) obj=check->object;
                  if (check->next==nullptr) break;
                  else check=check->next;
                }
                for(int i=0;i<7;i++){//Check all days
                  if(obj->daysOfWeek[i] && trainitr1->object->depTime>=0){
                    int time=-1; //Transit time
                    int newjc=bfs->object.stninfo->journeyCode; //New journeycode
                    listOfObjects<TrainInfoPerStation*> *looper= stationInfo[bfs->object.currstnind]; //Loop over trains of BFS station
                    int arrT=-2; //Arrival time into stop station
                    while(true){ //Find arrival time into stop station from looper
                      if(looper->object->journeyCode==newjc){arrT=looper->object->arrTime;}
                      if(looper->next==nullptr) break;
                      else looper=looper->next;
                    }
                    if(i>bfs->object.curday){// if day > BFS object current day
                      time=(i-bfs->object.curday-1)*2400+obj->depTime; 
                      time+=2400-100+60-arrT; //Compute transit time
                      if(time%100>=60){
                        time+=100-60; //Convert time to HHMM
                      }
                    }
                    else if(i<bfs->object.curday){ //if day < BFS object current day
                      time=i*2400+obj->depTime+(6-bfs->object.curday)*2400;
                      time+=2400-100+60-arrT; //Compute transit time
                      if(time%100>=60){
                        time+=100-60; //Convert time to HHMM
                      }
                    }
                    else{ //If both on same day
                      if(obj->depTime>=arrT) {//If departs from stop station later and arrives into stop station earlier
                        if(obj->depTime%100<arrT%100){
                          time=obj->depTime-100+60-arrT; //Compute transit time
                        }
                        else{
                        time=obj->depTime-arrT;
                        }
                        if(time%100>=60){
                        time+=100-60; //Convert time to HHMM
                        }
                      }
                    }
                    if(time>=0 && time<=maxTransitTime){//If time was found (>0) and less than maxTransitTime
                      int newcd; //New current day of object to be enqueues
                      if(trainitr1->object->arrTime>obj->depTime) newcd=i; //Set new current day
                      else newcd=(i+1)%7;
                      //Initialize new queuenode to be added to BFS queue
                      queuenode *c= new queuenode(trainitr1->object,bfs->object.currstn,itr1->object,newcd,trainitr1->object->journeyCode); //flag i>newcd
                      c->startday=bfs->object.startday; //Set all members of queuenode
                      c->numstops=bfs->object.numstops-1; //Decrement number of possible stops available
                      if(bfs->object.transtime==nullptr){//Transit time list is empty (first stop)
                        c->transtime=new listOfObjects<int>(time);
                      }
                      else{//Copy transit time list of BFS object into queuenode to be inserted into BFS queue similar to above
                        listOfObjects<int> *copy1=bfs->object.transtime;
                        listOfObjects<int> *btt;
                        bool abc=true;
                        while(true){
                          if(abc){
                            c->transtime=new listOfObjects<int>(copy1->object);
                            btt=c->transtime;
                            abc=false;
                          }
                          else{
                            listOfObjects<int>*temp5=btt;
                            btt=btt->next;
                            btt=new listOfObjects<int>(copy1->object);
                            btt->prev=temp5;
                            temp5->next=btt;
                          }
                          if(copy1->next==nullptr) break;
                          else copy1=copy1->next;
                        }
                        listOfObjects<int>*temp6=btt; //Add a new transittime object to the transittime list
                        btt=btt->next;
                        btt=new listOfObjects<int>(time);
                        btt->prev=temp6;
                        temp6->next=btt;
                      }//Copy stoplist of BFS object to the new queuenode to be inserted into BFS queue similar to above
                      listOfObjects<node> *cop=bfs->object.stoplist;
                      listOfObjects<node> *sl;
                      bool ghj=true;
                      while(true){
                        if(ghj){
                          c->stoplist=new listOfObjects<node>(cop->object);
                          sl=c->stoplist;
                          ghj=false;
                        }
                        else{
                          listOfObjects<node>*temp9=sl;
                          sl=sl->next;
                          sl=new listOfObjects<node>(cop->object);
                          sl->prev=temp9;
                          temp9->next=sl;
                        }
                        if(cop->next==nullptr) break;
                        else cop=cop->next;
                      }
                      listOfObjects<node>*temp4=sl;
                      sl=sl->next; //Add a new stop (current BFS object) to the stoplist 
                      node *app= new node(stnNameToIndex.getKeyAtIndex(bfs->object.currstnind),trainitr1->object->journeyCode,i,bfs->object.curday,obj->depTime, bfs->object.stninfo->arrTime);
                      sl= new listOfObjects<node>(*app);
                      sl->prev=temp4;
                      temp4->next=sl;
                      listOfObjects<queuenode> *tem=lastbfs; //Finally add to BFS queue
                      lastbfs=lastbfs->next; //Update pointer to last element of BFS queue
                      lastbfs=new listOfObjects<queuenode>(*c);
                      lastbfs->prev=tem;
                      tem->next=lastbfs;
                      arrsize++; //Increment BFS queue size
                    }
                  }
                }
              }
              if(trainitr1->next==nullptr){break;} //If trainlist exhausted then break
              else trainitr1=trainitr1->next;
            }
        }
        if(itr1->next==nullptr){break;}//If toStations list exhausted then break
        else itr1=itr1->next;
      }
    }
  }
  arrsize--; //Dequeue BFS
  bfs=bfs->next; 
  }
if(countr==0){//If no possible journeys
  cout<<"NO POSSIBLE JOURNEYS WITH GIVEN CONSTRAINTS"<<endl;
}
return;
}