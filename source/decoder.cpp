//  Author: Sean Davis

#include "decoder.h"
#include "BinaryHeap.h"
#include "dsexceptions.h"
#include <iostream>
#include <string.h> 

using namespace std;


//-----------------------------------------------------------------------------
//TRIE
//-----------------------------------------------------------------------------

class Trie
{
public:
  unsigned int code; 
  int depth; 
  char value; 
  int freqSum; 
  Trie * right; 
  Trie * left; 
  
  Trie()
  {
   code = 0; 
   depth = 0; 
  }

  Trie( Trie * l,  Trie * r)
  {
    left = l; 
    right = r; 
   // cout << "TEST when construting left " << left->freqSum << " right "  << right->freqSum << endl; 
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
    // delete &freqSum; 
    // delete right; 
    // delete left; 
  } 
  
  /*
  bool operator < ( const Trie & x ) const
  {
  //  cout << "**TEST**   HElllo ???  !!  this is called"  << endl; 

    if (freqSum < x.freqSum)
      return true; 
      
    return false; 
    
  }
  
  */
};

void const printTrieD(const Trie& x)
{
  //cout << "begin" << endl;
  cout << "TEST value  " << x.value << " Test freqSum "  << x.freqSum << endl; 
  //cout << "TEST temp left and right freqSum Left: " << x.left->freqSum << " Right: " << x.right->freqSum << endl; 

  if (x.left)
  {
  //  cout << "TESTing left " << x.left->freqSum; 
    printTrieD(*(x.left));
  }
  if (x.right)
  {
  
    //cout << "Testing right "  << x.right->freqSum; 
    printTrieD(*(x.right)); 
  }
}



//-----------------------------------------------------------------------------
// DECODER
//-----------------------------------------------------------------------------



Decoder::Decoder()
{
} // Decoder()


Decoder::~Decoder()
{
} // ~Decoder()


void Decoder::decode(const unsigned char* encodedMessage, const int encodedSize, 
  unsigned char* decodedMessage, int *decodedSize)
{
      // int size = (sizeof(decodedMessage)/sizeof(decodedMessage[0]))/2;
      int size = sizeof(encodedMessage); 
    //  unsigned char *encodedMessageTemp = new unsigned char[size];
    //  memcpy(encodedMessageTemp, encodedMessage, size);
      

//     cout << endl; 
//      for (int pos = 0; pos < 200; pos++)
//   {
//      //cout << "**TEST** encodedMessageTemp[pos]: " << encodedMessageTemp[pos] << endl;
  
//      for(int j = 0x80; j > 0; j >>= 1) 
//       if(encodedMessageTemp[pos] & j)
//          cout << '1'; 
//       else
//          cout << '0';
//   }
   
   
//   cout << "THE FREQ in Decoder " << endl; 
    int freq[256] = {};
    memcpy(freq, encodedMessage, 1024); 
    
      int totalfreq = 0; 

    // for (int i = 0; i < 256; i++)
    // {
        // if (freq[i])
        // {
        //   cout << "Entering the loop i = " << i << endl; 
        //   cout << "Totalfreq before = "  << totalfreq << endl;
        //   cout <<  "The char "  << (char) i << "  Test Freq"  << freq[i] << endl; 
        //   totalfreq += (int)freq[i]; 
        //   cout << "Totalfreq after = " << totalfreq << endl << endl << endl; 

          
    //     }

    // }

   BinaryHeap <Trie> heap(256);
   
  for (int i = 0; i < 256; i++)
  {
    if ( freq[i] )
    {
      // cout << "Entering the loop i = " << i << endl; 
      // cout << "Totalfreq before = "  << totalfreq << endl;
      // cout <<  "The char "  << (char) i << "  Test Freq"  << (int) freq[i] << endl; 
      Trie x = * (new Trie( (char)i, freq[i]) ); 
      heap.insert( x );
      totalfreq += freq[i];
      // cout << "Totalfreq after = " << totalfreq << endl << endl << endl; 

    } 
  }
  
  // for (int i = 0; i < 256; i++)
  //   {
  //       if (freq[i])
  //         cout <<  "The char "  << (char) i << "  Test Freq"  << freq[i] << endl; 
  //   }
  Trie temp; 
  temp = heap.findMin();
  
  while ( ! heap.isEmpty() )
  {
    Trie  l;
    Trie  r;  
    
    heap.deleteMin(l);
    if (heap.isEmpty())
      break;

    heap.deleteMin(r); 
    
    temp = *(new Trie( new Trie(l), new Trie(r) )); 
    heap.insert( temp ); 
  }
  
  // printTrieD(temp); 
  
  // cout << endl << endl << totalfreq << "TEST" << endl; 
  
  
  
    //reading message
  
  //message is encodedMessageTemp shifted 1024 bytes
    int end = (encodedSize/8) + 1;

  // temp is head
  // cout << endl << endl << endl << "Decoder"  << endl; 
  // for (int pos = 1024; pos < end; pos++)
  // {
  //   for(int j = 0x80; j > 0; j >>= 1) 
  //     if(encodedMessage[pos] & j)
  //       cout << '1'; 
  //     else
  //       cout << '0';
  // }
  
  cout << endl << endl; 
  //unsigned char *mes = new unsigned char[sizeof(decodedMessage)];
  int posInMes = 0; 
  Trie look = temp;
  
  for (int pos = 1024; pos < end; pos++)
  {
    
    for(int j = 0x80; j > 0; j >>= 1) 
    {
      if(encodedMessage[pos] & j)
      {
        look = *look.right;
       // cout << "Testing right" << look.freqSum << endl; 
      }
      else
      {
        look = *look.left;
        //cout << "Testing left " << look.freqSum << endl; 
      } 
      if (!look.left && !look.right)
      {
        cout << "Test"  << look.value << endl; 
        decodedMessage[posInMes++] = look.value;
        look = temp;
      }
    }
  }
 *decodedSize = size; 
  
} // decode()
