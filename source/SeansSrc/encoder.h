// Author: Sean Davis
#ifndef ENCODER_H
#define	ENCODER_H

#include "BinaryHeap.h"

class Encoding
{
  public:
    char count;
    unsigned encoding;
    Encoding(char cnt = 0, unsigned enc = 0) : count(cnt), encoding(enc) {}
};

class Encoder
{
  BinaryHeap heap;
  BinaryNode *root;
  Encoding encodings[256];
  unsigned masks[256];
  void createTree(const unsigned char *message, const int size);
  void traverse(BinaryNode *node, Encoding encoding, unsigned  mask);
public:
  Encoder();
  void encode(const unsigned char *message, const int size, 
    unsigned char *encodedMessage, int *encodedSize);
  ~Encoder();
private:

};

#endif	/* ENCODER_H */

