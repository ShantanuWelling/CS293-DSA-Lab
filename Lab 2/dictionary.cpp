#include<iostream>
#include<string.h>
#include<array>
#include<cmath>

#ifndef DICTIONARY_H
#define DICTIONARY_H


// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry {
  // define suitable fields here
  char key[32];
  int value;
  Entry(char input[]){ //constructor using given input
    int inp_len=strlen(input);
    for(int i=0;i<inp_len;i++){
        key[i]=input[i];
    }
  }
  Entry(){ //default constructor setting first value to null
    key[0]='\0';
  };
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(char key[]){
    const double x=33; //hash map code
    double n=strlen(key); //size of key string
    const double A1=(sqrt(5)-1)/2;
    double sum=0; //hash value to be computed
    for(int i=(n-1);i>=0;i--){
        sum=(sum*x+A1*key[i]);
        sum=(sum-floor(sum));
    }
    return floor(sum*N);
  }
  ;

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(char key[]){
    int keyhv=hashValue(key); //first find hashvalue of given key
    for(int i=keyhv;i<N;i++){
        if(A[i].key[0]=='\0'||A[i].key[0]=='$') return i; //start iterating from the given hashvalue
    }                                                     //till a null or tombstone is encountered
    return -1;
  };

  // Default constructor
  Dictionary(){
    this->N=64;
    A= new Entry[N];
  };

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(char key[]){
    int keyhv=hashValue(key);
    for(int i=keyhv;i<N;i++){
        for(int j=0;j<32;j++){
            if(A[i].key[j]==key[j]&&key[j]=='\0') { //if both strings are equal and terminate at same index
                Entry *res= &A[i];
                return res;
            }
            else if(A[i].key[0]=='\0') return NULL; //if dictionary key is empty
            else if (A[i].key[j]==key[j]) continue; //if both char are equal then continue
            else if(A[i].key[0]=='$') continue; //if dictionary key is tombstone continue
            else if(A[i].key[j]!=key[j]) break; //if chars unequal then break
        }

    }
    return NULL;
  };

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e){
    if(findFreeIndex(e.key)==-1) return false; //if no free index return false
    else {
        int free_index=findFreeIndex(e.key);
        A[free_index]=e;                    //else put key at free index and return true
        return true;
        }
  };

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(char key[]){
    if(get(key)==NULL) return false; 
    else {
        Entry *rem=get(key);
        (*rem).key[0]='$'; //remove key and put tombstone
        return true;
        }
  };
};

#endif
