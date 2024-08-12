#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS() {
  int time=0; //time counter
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visited==0){//If node of graph isnt visited (a new separate connected component)
      DFSvisit(nodes[i], time); //visit it
      lenBST++; //Increment number of connected components
    }
  }
  for(int i=0;i<numNodes;i++){
    if(nodes[i].visited==1) nv1++; //Count number of nodes visited once
    else if(nodes[i].visited==2) nv2++; //Count number of nodes visited twice
    if(nodes[i].visited==2 && nodes[i].incyc ) num_incyc++; //Count number of nodes in cycle
  }
  return;
}

void Graph::printResults() {//Print the results
  cout<<"No. of connected components: "<<lenBST<<endl;
  cout<<"No. of nodes visited once: "<<nv1<<endl;
  cout<<"No. of nodes visited twice: "<<nv2<<endl;
  cout<<"No. of nodes that are present in a cycle: "<<num_incyc<<endl;
  cout<<endl;
  for(int i=0; i<lenBST; i++){//Print the individual BST
    tree[i].printBST("");
    cout<<endl;
  }
  return;
}

void Graph::DFSvisit(Node &w, int &t){//DFS Visit 
  tree[lenBST].insert(w.value);//Insert value of node into BST
  if(w.visited==0){//If it wasn't visited earlier
    w.visited++; //Increment visited
    w.arrtime1=t; //Set arrival time 1
    t++; //Increment time
  }
  else if(w.visited==1){//If it was visited once before
    w.visited++; //Increment visited
    w.arrtime2=t; //Set arrival time 2
    //Cases for node to be in cycle:
    /*It can only be in cycle if it was visited twice
    If it wasn't backtracked out from even once, then:
      if its parent was visited once then it should be different from the node's first parent
      if node's first parent was nullptr (source node) then the current parent's first parent must not be the source node
      if its parent was visited twice then w's current parent's first parent must not be w itself

    If it was backtracked from once, if and only if w's both parents are different then it is in cycle
    */
    if(w.deptime1==-1 && ((w.p1==nullptr && w.par->p1->value!=w.value) || (w.p1!=nullptr && w.p2!=nullptr && w.p1->value!=w.p2->value && w.par->visited==1) || (w.p1!=nullptr && w.p2!=nullptr && w.par->p1==nullptr && w.par->visited==2) || (w.p1!=nullptr && w.p2!=nullptr && w.value!=w.par->p1->value && w.par->visited==2) )) w.incyc=true;
    else if(w.deptime1!=-1 && w.p1!=nullptr && w.p2!=nullptr && w.p1->value!=w.p2->value) w.incyc=true;
    t++; //Increment time
  }
  listOfObjects<Node *> *itr=w.adjlist; //Iterate over the adjacency list
  while (itr!=nullptr){ //For all nodes adjacent to w
    if(itr->object->visited<2 && (w.par==nullptr || itr->object->value!=w.par->value)){
      //If visited <2 and not w's current parent
      itr->object->par=&w; //Set the current parent
      if(itr->object->visited==0) itr->object->p1=&w; //Set first parent if visiting the first time
      else itr->object->p2=&w; //Set second parent if visiting the second time
      DFSvisit(*itr->object,t); //Visit the node
    }
    itr=itr->next; //Go to the next node
  }
  if(w.visited==1) {w.deptime1=t; t++;} //While backtracking the first time, store the departure time
  //Increment time
  return;
}

#endif
