HOW TO RUN:

Compile any of the queueTestx.C files (using Makefile -> Make queueTestx.C), any of the testFiles work.
Run the queueTestx.o File.

Implementation:
Implementation of the queue was created using NODES: QueueNode in combination with the queueStruct QueueADT. 

The QueueNode creates the 'Queue' storing the individual piece of data (as any form of data), and contains a "next" node that points to the next node in the queue. This is similar to Linked Lists we used in CS2

The QueueADT/queueStruct is a Struct that represents the queue holding 2 pointers: The "front" Node, and the "rear" node. As well as those, the struct also contains "cmp" that holds the comparison function for the Queue.

The functions work as inteded in the Header file, hence I didn't add comments on the code as the function's comments were already determined in the Header file Class.