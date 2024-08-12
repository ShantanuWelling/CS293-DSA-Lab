#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#endif

//Function to recursively update height
void BST::htupdt(TreeNode *node1){
  if(node1->left==nullptr && node1->right==nullptr) node1->height=0; //If both childs null
  else if (node1->left==nullptr && node1->right!=nullptr) node1->height=node1->right->height+1; //If only right child
  else if (node1->left!=nullptr && node1->right==nullptr) node1->height=node1->left->height+1; //If only left child
  else node1->height=max(node1->left->height,node1->right->height)+1; //If 2 children
  if(node1->parent!=nullptr) htupdt(node1->parent); //If parent not null recursively update parent's height
  return;
}

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
  // Implement insertion in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke BSTLessThan on the current node in the tree that you
  // are inspecting and the new node to do your comparison.

  // REMEMBER to update the heights of appropriate nodes in the tree
  // after an insertion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  TreeNode *newnode=new TreeNode(jrnyCode,price);
  TreeNode *y=nullptr; //parent pointer
  TreeNode *x=root;    //current pointer
  while(x!=nullptr){
    y=x;            //set parent to current
    if(BSTLessThan(newnode,x)) x=x->left; //move current to its child depending on the price
    else x=x->right;
  }
  if(root==nullptr) {root= newnode;root->height=1; return true;} //if no root, insert at root
  if(y!=nullptr) {
    if(BSTLessThan(newnode,y)) {updateBSTParentChild(newnode,y,true);} //if less than parent price insert at parent's left
    else {updateBSTParentChild(newnode,y,false);} //else insert at right
  }
  htupdt(newnode);
  return true;
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
  // Implement find in BST

  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.
  TreeNode *x=root;
  TreeNode *newnode=new TreeNode(jrnyCode,-10);
  while(x!=nullptr){ //While x isn't null
        if (BSTLessThan(x,newnode)) x=x->right; //if journey code of x less than query code move down to right of x
        else if(BSTLessThan(newnode,x)) x=x->left; //else move to left of x
        else return x->getprice();
    }
  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
  // Implement deletion in BST
  
  // You MUST use only BSTLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke BSTLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}


