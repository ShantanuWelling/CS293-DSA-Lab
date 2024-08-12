#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the left child of parentNode, and
  // parentNode is the left child of grandParentNode
  // That's why we are doing a rotateLeftLeft
  if(grandParentNode->parent!=nullptr){
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered 1!" << endl;
    return false;
  }

  // Let T3 be the right child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parentNode->right;

  // Now replicate the single rotation for LeftLeft as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that currNode should be
  // made the left child of parentNode
  updateAVLParentChild(currNode, parentNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of parentNode
  updateAVLParentChild(grandParentNode, parentNode, false);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the right subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the right child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the right subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become the left
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);
  }
  else{
    //Similar steps but without involving great grandparent
    TreeNode *T3 = parentNode->right;
    updateAVLParentChild(currNode, parentNode, true);
    updateAVLParentChild(grandParentNode, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    root=parentNode;
    parentNode->parent=nullptr;//Update root
  }
  return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
  // Going back to Prof. Naveen Garg's lecture, x is *currNode,
  // y is *parentNode and z is *grandParentNode

  // Moreover, currNode is the right child of parentNode, and
  // parentNode is the left child of grandParentNode.  That's
  // why we are doing a rotateLeftRight
  if(grandParentNode->parent!=nullptr){
  TreeNode *greatGrandParentNode = grandParentNode->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParentNode) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParentNode) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered 2!" << endl;
    return false;
  }

  // Let T2 be the left child of currNode (i.e. of x)
  TreeNode *T2 = currNode->left;
  
  // Let T3 be the right child of currNode (i.e. of x)
  TreeNode *T3 = currNode->right;

  // Now replicate the double rotation for LeftRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild
  //
  // We can directly implement the double rotation, instead of doing two
  // rotations sequentially.  So we'll look at the end-result of the
  // double rotation (refer Prof. Garg's lecture notes) and arrive at that
  // from the original tree.

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that parentNode should be
  // made the left child of currNode
  updateAVLParentChild(parentNode, currNode, true);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that grandParentNode
  // should NOT be made the left child of currNode
  updateAVLParentChild(grandParentNode, currNode, false);
  
  // Recall from Prof. Garg's lectures that the left subtree of 
  // parentNode (i.e. y in Prof. Garg's lectures) and right subtree of
  // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
  // after the LeftRight rotation.  So do don't need to update the
  // left child of parentNode and the right child of grandParentNode
  // at all.
  // The only update needed is that the left subtree of currNode (i.e.
  // x in Prof. Garg's notes) should now become the right subtree of
  // parentNode (y in Prof. Garg's notes).  Similarly, the right subtree
  // of currNode (i.e. of x) should now become the left subtree of
  // grandParentNode (i.e. of z).
       
  // Let's implement these updations below.
       
  // We use "false" as the third argument of the following call to indicate
  // that T2 should NOT become the left child of ParentNode
  updateAVLParentChild(T2, parentNode, false);

  // We use "true" as the third argument of the following call to indicate
  // that T3 should become the left child of grandParentNode
  updateAVLParentChild(T3, grandParentNode, true);
  }
  else{
    //Similar steps but without involving great grandparent
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;
    updateAVLParentChild(parentNode, currNode, true);
    updateAVLParentChild(grandParentNode, currNode, false);
    updateAVLParentChild(T2, parentNode, false);
    updateAVLParentChild(T3, grandParentNode, true);
    root=currNode;
    currNode->parent=nullptr; //update root
  }

  return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // currNode is the left child of parentNode, and
  // parentNode is the right child of grandParentNode.  That's
  // why we are doing a rotateRightLeft
  if(grandParent->parent!=nullptr){
  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode

  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered 3!" << endl;
    return false;
  }

  // Let T1 be the left child of currNode (i.e. of x)
  TreeNode *T1 = currNode->left;
  
  // Let T2 be the right child of currNode (i.e. of x)
  TreeNode *T2 = currNode->right;

  // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

  // Make parentNode (y in Prof. Garg's lectures) the right child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that parentNode should be
  // made the right child of currNode
  updateAVLParentChild(parent, currNode, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // currNode (x in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should NOT be made the right child of currNode
  updateAVLParentChild(grandParent, currNode, true);
  
  // We use "true" as the third argument of the following call to indicate
  // that T2 should become the left child of ParentNode
  updateAVLParentChild(T2, parent, true);

  // We use "false" as the third argument of the following call to indicate
  // that T1 should become the right child of grandParentNode
  updateAVLParentChild(T1, grandParent, false);
  }
  else{
    //Similar steps but without involving great grandparent
    TreeNode *T2 = currNode->left;
    TreeNode *T3 = currNode->right;
    updateAVLParentChild(parent, currNode, false);
    updateAVLParentChild(grandParent, currNode, true);
    updateAVLParentChild(T3, parent, true);
    updateAVLParentChild(T2, grandParent, false);
    root=currNode;
    currNode->parent=nullptr; //update root
  }
  
  return true;
}
void AVLTree::htupdt(TreeNode *cnode){//Updates height of a given node
  if(cnode->left==nullptr && cnode->right==nullptr) cnode->height=0;
  else if (cnode->left==nullptr && cnode->right!=nullptr) cnode->height=cnode->right->height+1;
  else if (cnode->left!=nullptr && cnode->right==nullptr) cnode->height=cnode->left->height+1;
  else cnode->height=max(cnode->left->height,cnode->right->height)+1;
  return;
}
bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
  // Implement this yourself
  if(grandParent->parent!=nullptr){
  TreeNode *greatGrandParentNode = grandParent->parent;
  
  // First find if grandParentNode is the left or right child of
  // greatGrandParentNode
  
  bool isGPLeftChild;
  if (greatGrandParentNode->left == grandParent) {
    isGPLeftChild = true;
  }
  else if (greatGrandParentNode->right == grandParent) {
    isGPLeftChild = false;
  }
  else {
    cerr << "Unexpected condition encountered 4!" << endl;
    return false;
  }

  // Let T3 be the left child of parentNode (i.e. of y, using notation
  // from Prof. Garg's lectures
  TreeNode *T3 = parent->left;

  // Now replicate the single rotation for RightRight as from the lecture
  // notes/video using *ONLY* calls to updateAVLParentChild

  // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
  // child of greatGrandParentNode
  updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);

  // Make currNode (x in Prof. Garg's lectures) the right child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "false" to indicate that currNode should be
  // made the right child of parentNode
  updateAVLParentChild(currNode, parent, false);
  
  // Make grandParentNode (z in Prof. Garg's lectures) the left child of
  // parentNode (y in Prof. Garg's lectures)
  // The last parameter is "true" to indicate that grandParentNode
  // should NOT be made the right child of parentNode
  updateAVLParentChild(grandParent, parent, true);

  // Recall from Prof. Garg's lectures that the left and right subtrees
  // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
  // the LeftLeft rotation.  So do don't need to update the children of
  // currNode at all.
  // Similarly, the left subtree of grandParentNode (i.e. z in Prof.
  // Garg's lectures) stays unchanged.  Hence, the left child of
  // grandParentNode doesn't need to be updated at all.
  // The only update needed is that the left subtree of parentNode (i.e.
  // y in Prof. Garg's notes) should now become the right
  // child of grandParentNode (i.e. of z in Prof. Garg's notes).

  // We use "false" as the third argument of the following call to indicate
  // that T3 should become the right child of grandParentNode
  updateAVLParentChild(T3, grandParent, false);
  }
  else{
    //Similar to above steps but without great grandparent
    TreeNode *T3 = parent->left;
    updateAVLParentChild(currNode, parent, false);
    updateAVLParentChild(grandParent, parent, true);
    updateAVLParentChild(T3, grandParent, false);
    root=parent;
    parent->parent=nullptr;//Update Root
  }
  return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
  // Implement insertion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be inserted
  // and invoke AVLLessThan on the current node in the tree that you
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
    if(AVLLessThan(newnode,x)) x=x->left; //move current to its child depending on the price
    else x=x->right;
  }
  if(root==nullptr) {root= newnode;root->height=1; return true;} //if no root, insert at root
  if(y!=nullptr) {
    if(AVLLessThan(newnode,y)) {updateAVLParentChild(newnode,y,true);} //if less than parent price insert at parent's left
    else {updateAVLParentChild(newnode,y,false);} //else insert at right
  }
  TreeNode *a=newnode; //Tracker of current node while looping
  bool rotate=false;//Temp variable just for using bool rotate functions
  while(true){
    int balance;
    if(a->left==nullptr && a->right==nullptr) {a->height=0;balance=0;} //If both childs null
    else if (a->left==nullptr && a->right!=nullptr) {a->height=a->right->height+1; balance=-(a->right->height+1);} //If only right child
    else if (a->left!=nullptr && a->right==nullptr) {a->height=a->left->height+1; balance=a->left->height+1;} //If only left child
    else {a->height=max(a->left->height,a->right->height)+1; balance=a->left->height-a->right->height;} //If 2 children

    //Check balance and AVLLessThan for one of the 4 rotatations
    if (balance>1 && a->left!=nullptr){
      if(AVLLessThan(newnode,a->left)) {
        rotate=rotateLeftLeft(a->left->left,a->left,a); 
        htupdt(a);//Update height of the node
        break;}
      else if (AVLLessThan(a->left,newnode)) {
        TreeNode *alr=a->left->right;
        TreeNode *al=a->left;
        rotate=rotateLeftRight(a->left->right,a->left,a);
        htupdt(a); //Update heights of the nodes after rotation
        htupdt(al);
        htupdt(alr);
        break;
        }
    }
    else if (balance < -1 && a->right!=nullptr){
      if(AVLLessThan(a->right,newnode)){rotate=rotateRightRight(a->right->right,a->right,a); htupdt(a); break;}
      else if(AVLLessThan(newnode,a->right)){
        TreeNode *arl=a->right->left;
        TreeNode *ar=a->right;
        rotate=rotateRightLeft(a->right->left,a->right,a);
        htupdt(a); //Update height of the nodes after rotation
        htupdt(ar);
        htupdt(arl);
        break;
        }
    }
    if(a->parent!=nullptr) a=a->parent;//If parent not null recursively update parent's height
    else break;  
  }
  return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
  // Implement find in AVL tree.
  // This is really no different from finding in a binary search tree.
  // This operation cannot cause any balance factor disturbances.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.
  TreeNode *x=root;
  TreeNode *newnode=new TreeNode(jrnyCode,100);
  while(x!=nullptr){ //While x isn't null
        if (AVLLessThan(x,newnode)) x=x->right; //if journey code of x less than query code move down to right of x
        else if (AVLLessThan(newnode,x)) x=x->left; //else move to left of x
        else return x->getprice();
    }
  // We use "return -1" below to enable compilation.  Change this as you
  // see fit.
  return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
  // Implement deletion in AVL tree followed by balance factor restoration
  // by properly identifying x, y, z as used in Prof. Garg's lectures
  // (equivalently, currNode, parentNode, grandParentNode in our code) and
  // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
  // rotateRightRight as appropriate.

  // It is your responsibility to find out the right x, y, z (or currNode,
  // parentNode, grandParentNode) following Prof. Garg's lectures
  //
  // Once you identify these correctly, simply invoking the appropriate
  // rotation(s) should do the job.
  // You don't even need to invoke rotation twice for the double
  // rotations -- the way rotationLeftRight is implemented, and
  // rotationRightLeft should be implemented, you should be able to achieve
  // the effect of the double rotation using one invokation of the
  // appropriate member function.

  // You MUST use only AVLLessThan to compare two journey codes.  You
  // can create a new node containing the journey code to be searched
  // (along with some arbitrary price) and invoke AVLLessThan on the
  // current node in the tree that you are inspecting and the new node
  // to do your comparison.

  // REMEMBER to update the height of appropriate nodes in the tree
  // after a successful deletion.
  
  // We use "return true" below to enable compilation.  Change this as you
  // see fit.
  return true;
}


