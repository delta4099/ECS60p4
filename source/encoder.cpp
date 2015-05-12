//  Author: Sean Davis

#include "encoder.h"
#include "BinaryHeap.h"
#include "dsexceptions.h"

class Trie
{
public:
  char value; 
  int count; 
  Trie * right; 
  Trie * left; 
  
  Trie(); 
  ~Trie(); 
  Trie (char val, int c): value(val), count(c)
  {
    left = NULL; 
    right = NULL; 
  }
  bool operator < (const Trie& x)
  {
    if (count < x.count)
      return true; 
      
    return false; 
  }
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
  
  BinaryHeap <Trie> heap(255);
  
  // inserts used letters into binary heap
  for (int i = 0; i < 256; i++)
  {
    if ( freq[i] )
      heap.insert( new Trie((char)i, freq[i]) );
      
    
  }
  
}  // encode()



