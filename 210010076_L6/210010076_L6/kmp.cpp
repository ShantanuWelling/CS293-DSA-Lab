#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len = 0;
  int patlen= pattern.length();
  int lps[patlen]; //Hmatrix
  lps[0]=0; //First index is always 0
  int i = 1;
  while (i < patlen) {
    if (pattern[i] == pattern[len]) {//pattern[i] matches pattern[len]
      len++; //Increment len
      lps[i] = len; //Update lps[i]
      i++; //Increment i
    }
    else { // (pat[i] != pat[len])
      if (len != 0) { //If len is not 0, make len lps[len-1]
        len = lps[len - 1];
      }
      else {lps[i]=0;i++;} //Else make lps[i]=0 and increment i
    }
  }
  return lps;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int M = pattern.length();
  int N = text.length();
  int i = 0; // index for txt[]
  int j = 0; // index for pat[]
  while ((N - i) >= (M - j)) {
    if (pattern[j] == text[i]) {//If matched
      j++; 
      i++;
    }
    if (j == M) {//Complete match then return starting index of pattern in text
      return (i-j);
    }
    else if (i < N && pattern[j] != text[i]){ // mismatch after j matches
      // Do not match hmatrix[0..hmatrix[j-1]] characters,
      // they will match anyway
      if (j != 0) j = hMatrix[j - 1];
      else i = i + 1;
    }
  }
  return -1;
}

#endif
