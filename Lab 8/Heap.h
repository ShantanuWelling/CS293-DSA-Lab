#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T> class TreeNode {
 public:
  T object;
  TreeNode<T> *left;
  TreeNode<T> *right;
  TreeNode<T> *parent;
  TreeNode<T>* prevT;

  TreeNode(T initObj) {
    object = initObj;
    left = right = parent = nullptr;
    prevT=nullptr;
  }
  ~TreeNode() {;}
};

template <typename T> class Heap {
  TreeNode<T>* root;
  TreeNode<T>* tail;
  int size;

 public:
  Heap() {root = nullptr; tail=nullptr;size=0;}
  ~Heap() {;}

  void insert(T obj);
  T delMax();
  T getMax() {return root->object;}
  void printHeap(TreeNode<T> *node);
  void setTail(TreeNode<T> * node);
  void maxHeapify(TreeNode<T> * node);
  void ogmaxheapify(TreeNode<T> * node);
  void displayAboveThresh(int thresh);
  void printBT(string prefix, const TreeNode<T>* node, bool isLeft);
};
#endif

