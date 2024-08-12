#ifndef PLANNER_H
#define PLANNER_H
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include <tuple>
#include<cmath>
using namespace std;

int hashValue(string key,int N){
    const double x=33; //hash map code
    double n=key.length(); //size of key string
    const double A1=(sqrt(5)-1)/2;
    double sum=0; //hash value to be computed
    for(int i=(n-1);i>=0;i--){
        sum=(sum*x+A1*key[i]);
        sum=(sum-floor(sum));
    }
    return floor(sum*N);
  };

struct Journey {
  // define suitable fields here
  tuple <string,float,string,float> route;
  int value=-1;
  Journey(string srcstat, float strtime, string deststat, float endtime){
    get<0>(route)=srcstat;
    get<1>(route)=strtime;
    get<2>(route)=deststat;
    get<3>(route)=endtime;
  }
  Journey(){};
};

class Dictionary {
 public:
  int N; // size of array A
  Journey *A; // Array of dictionary entries


  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(string key){
    int keyhv=hashValue(key,this->N); //first find hashvalue of given key
    for(int i=keyhv;i<N;i++){
        if(A[i].value==-1) return i; //start iterating from the given hashvalue till null (-1) is encountered
    }                                                    
    return -1;
  };

  // Default constructor
  Dictionary(){
    this->N=1000;
    A= new Journey[N];
  };


  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(Journey B){
    if(findFreeIndex(get<0>(B.route))==-1) return false; //if no free index return false
    else {
        int free_index=findFreeIndex(get<0>(B.route));
        A[free_index]=B;                    //else put key at free index and return true
        return true;
        }
  };
};

#endif
