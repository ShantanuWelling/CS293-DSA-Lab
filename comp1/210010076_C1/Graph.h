#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

//Linked list for adjacency lists
template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;
  listOfObjects<T> *prev;
  
  // Constructor
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  
  // Destructor
  ~listOfObjects() {;}
};

//BSTNode class
class BSTNode{
public:
  int val; //Value of BST node
  BSTNode *left; //Pointer to left node
  BSTNode *right; //Pointer to right node
  BSTNode *parent; //Pointer to parent node
  BSTNode(int v){ //Constructor
    val=v;
    left=right=parent=nullptr;
  }
  ~BSTNode(){;} //Destructor
};

class BST { //Binary search tree class
  // Add your own field and members here
public:
  BSTNode * root; //Pointer to root of tree
  BST(BSTNode *r){ //Default constructor with root
    root=r;
  }
  BST(){ //Empty tree constructor
    root=nullptr;
  }
  ~BST(){;} //Destructor
  void insert(int v){ //Insert into BST same as done in Lab 3
      if(root == nullptr){
        root= new BSTNode(v);
        return;
      }
      BSTNode *curr=root;
      while (true){
        if(v>curr->val){
          if(curr->right==nullptr){
            curr->right=new BSTNode(v);
            curr->right->parent=curr;
            break;
          }
          else{
            curr=curr->right;
          }
        }
        else{
          if(curr->left!=nullptr){
            curr = curr->left;
          }
          else{
            curr->left = new BSTNode(v);
            curr->left->parent=curr;
            break;
          }
      }
      }
      return;
  }
  // Feel free to use the printBST function used earlier
  void printBST(const string& prefix, bool isLeft=false){
    if( root != nullptr ){
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << '('<< root->val<<')' << endl;
        BSTNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
    return;
  }
};

class Node {
 public:
  int value; //Value of Node
  listOfObjects<Node *> *adjlist=nullptr; //Adjacency list of a node
  int visited=0; //Number of times node is visited
  bool incyc=false; //If in cycle
  int arrtime1, arrtime2, deptime1=-1; //First and second arrival times and first time backtrack
  Node *par=nullptr; //Pointer to current parent node
  Node *p1=nullptr; //Pointer to the parent when node was visited the first time
  Node *p2=nullptr; //Pointer to the parent when node was visited the second time
  Node(){;} //Destructor
  // insert other fields and methods as appropriate
};

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  BST * tree; //BST Tree of graph
  Graph(int nNodes, int nEdges, string gFileName) {
    numNodes = nNodes;
    numEdges = nEdges;
    graphFile.open(gFileName, ios::out);
    if (!graphFile.is_open()) {
      cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
      exit(-1);
    }

    graphFile << numNodes << endl;
    graphFile << numEdges << endl;

    nodes = new Node[numNodes];
    if (nodes == nullptr) {
      cerr << "Memory allocation failure." << endl;
      exit(-1);
    }

    for (int i = 0; i < numNodes; i++) {
      nodes[i].value = i+1;
    }

    srand(time(0));
    int n1, n2;
    int countEdges = 0;
    
    while (countEdges < numEdges) {
      n1 = rand() % numNodes;
      n2 = rand() % numNodes;
      if(n1!=n2){
        bool found=false; //Check if already edge exists between them
        listOfObjects<Node *> *check=nodes[n1].adjlist; //Iterate through the adjacency list to check
        while(check!=nullptr){
          if(check->object->value==nodes[n2].value){
            found=true;
            break;
          }
          check=check->next;
        }
        if(!found){//If edge not present
          if(nodes[n1].adjlist==nullptr){//If adjacency list is empty, create a new list
            nodes[n1].adjlist= new listOfObjects<Node *>(&nodes[n2]);
          }
          else{//Else add at the end of the list
            listOfObjects<Node *> *itr=nodes[n1].adjlist;
            while(true){//Go to the end of the adjacency list
              if(itr->next!=nullptr) itr=itr->next;
              else break;
            }
            listOfObjects<Node *> *temp=itr;
            itr=itr->next;
            itr=new listOfObjects<Node *>(&nodes[n2]);
            itr->prev=temp;
            temp->next=itr;
          }
          if(nodes[n2].adjlist==nullptr){//Similar process for adding to adjacency list of other node
            nodes[n2].adjlist= new listOfObjects<Node *>(&nodes[n1]);
          }
          else{
            listOfObjects<Node *> *itr1=nodes[n2].adjlist;
            while(true){
              if(itr1->next!=nullptr) itr1=itr1->next;
              else break;
            }
            listOfObjects<Node *> *temp1=itr1;
            itr1=itr1->next;
            itr1=new listOfObjects<Node *>(&nodes[n1]);
            itr1->prev=temp1;
            temp1->next=itr1;
          }
          graphFile << n1+1 << " " << n2+1 << endl;
          countEdges++;
        }
      }

      // Create an undirected edge from n1 to n2 and store in appropriate
      // adjacency list(s).  If an undirected edge from n1 to n2 (or
      // equivalently from n2 to n1) already exists, you shouldn't add
      // an edge.  Only if such an undirected edge didn't exist earlier,
      // should you add the edge and increment countEdges; otherwise,
      // do not increment countEdges;
      // Every time an edge is created, we also add that information to
      // graphFile
      
    }
    // Add appropriate code as necessary for your implementation
    tree=new BST[numNodes]; //Create a new BST array for storing multiple connected components
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  int lenBST=0; //Number of connected components (number of BST)
  int nv1=0; //Number of vertices visited once
  int nv2=0; //Number of vertices visited twice
  int num_incyc=0; //Number of nodes present in a cycle
  void DFSvisit(Node &w, int &t); //DFS-visit (referred from CLRS pseudocode)
  void modifiedDFS();
  void printResults();
};

#endif
