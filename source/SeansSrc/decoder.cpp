//  Author: Sean Davis
#include <cstring>
#include "decoder.h"
#include "encoder.h"
using namespace std;

Decoder::Decoder()
{
} // Decoder()


Decoder::~Decoder()
{
} // ~Decoder()


void Decoder::constructTrie(const unsigned char *encodedMessage)
{
  unsigned mask, code;
  int j, count;
  
  TrieNode *ptr;
  
  for(int i = 0; i < 256; i++)
  {
    memcpy(&code, &encodedMessage[i * sizeof(unsigned) + 1], sizeof(unsigned));
    count = code & 0x1f;
    ptr = &root;
    
    for(j = 0, mask = 0x80000000; j < count; j++, mask >>= 1)
    {
      if(code & mask)
      {
        if(!ptr->right)
          ptr->right = new TrieNode();
        
        ptr = ptr->right;
      }  // if a 1 bit
      else  // zero at this position
      {
        if(!ptr->left)
          ptr->left = new TrieNode();
        
        ptr = ptr->left;
      }  // else a zero bit
    }  // for each bit in encoding
    
    ptr->letter = i;
  } // for each character
}  // constructTrie



void Decoder::decode(const unsigned char* encodedMessage, const int encodedSize, 
  unsigned char* decodedMessage, int *decodedSize)
{
  unsigned decodePos = 0;
  char endBitPos =  encodedMessage[0];
  unsigned pos = 256 * sizeof(unsigned) + 1;
  unsigned bitPos = 0;
  
  constructTrie(encodedMessage);
  
  while(pos < encodedSize || bitPos != endBitPos)
  {
    TrieNode *ptr = &root;
    while(ptr->left || ptr->right)
    {
      if(encodedMessage[pos] & (0x80 >> bitPos))
        ptr = ptr->right;
      else
        ptr = ptr->left;
      
      if(++bitPos == 8)
      {
        bitPos = 0;
        pos++;
      }  // if reached end of char
    }  // while not at leaf
    
    decodedMessage[decodePos++] = ptr->letter;
  }  // while not reached end of encoded message
  *decodedSize = decodePos;
} // decode()
