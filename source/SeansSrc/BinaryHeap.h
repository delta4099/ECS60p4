#ifndef _BINARY_HEAP_H_
#define _BINARY_HEAP_H_
#include <iostream>
using namespace std;
class BinaryNode
{
public:
  int letter;
  BinaryNode *left;
  BinaryNode *right;
  int count;
  BinaryNode(int cnt, BinaryNode *lef = NULL, BinaryNode *r = NULL, 
    int let = -1) 
    : letter(let), left(lef),  right(r),  count(cnt) {}
};

class BinaryHeap
{
  public:
    explicit BinaryHeap( int capacity = 100 );

    bool isEmpty( ) const;
    bool isFull( ) const;
    const BinaryNode* findMin( ) const;

    void insert( BinaryNode *x );
    void deleteMin( );
    void deleteMin( BinaryNode **minItem );
    void makeEmpty( );
    int currentSize;  // Number of elements in heap
    BinaryNode *array[257];        // The heap array
    void buildHeap( );
    void percolateDown( int hole );
};

#endif
