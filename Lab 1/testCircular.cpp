#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>

#define CONST_GROWTH 1000
#define INIT_SIZE 1000

template <typename T> class DynamicQueue {
private:
  T *A; // the array used for implementing the dynamic dequeue
  unsigned int N; // the current size of array A
  unsigned int head; // index where next element of queue will be deleted from
  unsigned int tail; // index where next element will be inserted
  unsigned int nextSize() { return N+CONST_GROWTH; }

public:
  DynamicQueue() // default constructor
  {
    A = new T[INIT_SIZE];
    if (A != nullptr) N = INIT_SIZE;
    else N = 0;
    head = 0;
    tail = 0;
  }
  ~DynamicQueue(){delete[] A;}; // default destructor

  bool isEmpty() // is the queue empty?
  {
  if(head==tail&&tail==0) return true;
  else return false;

  };

  unsigned int size() // return the current number of elements in the queue
  {
  if (this->isEmpty()==true) return 0;
  else if (tail>head) return tail-head;
  else return N-head+tail;
  };

  bool isFull() // is the queue full?
  {
  int h=head;
  int t=tail;
  if ((N+head-tail)%N==0&&tail!=0) return true;
  else return false;
  };

  void grow() // grow the queue to its next size
  {
  int siz=this->size();
  T *B= new T[N+CONST_GROWTH];
  for(int i=0;i<this->size();i++){
    B[i]=A[(head+i)%N];
    }
  delete[] A;
  A=B;
  head=0;
  tail=siz;
  N+=CONST_GROWTH;
  };

  void QInsert(T x) // insert given element at tail of the queue; grow array size as necessary
  {
  if(!this->isFull()) {A[tail]=x; tail=(tail+1)%N;}
  else {this->grow(); A[tail]=x; tail=(tail+1)%N;}
  };

  bool QDelete(T *x) // delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
  {
  if (this->isEmpty()) return false;
  *x= A[head];
  if((tail-head+N)%N==1) {head=0;tail=0;}
  else head=(head+1)%N;
  return true;
  };
};



using namespace std;
using namespace std::chrono;

void do_insert_delete(DynamicQueue<int>&, int, int&, int&);

int main() {
  try {
    DynamicQueue<int> myQueue; // Queue of integers
    int num_ins=0, num_del=0;
    int total_num_ops = 10000;
    int points_to_plot = 100;

    for (int i = 0; i < points_to_plot; i++) {
      auto start = std::chrono::high_resolution_clock::now();

      do_insert_delete(myQueue, total_num_ops, num_ins, num_del);

      auto stop = high_resolution_clock::now();

      auto duration = duration_cast<microseconds>(stop - start);
      cout << (num_ins + num_del) << " " << duration.count() << endl;
    }

    return 0;
  }
  catch (exception const& ex) {
    cerr << "Exception " << ex.what() << endl;
    return -1;
  }
}

void do_insert_delete(DynamicQueue<int>& q, int N, int& num_ins, int& num_del)
{
  int element;
  int modulus = 100;
  int thresh_for_del = 20;

  // Simple insertion deletion strategy: delete one element after every thresh_for_del steps

  srand(time(0));

  for (int i=0; i < N; i++) {
    if ((i > 0) && (i % thresh_for_del == 0)) {
      // Delete element from queue
      if (q.QDelete(&element)) {
	// Don't count deletions from empty queue
	num_del++;
      }
    }
    else {
      // Insert random element in queue
      element = rand() % modulus;
      q.QInsert(element);
      num_ins++;
    }
  }

  return;
}
