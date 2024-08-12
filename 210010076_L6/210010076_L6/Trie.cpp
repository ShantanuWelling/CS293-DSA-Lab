#ifndef TRIE_CPP
#define TRIE_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef TRIE_H
#include "Trie.h"
#endif

using namespace std;

Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

Trie::~Trie() {
  recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node) {
  if (node == nullptr) {
    return;
  }
  else {
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      recursiveDelete(currNode);
      node->branch[i] = nullptr;
    }
    if (node != root) {
      delete node;
    }
    return;
  }
}

bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  // Insert your code here
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      //If letter of branch from currNode is empty then create new Trienode
      currNode->branch[letter]=new TrieNode();
      currNode->numNonNullBranches++; //Increment number of non-null branches
    }
    if(i==(len-1)){
      currNode->branch[letter]->isWord=true; //Update isWord of last letter
      if(currNode->branch[letter]->indices==nullptr) {
        //If indices is empty, update indices
        currNode->branch[letter]->indices= new listOfObjects<int>(indexOfName);
      }
      else{
        listOfObjects<int> *L=currNode->branch[letter]->indices;
        //If indices non-empty, go through linked list and find empty element
        while(L->next!=nullptr){
          L=L->next;
        }
        L->next=new listOfObjects<int>(indexOfName); //Update list
      }
    }
    currNode = currNode->branch[letter];
  }

  return true;
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  // Insert your code here
  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      return false;
    }
    if(currNode->numNonNullBranches>1) {//Check for last Branched node
      lastBranchChar=letter;
      lastBranchNode=currNode;
    }
    currNode = currNode->branch[letter];
  }
  if(!currNode->isWord) return false;
  else{
    listOfObjects<int> *currIndices = currNode->indices;//Pointer to current element
    listOfObjects<int> *y=currIndices;//Pointer to previous element
    if(currIndices==nullptr) return false;
    else if(currIndices->next==nullptr && name==nameDict->getKeyAtIndex(currIndices->object)){
      //Case where trie is to be deleted
      if(lastBranchNode==nullptr){//If root has only 1 branch
        int letter1=toupper(wordInName.at(0)) - 'A';
        recursiveDelete(root->branch[letter1]); //Recursively delete that branch of root
        root->branch[letter1]=nullptr;
        root->numNonNullBranches-=1; //Decrement number of non null branches of root
      }
      else{
        recursiveDelete(lastBranchNode->branch[lastBranchChar]); //Recursively deleted trie from last branched node found
        lastBranchNode->branch[lastBranchChar]=nullptr; 
        lastBranchNode->numNonNullBranches-=1; //Decrement number of non null branches of lastbranch node
      }
      return true;
    }
    else if(currIndices->next==nullptr && name!=nameDict->getKeyAtIndex(currIndices->object)) return false;
    while (currIndices != nullptr) {//Check through all indices
      if(name==nameDict->getKeyAtIndex(currIndices->object)){//Found name
        if(currNode->indices==currIndices) currNode->indices=currIndices->next;
        //If found at first element, update indices of currNode
        else{
          if(currIndices->next==nullptr) y->next=nullptr;//if found at last element
          else y->next=currIndices->next; //found at some middle element
        }
        return true;
      }
      y=currIndices;
      currIndices=currIndices->next;
    }
  }
  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  listOfObjects<string> *currCompletions = new listOfObjects<string>("hznxczjknc");

  // Insert your code here
  for (int i = 0; i < len; i++) {
    int letter = toupper(prefix.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      return nullptr;
    }
    currNode = currNode->branch[letter];
  }//Match the prefix
  recursiveAddCompletions(currNode,currCompletions);
  //Perform Recursive Add completions on the Node till which prefix was matched
  if(currCompletions->object=="hznxczjknc") return nullptr;
  return currCompletions;
  
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
	return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {

  // Insert your code here
  listOfObjects<int> *currIndices = node->indices;
  listOfObjects<string> *last=currCompletions;//pointer to last element of list
  if(currIndices!=nullptr){//Find last element of currCompletions
      while (last->next != nullptr) {
        last=last->next;
      } 
  }
     
  while (currIndices != nullptr) {//Check through all indices
    string inp= nameDict->getKeyAtIndex(currIndices->object); //Get string name
    if(!isPresentInCompletions(currCompletions,inp)){//If not present in completions
      if(currCompletions->object=="hznxczjknc"){//If currCompletions empty
        currCompletions->object= inp;
        last=currCompletions;
      }
      else{//Add after last element
      last->next=new listOfObjects<string>(inp);
      last=last->next;//Update pointer to last element
      }
    }
    currIndices=currIndices->next;
  }
  return true;
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name) {
  listOfObjects<string> *currCompletion = completions;
  bool isPresent = false;
  while (currCompletion != nullptr) {
    if (currCompletion->object == name) {
      isPresent = true;
      break;
    }
    currCompletion = currCompletion->next;
  }
  return isPresent;
}

void Trie::freeCompletionList(listOfObjects<string> *completions) {
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr) {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}

bool Trie::isPresent(string wordInName) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      return false;
    }
    currNode = currNode->branch[letter];
  }

  return currNode->isWord;
  
}

// Edit version 1: Added printTrie and recursivePrintTrie functions
// to help in debugging

void Trie::printTrie()
{
  recursivePrintTrie(root, "", -1, false);
}

// Adapted from Adrian Schneider's code on StackOverflow
// Basically a variation of the function we've been using
// print binary search trees in previous labs

void Trie::recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight)
{
  if (node != nullptr) {
    cout << prefix;
    
    cout << ((branchId == 0) ? "|-" : (branchId == -1)? " *":"|_" ) << (char) ((branchId != -1) ? 'A'+branchId: '*');
    cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*':'_');
    
    // If this trie node has isWord set to true, print "(isWord)" and
    // also the list of complete station names (accessed through indices
    // in nameDict) associated with this trie node.
    if (node->isWord) {
      cout << "(isWord)";
      listOfObjects<int> *currIndices = node->indices;
      while (currIndices != nullptr) {
	cout << endl << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
	currIndices = currIndices->next;
      }
    }
    else {
      cout << "()";
    }
    cout << endl;
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      bool childrenToRight = false;
      for (int j = i+1; j < NUM_CHARS; j++) {
	if (node->branch[j] != nullptr) {
	  childrenToRight = true;
	  break;
	}
      }
      if (currNode != nullptr) {
	recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
      }
    }
  }
}
// End edit version 1

#endif
