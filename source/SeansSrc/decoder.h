// Author: Sean Davis
#ifndef DECODER_H
#define	DECODER_H
#include <iostream>
using namespace std;

class TrieNode
{
public:
  char letter;
  TrieNode *left;
  TrieNode *right;
  TrieNode(char let = 0, TrieNode *lef = NULL, TrieNode *r = NULL)
    : letter(let), left(lef),  right(r) {}
};

class Decoder
{
  TrieNode root;
  void constructTrie(const unsigned char *encodedMessage);
public:
  Decoder();
  ~Decoder();
  void decode(const unsigned char* encodedMessage, const int encodedSize, 
    unsigned char* decodedMessage, int *decodedSize);
private:

};

#endif	/* DECODER_H */

