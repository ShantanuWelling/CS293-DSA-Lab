#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

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

class BSTNode{
public:
  int val;
  BSTNode *left;
  BSTNode *right;
  BSTNode *parent;
  BSTNode(int v){
    val=v;
    left=right=parent=nullptr;
  }
  ~BSTNode(){;}
};

class BST {
  // Add your own field and members here
public:
  BSTNode * root;
  BST(BSTNode *r){
    root=r;
  }
  BST(){
    root=nullptr;
  }
  ~BST(){;}
  void insert(int v){
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
  int value;
  listOfObjects<Node *> *adjlist=nullptr;
  int lenadj=0;
  int visited=0;
  bool incyc=false;
  int arrtime1, arrtime2, deptime1=-1;
  Node *par=nullptr, *p1=nullptr, *p2=nullptr;
  Node(){;}
  // insert other fields and methods as appropriate
};

//int a[8]={4,1,3,2,5,4,2,1}; int b[8]={5,4,4,5,3,2,3,3}; int i=0;

class Graph {
  int numNodes;
  int numEdges;
  fstream graphFile;
  Node *nodes;

  // Add appropriate fields as necessary for your implementation
  
 public:
  BST * tree;
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
    int i=0;
    int a[8]={6,4,4,3,1,7,2,5};
    int b[8]={2,3,8,6,8,3,5,6};

    for(int i=0;i<8;i++){
        n1=a[i]-1;
        n2=b[i]-1;
        cout<<n1<<n2<<endl;
        bool found=false;
        listOfObjects<Node *> *check=nodes[n1].adjlist;
        while(check!=nullptr){
          if(check->object->value==nodes[n2].value){
            found=true;
            break;
          }
          check=check->next;
        }
        if(!found){
          if(nodes[n1].adjlist==nullptr){
            nodes[n1].adjlist= new listOfObjects<Node *>(&nodes[n2]);
          }
          else{
            listOfObjects<Node *> *itr=nodes[n1].adjlist;
            while(true){
              if(itr->next!=nullptr) itr=itr->next;
              else break;
            }
            listOfObjects<Node *> *temp=itr;
            itr=itr->next;
            itr=new listOfObjects<Node *>(&nodes[n2]);
            itr->prev=temp;
            temp->next=itr;
          }
          if(nodes[n2].adjlist==nullptr){
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
          nodes[n1].lenadj++;
          nodes[n2].lenadj++;
          graphFile << n1+1 << " " << n2+1 << endl;
          countEdges++;
        }
    }
    // Add appropriate code as necessary for your implementation
    tree=new BST[numNodes];
  }
      
  ~Graph() {
    if (graphFile.is_open()) {
      graphFile.close();
    }
    delete[] nodes;
    // Add appropriate code as necessary for your implementation
  }

  // Add appropriate method declarations as necessary for your implementation
  int lenBST=0;
  int nv1=0, nv2=0, num_incyc=0;
  void DFSvisit(Node &w, int &t);
  void modifiedDFS();
  void printResults();
};

void Graph::modifiedDFS() {
  int time=0;
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visited==0){
      DFSvisit(nodes[i], time);
      lenBST++;
    }
  }
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visited==1) nv1++;
    else if(nodes[i].visited==2) nv2++;
    if(nodes[i].visited==2 && nodes[i].incyc ) {num_incyc++; cout<<"Incycle "<<nodes[i].value<<endl;}
  }
  return;
}

void Graph::printResults() {
  cout<<"No. of connected components: "<<lenBST<<endl;
  cout<<"No. of nodes visited once: "<<nv1<<endl;
  cout<<"No. of nodes visited twice: "<<nv2<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<num_incyc<<endl;
  cout<<endl<<endl;
  for(int i=0; i<lenBST; i++){
    tree[i].printBST("");
  }
  for(int i=0;i<numNodes;i++){
    listOfObjects<Node *>*itr=nodes[i].adjlist;
    cout<<nodes[i].value<<": ";
    while(itr!=nullptr){
      cout<<itr->object->value<<", ";
      itr=itr->next;
    }
    cout<<endl;
  }

  return;
}

void Graph::DFSvisit(Node &w, int &t){
  static int l=1;
  cout<<w.value<<" visited "<<l++<<endl;
  //cout<<"hel"<<l++<<endl;
  tree[lenBST].insert(w.value);
  //cout<<"oh"<<l++<<endl;
  if(w.visited==0){
    w.visited++;
    w.arrtime1=t;
    t++;
  }
  else if(w.visited==1){
    w.visited++;
    w.arrtime2=t;
    if(w.deptime1==-1 && ((w.p1==nullptr && w.par->p1->value!=w.value) || (w.p1!=nullptr && w.p2!=nullptr && w.p1->value!=w.p2->value && w.par->visited==1) || (w.p1!=nullptr && w.p2!=nullptr && w.par->p1==nullptr && w.par->visited==2) || (w.p1!=nullptr && w.p2!=nullptr && w.value!=w.par->p1->value && w.par->visited==2) )) w.incyc=true;
    else if(w.deptime1!=-1 && w.p1!=nullptr && w.p2!=nullptr && w.p1->value!=w.p2->value) w.incyc=true;
    t++;
  }
  listOfObjects<Node *> *itr=w.adjlist;
  while (itr!=nullptr){
    //cout<<"nm"<<l++<<endl;
    if(itr->object->visited<2 && (w.par==nullptr || itr->object->value!=w.par->value)){

      //cout<<"bot"<<l++<<endl;
      itr->object->par=&w;
      if(itr->object->visited==0) itr->object->p1=&w;
      else itr->object->p2=&w;
      DFSvisit(*itr->object,t);
    }
    //cout<<"got"<<l++<<endl;
    itr=itr->next;
  }
  

  /**for(int j=0;j<w.lenadj;j++){
    if(w.adjlist[j]->visited<2 && w.adjlist[j]!=w.par1){
      w.adjlist[j]->par1=&w;
      DFSvisit(*w.adjlist[j], t);
    }
  }**/
  if(w.visited==1) {w.deptime1=t; t++;}
  return;
}

int main(int argc, char **argv)
{
  Graph *myGraph;

  if (argc != 4) {
    cerr << "Usage: " << argv[0] << " numNodes numEdges graphFile" << endl;
  }

  int numNodes = stoi(argv[1]);
  int numEdges = stoi(argv[2]);
  string graphFileName = argv[3];

  myGraph = new Graph(numNodes, numEdges, graphFileName);
  if (myGraph == nullptr) {
    cerr << "Memory allocation failure." << endl;
    exit(-1);
  }

  myGraph->modifiedDFS();
  myGraph->printResults();

  return 0;
}

