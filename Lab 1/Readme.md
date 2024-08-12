CS293 Lab 1 Readme file
210010076 Shantanu Welling

Implementation of the functions which are same for both queues:
IsEmpty: if the head and tail index is the same then the queue is empty

grow: If the initial array is full, create a new array of size N+ CONST_GROWTH, copy the initial array elements into the new array. Delete the initial array and make the intial array's pointer point to the new array. Set head=0 and tail to the size of the initial array and set the array size to N+CONST_GROWTH.

Implementation of the functions which are different for both queues:

size: if queue is empty returns 0. Else for linear queue returns tail-head. For circular queue if tail index is more than head index it returns tail-head, else it returns N-head+tail where N is the size of the array.

isFull: for linear queue if the tail= N it returns true as the tail index (which signifies where the next element would be inserted) is N and array indices go from 0 to N-1. For circular queue, first the head and tail values are stored into int type to avoid errors because of unsigned int type. if head-tail+N is divisible by N then the queue is full.

Qinsert: For linear queue, if the queue isn't full, insert element at tail and increment the tail. If the queue is full, grow the queue and then insert element at the tail and increment tail. For circular queue, if the queue isn't full, insert element at tail and assign tail as (tail+1)%N. If the queue is full, grow the queue and then insert element at the tail and assign tail as (tail+1)%N.

QDelete: If the queue is empty return false. Else place the element at the head of the queue into *T. For linear queue, increment the head. For circular queue assign head as (head+1)%N. Then return true for both queues. 

Time conclusion: 
Linear queue takes time (in given units) around 1/10th of the number of elements inserted/deleted. If the numbers of elements inserted/deleted are 10000 then time taken is approximately 1000 and for 100000 it is approximately 10000. So the time complexity of it is O(n).

Circular queue execution takes constant time of around 1000 units irrespective of the input size. So the time complexity is O(1000) or O(1).

