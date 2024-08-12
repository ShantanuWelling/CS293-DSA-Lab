#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4


// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(){ root=nullptr; }
BST::BST(TreeNode *root){ this->root=root; }

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price) {
    TreeNode *x=root;
    while(x!=nullptr){ //While x isn't null
        if((x->price)==price && (x->JourneyCode)==JourneyCode) return true; //if values of x match the query return true
        else if ((x->price)>price) x=x->left; //if price of x more than query price move down to left of x
        else x=x->right; //else move to right of x
    }
    return false; } //return false if not found

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price) {
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

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price) {
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
    }

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::preorder(TreeNode *node1){
    if(node1==nullptr) return;
    else {
        cout<<node1->JourneyCode<<endl;
        if (node1->left!=nullptr) preorder(node1->left);
        if (node1->right!=nullptr) preorder(node1->right);
    }
    return;
}

void BST::postorder(TreeNode *node1){
    if(node1==nullptr) return;
    else {
        if (node1->left!=nullptr) postorder(node1->left);
        if (node1->right!=nullptr) postorder(node1->right);
        cout<<node1->JourneyCode<<endl;
    }
    return;
}

void BST::inorder(TreeNode *node1){
    if(node1==nullptr) return;
    else {
        if (node1->left!=nullptr) inorder(node1->left);
        cout<<node1->JourneyCode<<endl;
        if (node1->right!=nullptr) inorder(node1->right);
    }
    return;
}
void BST::inorder1(TreeNode *node1, int *arr, int &ind){//returns inorder traversal array
    if(node1==nullptr) return;
    else {
        if (node1->left!=nullptr) inorder1(node1->left, arr, ind);
        arr[ind++]=node1->price;
        if (node1->right!=nullptr) inorder1(node1->right,arr,ind);
    }
    return;
}

//2 arrays of preorder traversal storing journey code and corresponding price
void BST::preorder1(TreeNode *node1, int* arrjc, int* arrpc, int *ind){
    if(node1==nullptr) return;
    else {
        arrpc[(*ind)]=node1->price;
        arrjc[(*ind)]=node1->JourneyCode;
        (*ind)++;
        if (node1->left!=nullptr) preorder1(node1->left, arrjc,arrpc, ind);
        if (node1==root) {// when moving from left of root to right of root, store a sentinel character
            arrpc[(*ind)]=-2;
            arrjc[(*ind)]= -2;
            (*ind)++;
        }
        if (node1->right!=nullptr) preorder1(node1->right,arrjc,arrpc,ind);
    }
    return;
}


void BST::traverse(int typeOfTraversal) {
    if(typeOfTraversal==0) preorder(root);
    else if(typeOfTraversal==1) postorder(root);
    else if(typeOfTraversal==2) inorder(root);
    return; }

// Returns the price of the cheapest journey
int BST::getMinimum() {
    TreeNode *x=root;
    while(x->left!=nullptr){
        x=x->left;
    }
    return x->price;}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound) {
    int res[1000000];
    int index=0;
    int result=0;
    inorder1(root,res,index); //gets in-order traversal array
    for(int i=0;i<index;i++){//select prices withing bounds
        if (res[i]>=lowerPriceBound && res[i]<=upperPriceBound) result++;
    }
    return result; }

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.
void BST::customStore(string filename) {
    ofstream outfile;
    outfile.open(filename);
    int arrj[1000000],arrp[1000000];
    int size1=0;
    preorder1(root,arrj, arrp, &size1);
    for(int i=0;i<size1;i++){
        outfile<<arrj[i]<<" "<<arrp[i]<<endl;
    }
    outfile<<"-3 -3"<<endl;
    outfile.close();
    return; }

//Creates a tree using preorder array
TreeNode* BST::treecreate(int *arrj, int*arrp, int &insind, int minp, int maxp, int count1, TreeNode* par){
    if(insind==count1) return nullptr;
    int currentprice=arrp[insind];
    if(arrp[insind]>maxp || arrp[insind]<minp) return nullptr; //if out of range return null
    TreeNode *node1= new TreeNode(arrj[insind],arrp[insind],nullptr,nullptr,par); //make a new node
    insind++;
    node1->left=treecreate(arrj,arrp,insind,minp,currentprice-1,count1,node1); //update new nodes left and right from preorder traversal array
    node1->right=treecreate(arrj,arrp,insind,currentprice+1,maxp,count1,node1); // with changed bounds and updated index
    return node1;
}

// While loading a tree from a file written by customStore, we
// can have one of two modes of loading.  We could either ask
// for the entire tree to be loaded or only the left subtree of
// the root (if it exists) to be loaded.  The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the left subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.

void BST::customLoad (int flag, string filename) {
    ifstream infile;
    infile.open(filename);
    int arrj[1000000], arrp[1000000],count=0,insind=0, jc,pc;
    for(int i=0;i<1000000;i++){ //load journeycode and price into arrj and arrp
        infile>>jc>>pc;
        if(flag==LOAD_LEFT_SUBTREE && jc==-2) {break;} //custom store sentinel used to separate left tree
        if(jc==-3) {break;} //if -3 then file ended
        else if(jc==-2) {i--; continue;}
        else {arrj[i]=jc; arrp[i]=pc;count++;}
    }
    root=treecreate(arrj,arrp,insind,0,1000000,count,nullptr); //create BST, runtime is O(n)
    return; }


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
        result.push_back(to_string(root->JourneyCode) + "\n");
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
