//  Author: Sean Davis

#include <cstring>
#include "encoder.h"
using namespace std;

Encoder::Encoder() : heap(257)
{
 
} // Encoder()


Encoder::~Encoder()
{
} // ~Encoder()


void Encoder::createTree(const unsigned char *message, const int size)
{
  int counts[256];
  memset(counts, 0, sizeof(counts));
  BinaryNode *node1, *node2;
  
  for(int i = 0; i < size; i++)
    counts[message[i]]++;
  
  heap.currentSize = 0;
  
  for(int i = 0; i < 256; i++)
    if(counts[i] > 0)
      heap.array[++heap.currentSize] = new BinaryNode(counts[i], NULL, NULL, i);

  heap.buildHeap();
  
  while(heap.currentSize > 1)
  {
    heap.deleteMin(&node1);
    heap.deleteMin(&node2);
    heap.insert(new BinaryNode(node1->count + node2->count, node1, node2));
  }
  
  root = heap.array[1];
  Encoding encoding(0, 0);
  traverse(root, encoding, 0);
/*  
  for(int i = 0; i < 256; i++)
    if(encodings[i].count > 0)
    {
      cout << (char) i << ": ";
      for(unsigned j = 0x80000000, k = 0; k < encodings[i].count; j >>= 1, k++)
        if(j & encodings[i].encoding)
          cout << '1';
        else
          cout << '0';
      cout << endl;
    }
 */ 
}  // createTree()

void Encoder::traverse(BinaryNode *node, Encoding encoding, unsigned mask)
{
  if(node->letter != -1)
  {
    
    for(int i = 0; i < 4; i++)
    {
      encodings[node->letter] = encoding; 
      masks[node->letter] = mask;  
    }
    
    encodings[node->letter].count = encoding.count;
  }  // if node is an actual letter

  mask |= 0x80000000U >> encoding.count;
  encoding.count++;
  
  if(node->left)
    traverse(node->left, encoding, mask); 
  
  if(node->right)
  {
    encoding.encoding |= 0x80000000 >> (encoding.count - 1);
    traverse(node->right, encoding, mask);
  }
}
void Encoder::encode(const unsigned char *message, const int size, 
  unsigned char *encodedMessage, 
    int *encodedSize)
{
  unsigned pos = 1, bitPos = 0, word, letterWord;
  createTree(message, size);
  
  for(int i = 0; i < 256; i++)
  {
    encodings[i].encoding |= encodings[i].count;
    memcpy(&encodedMessage[pos],  &encodings[i].encoding, sizeof(unsigned));
    pos += sizeof(unsigned);
  }  // for each of 256 chars
  
  for(int i = 0; i < size; i++)
  {
    letterWord = encodings[message[i]].encoding;
    word = (word & ~(masks[message[i]] >> bitPos)) | (letterWord >> bitPos);
    bitPos += encodings[message[i]].count;
    
    while(bitPos > 7)
    {
       encodedMessage[pos++] = word >> 24;
/*      for(int j = 0x80; j > 0; j >>= 1)
        if(encodedMessage[pos - 1] & j)
          cout << '1';
        else
          cout << '0';
*/      
      word <<= 8;
      bitPos -= 8;
    }
  }  // for each char in message
  encodedMessage[pos] = word >> 24;
  encodedMessage[0] = (char) bitPos;
  *encodedSize = pos;
}  // encode()
