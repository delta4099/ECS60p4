//  Author: Sean Davis

#include "encoder.h"
#include "BinaryHeap.h"
#include "dsexceptions.h"
#include <iostream>

using namespace std;

class Trie
{
public:
  char value; 
  int freqSum; 
  Trie * right; 
  Trie * left; 
  
  Trie()
  {
    
  }
  

  Trie(Trie * l, Trie * r)
  {
    left = l; 
    right = r; 
    value = 0; 
    freqSum = l->freqSum + r->freqSum; 
  }
  
  Trie (char val, int c): value(val), freqSum(c)
  {
    left = NULL; 
    right = NULL; 
  }
  
  ~Trie()
  {
    
  } 
  
  bool operator < ( Trie& x ) const
  {
    if (freqSum < x.freqSum)
      return true; 
      
    return false; 
  }
  
  
};

void printTrie(Trie* x)
{
  cout << x->value << " "; 
  printTrie(x->left); 
  printTrie(x->right); 
}

Encoder::Encoder()
{
} // Encoder()


Encoder::~Encoder()
{
} // ~Encoder()

void Encoder::encode(const unsigned char *message, const int size, 
  unsigned char *encodedMessage, 
    int *encodedSize)
{
  // makes count array and records frequencies of letters in message
  int freq[256] = {}; 
  for (int i = 0; i < size; i++)
    freq[message[i]]++;
    
  // print out letters with frequencies
  
  // end print
  
  BinaryHeap <Trie *> heap(255);
  
  // inserts used letters into binary heap
  for (int i = 0; i < 256; i++)
  {
    if ( freq[i] )
    {
      cout << "**TEST** char: " << (char)i << " ; freq: " << freq[i] << endl;
      Trie *x = new Trie( (char)i, freq[i]) ; 
      heap.insert( x );
    } 
  }
  
  // reorders binary heap until only one Trie left
  Trie *temp; 
  temp = heap.findMin();
  while ( ! heap.isEmpty() )
  {
    Trie * left;
    Trie * right;  
    heap.deleteMin(left);
    heap.deleteMin(right); 
    Trie * x = new Trie(left, right); 
    heap.insert( x ); 
    temp = heap.findMin(); 
  }
  
  printTrie(temp); 
}  // encode()



