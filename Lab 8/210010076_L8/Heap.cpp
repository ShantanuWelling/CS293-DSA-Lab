#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template<typename T>
void Heap<T>::insert(T obj) {
  // insert your code here
  if(root==nullptr){//If heap is empty, initialize root and tail
    root= new TreeNode<T>(obj);
    tail= root;
  }
  else if(tail->left==nullptr){//If left of tail is empty, insert there
    tail->left= new TreeNode<T>(obj);
    tail->left->parent=tail; //Update parent of the inserted node
    maxHeapify(tail->left); //Invoke insert Heapify on the inserted node
  }
  else{//Insert at right of tail
    tail->right=new TreeNode<T>(obj);
    tail->right->parent=tail; //Update parent of the inserted node
    maxHeapify(tail->right); //Invoke insert Heapify on the inserted node
    TreeNode<T> * prevtail=tail;
    setTail(tail); //Reset tail
    tail->prevT=prevtail; //Update previous tail of new tail
  }
  size++; //Increment size of heap
  return;
}

//Updates tail of the heap
template<typename T>
void Heap<T>::setTail(TreeNode<T>* node){
  //If we reach this stage that means a level is completely filled 
  //and we need to proceed to the next level by going to the extreme left.
  if(node->parent==nullptr){
    tail=node;
    while(tail->left!=nullptr){
      tail=tail->left;
    }
  }//If current node is the left node, go to the right node and 
  //proceed left from there to reach the left most node.
  else if(node->parent->left==node){
    tail=node->parent->right;
    while(tail->left!=nullptr){
      tail=tail->left;
    }
  }//Check if right child and then perform recursion
  else if(node->parent->right==node){
    setTail(node->parent); //Recursively call set tail on the parent node 
  }
  return;
}
//heapify for insertion
template<typename T>
void Heap<T>::maxHeapify(TreeNode<T>* node){
  if(node->parent!=nullptr){
    if(node->parent->object<node->object){//COMPARISON
    //If parent node is less than current node, swap them
      swap(node->parent->object,node->object);
      maxHeapify(node->parent);
      //Perform maxHeapify recursively on parent node and keep on swapping
      //it with current node if it is less till root is reached or greater than
      //condition is encountered
    }
  }
  return;
}

template<typename T>
T Heap<T>::delMax() {
  T res;
  // insert your code here
  if(root==nullptr){ return res;}
  if(size==1){//If only one element in heap
    res=root->object; //Return root
    tail=nullptr; //Reset parameters
    root=nullptr;
    size--;
    return res;
  }
  else{
    res=root->object;//Store root's object for returning
    if(tail->right!=nullptr){//If last element of heap is right child of tail
      swap(tail->right->object,root->object); //swap it with root
      tail->right=nullptr; //delete right of tail
      ogmaxheapify(root); //Heapify root
    }
    else if(tail->left!=nullptr){//If last element of heap is left child of tail
      swap(tail->left->object,root->object); //swap it with root
      tail->left=nullptr; //delete left of tail
      ogmaxheapify(root); //Heapify root
    }
    else{//If completely filled binary heap
      tail=tail->prevT; //set tail to its previous tail
      return delMax(); //Delete rightmost (last) node by swapping it with root
    }

  }
  size--; //decrement size of heap
  return res; //return root's object
}

//Usual Heapify function
template<typename T>
void Heap<T>::ogmaxheapify(TreeNode<T> * node){
  if(node==nullptr||node->left==nullptr){return;}//If node is null or leaf, do nothing
  TreeNode<T> * maxnode=node->left; //Iterator node initialized to left child of node
  if(node->right!=nullptr && maxnode->object<node->right->object){//COMPARISON
    maxnode=node->right; //If right child is larger than left child, set iterator to right child
  }
  //If iterator is larger than current node:
  if(node->object<maxnode->object){//COMPARISON 
    swap(node->object,maxnode->object);//swap the iterator and current nodes
    ogmaxheapify(maxnode); //Recursively call heapify on swapped node
  }
  return;
}

template<typename T>
void Heap<T>::printHeap(TreeNode<T> *node) {
  // insert your code here
  static string a=" ";
  printBT(a, node, false);
  return;
}

template<typename T>
void Heap<T>::printBT(std::string prefix, const TreeNode<T>* node, bool isLeft) {
  if( node != nullptr ){
    cout << prefix;
    cout << (isLeft ? "├──" : "└──" );
    // print the value of the node
    cout<< node->object << std::endl;
    // enter the next tree level - left and right branch
    printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
    printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
  }
}

  
