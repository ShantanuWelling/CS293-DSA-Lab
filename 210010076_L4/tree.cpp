// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

#include "tree.h"

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance(){
  if (root == nullptr) return 0;
  else {
    root->longestPathLength=longestpath(root); //Updates root parameters
    root->shortestPathLength=shortestpath(root);
    return root->getImbalance(); //Returns imbalance [O(n)]
  }
}

int BST::longestpath(TreeNode* node1){
    if (node1 == nullptr) return 0;
    else {// Find the height of left, right subtrees
        int lefth= longestpath(node1->left);
        int righth= longestpath(node1->right);
        return max(lefth, righth) + 1; // Find max(subtree_height) + 1 to get longest path
    }
}

int BST::shortestpath(TreeNode *node1){
    if (node1 == nullptr) return 0;
    else {// Find the height of left, right subtrees
        int lefth= shortestpath(node1->left);
        int righth= shortestpath(node1->right);
        return min(lefth, righth)+1; // Find min(subtree_height) + 1 to get shortest path
    }
}

bool BST::insert(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace/augment it with appropriate code,
  // similar to what you had done in lab assignment 3.

  if(find(JourneyCode,price)) return false; //if element present return false
        TreeNode *y=nullptr; //parent pointer
        TreeNode *x=root;    //current pointer
        while(x!=nullptr){
            y=x;            //set parent to current
            if(price<(x->price)) x=x->left; //move current to its child depending on the price
            else x=x->right;
        }
        if(root==nullptr) root= new TreeNode(JourneyCode,price); //if no root, insert at root
        if(y!=nullptr) {
            if(price< y->price) y->left=new TreeNode(JourneyCode,price,nullptr,nullptr,y); //if less than parent price insert at parent's left
            else if(price> y->price) y->right= new TreeNode(JourneyCode,price,nullptr,nullptr,y); //else insert at right
        }
    return true;}

TreeNode* BST::nodemin(TreeNode *node1){
    TreeNode *x=node1;
    while(x->left!=nullptr){
        x=x->left; //move down left till encounter a null
    }
    return x; //return min node
}

//Successor of x is the least element larger than x
TreeNode* BST::sucscr(TreeNode *node1){//returns successor of given input node
    TreeNode *x=node1;
    if(x->right!=nullptr) return nodemin(x->right);
    else return nullptr;
}
  // JourneyCode is not present in the BST.  We must now
  // insert an appropriate child of parentOfCurrNode.
  // Please implement this part yourself.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to the new node you are inserting

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // You can look at the implementation of insert to code this part up.
    TreeNode *x=root;
    while(x!=nullptr){ //While x isn't null
        if((x->price)==price && (x->JourneyCode)==JourneyCode) return true; //if values of x match the query return true
        else if ((x->price)>price) x=x->left; //if price of x more than query price move down to left of x
        else x=x->right; //else move to right of x
    }
  return false;
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
  // The following filler code snippet is only given to facilitate
  // compilation.  You should replace it with appropriate code, very
  // similar to what you had done in lab assignment 3.
  //
  // Recall from CS 213 lectures about the various ways in which the
  // BST can be restructured when a node is deleted. You can implement
  // any of these alternatives.
  //
  // Do not forget to update shortestPathLength and
  // longestPathLength of (possibly all) BST nodes in the
  // path from the root to nodes whose position in the BST is affected
  // by the remove.
  if (!find(JourneyCode,price)) return false;//returns false if not in tree
    else {
        TreeNode *x=root;
        TreeNode *res; //pointer of node to be deleted
        while(true){//find the location of node to be deleted
            if((x->price)==price) {res=x; break;}
            else if ((x->price)>price) x=x->left;
            else x=x->right;
    }
        if(res==root){//if root is to be deleted
            if((res->left)==nullptr && (res->right)==nullptr){//0 children
                root=nullptr;
            }
            else if((res->left)==nullptr && (res->right)!=nullptr){//only right child
                res->right->parent=nullptr; //changing parent pointers and deleting the node
                this->root=res->right;
            }
            else if((res->left)!=nullptr && (res->right)==nullptr){//only left child
                res->left->parent=nullptr; //changing parent pointers and deleting the node
                this->root=res->left;
            }
            else {//2 children
                TreeNode *rep=sucscr(res); //successor can't have left child
                if(rep->right!=nullptr){ //if successor has right child
                    rep->parent->left=rep->right; //changing parent pointers and deleting the node
                    rep->right->parent=rep->parent;
                    int newjc=rep->JourneyCode;
                    int newpc=rep->price;
                    res->JourneyCode=newjc;
                    res->price=newpc;
                }
                else{ //if successor doesn't have children
                    int newjc=rep->JourneyCode;
                    int newpc=rep->price;
                    rep->parent->left=nullptr; //changing parent pointers and deleting the node
                    res->JourneyCode=newjc;
                    res->price=newpc;
                }
            }
        }
        else if(res->left==nullptr && res->right==nullptr){//no children
            if((res->price)<res->parent->price){//left child of its parent
                res->parent->left=nullptr; //changing parent pointers and deleting the node
            }
            else if(res->price>res->parent->price){//right child of its parent
                res->parent->right=nullptr;//changing parent pointers and deleting the node
            }
        }
        else if(res->left==nullptr && res->right!=nullptr){//right child
            if((res->price)<res->parent->price){//left child of its parent
                res->parent->left=res->right; //changing parent pointers and deleting the node
                res->right->parent=res->parent;
            }
            else if(res->price>res->parent->price){//right child of its parent
                res->parent->right=res->right; //changing parent pointers and deleting the node
                res->right->parent=res->parent;
                }
        }
        else if(res->left!=nullptr && res->right==nullptr){ //right child
           TreeNode *respar=res->parent;
           if((res->price)<res->parent->price){//left child of its parent
                respar->left=res->left; //changing parent pointers and deleting the node
                res->left->parent=respar;
           }

            else if(res->price>res->parent->price){//right child of its parent
                respar->right=res->left; //changing parent pointers and deleting the node
                res->left->parent=respar;
            }
        }
        else{//2 children
            TreeNode *rep=sucscr(res);//successor can't have left child
            if(rep->right!=nullptr){//if successor has right child
                rep->parent->left=rep->right;
                rep->right->parent=rep->parent;
                int newjc=rep->JourneyCode;
                int newpc=rep->price;
                res->JourneyCode=newjc;
                res->price=newpc;
            }
            else{//if successor doesn't have children
                int newjc=rep->JourneyCode;
                int newpc=rep->price;
                rep->parent->left=nullptr;
                res->JourneyCode=newjc;
                res->price=newpc;
            }
        }
    return true;
    }
  return false;
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft=false)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back((root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}

