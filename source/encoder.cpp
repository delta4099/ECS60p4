//  Author: Sean Davis

#include "encoder.h"
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
  int value; 
  int freqSum; 
  Trie * right; 
  Trie * left; 
  
  Trie()
  {
   code = 0; 
   depth = 0; 
  }

  Trie( Trie * l,  Trie * r, int v = 300) : value(v)
  //: value(300), freqSum(l->freqSum + r->freqSum)
  {
    left = l; 
    right = r; 
   //cout << "TEST when construting left " << left->freqSum << " right "  << right->freqSum << endl; 
    //value = 300; 
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

void const printTrie(const Trie& x)
{
  //cout << "begin" << endl;
  cout << "TEST value  " << (int) x.value << " Test freqSum "  << x.freqSum << endl; 
  //cout << "TEST temp left and right freqSum Left: " << x.left->freqSum << " Right: " << x.right->freqSum << endl; 

  if (x.left)
  {
  //  cout << "TESTing left " << x.left->freqSum; 
    printTrie(*(x.left));
  }
  if (x.right)
  {
  
    //cout << "Testing right "  << x.right->freqSum; 
    printTrie(*(x.right)); 
  }
}

void getCode(Trie t, unsigned int c, int d, unsigned int* codes, int *depths)
{
  t.code = c; 
  t.depth = d; 
  
  if (t.value < 280)
  {
     //c <<= (32 - d); 
     codes[(int) t.value] = c; 
     depths[(int) t.value] = d;
     return;
  }
  
  t.code <<= 1; 
  t.depth++; 
  if (t.left)
  {
    //unsigned int temp = code <<= 1; 
    getCode(*(t.left), t.code , t.depth, codes, depths ); 
  } 
  if (t.right)
  {
    //unsigned int temp = code <<= 1; 
    t.code |= 1;
    getCode(*(t.right), t.code, t.depth, codes, depths); 
  } 
 
  
}






//-----------------------------------------------------------------------------
// ENCODER
//-----------------------------------------------------------------------------




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
  /*
  for (int i = 0; i < 30; i++)
  {
    cout << i << "  TEST Message " << (int) message[i] << endl; 
   }
   */
  unsigned char *encodedMessageTemp = new unsigned char[size]; 
  // cout << " TEST Array before "  << endl; 
  // for (int pos = 0; pos < 30; pos++)
  // {
  //   //cout << "**TEST** encodedMessage[pos]: " << encodedMessage[pos] << endl;
  
  //   for(int j = 0x80; j > 0; j >>= 1) 
  //     if(encodedMessage[pos] & j)
  //       cout << '1'; 
  //     else
  //       cout << '0';
  // }
  
  
  // makes count array and records frequencies of letters in message
  int freq[256] = {}; 
 // memset(freq, 0, sizeof(freq));
 //memset(encodedMessage, 0, size + 1028);

 //memset(encodedMessageTemp, 0, size + 1028);

// int mempos = 0; 

  for (int i = 0; i < size; i++)
  {
    freq[message[i]]++;
  }
   memcpy(&encodedMessageTemp[1], freq, 1024); 

// for (int i = 0; i < 256; i++)
//     {
//         if (freq[i])
//           cout <<  "The char "  << (char) i << "  Test Freq"  << freq[i] << endl; 
//     }
    
  BinaryHeap <Trie> heap(256);
  
  // for (int i = 0; i < 256; i++)
  //   {
  //       if (freq[i])
  //         cout <<  "The char "  << (char) i << "  Test Freq"  << freq[i] << endl; 
  //   }
  
  // inserts used letters into binary heap
  //int totalfreq = 0; 
  int testSum = 0;
  for ( register int i = 0; i < 256; i++)
  {
    if ( freq[i] )
    {
      // cout << "Entering the loop i = " << i << endl; 
      // cout << "Totalfreq before = "  << totalfreq << endl;
      // cout <<  "The char "  << (char) i << "  Test Freq"  << freq[i] << endl; 
     //  totalfreq += (int)freq[i]; 

      Trie x = * (new Trie( (char)i, freq[i]) ); 
      heap.insert( x );
      testSum++;
      //totalfreq += freq[i]; 
  
      // cout << "Totalfreq after = " << totalfreq << endl << endl << endl; 

    } 
  }

  // reorders binary heap until only one Trie left
  Trie temp; 
  temp = heap.findMin();
  
  while ( heap.currentSize > 1 )
  {
    Trie  l;
    Trie  r;  
    
    heap.deleteMin(l);
    //if (heap.isEmpty())
      //break;

    heap.deleteMin(r); 
    
    temp = *(new Trie( new Trie(l), new Trie(r) )); 
    heap.insert( temp ); 
  }

 // printTrie(temp); 
  
  unsigned int codes[256] = {}; 
  int depths[256] = {}; 
  getCode(temp, 0, 0, codes, depths); 
  
  unsigned int totalDepths = 0; 
  // checks for correct code and depth
  for (int pos = 0; pos < 256; pos++)
  {
    if (depths[pos])
    {
      totalDepths += depths[pos]; 
      // cout << "The index is " << (char) pos << endl; 
      // cout << "12345678901234567890" << endl; 
    //   for(unsigned int j = 0x80000000; j > 0; j >>= 1)
    //   {
    //     if(codes[pos] & j)
    //       cout << '1';
    //     else
    //       cout << '0';
    //   }    
    // cout << endl << "test " << codes[pos] << endl << "The depth is " << depths[pos] << endl; 
    }
  }
  
  // test before 
 // memset(encodedMessage, 0, size);
  //encodedMessage = {0}; 
  /*
  cout << " TEST Array before "  << endl; 
  for (int pos = 0; pos < 200; pos++)
  {
    //cout << "**TEST** encodedMessage[pos]: " << encodedMessage[pos] << endl;
  
    for(int j = 0x80; j > 0; j >>= 1) 
      if(encodedMessage[pos] & j)
        cout << '1'; 
      else
        cout << '0';
  }
  */
  
  // cout << endl; 
  
  // cout << "Test if reach memcpy" << endl; 
   //(encodedMessage, 0x00, totalDepths + 2048); 
   //memcpy(encodedMessage, freq, 1024); 
  
  // for (int pos = 0; pos < 200; pos++)
  // {
  //   //cout << "**TEST** encodedMessage[pos]: " << encodedMessage[pos] << endl;
  
  //   for(int j = 0x80; j > 0; j >>= 1) 
  //     if(encodedMessage[pos] & j)
  //       cout << '1'; 
  //     else
  //       cout << '0';
  // }
  
  // cout << endl << "Done" << endl; 
 register int encodedCount = 1028;
  //int encodedCount = 2044; 
  // put huffman code into encodedMessage
  
  
  
  
  // workbench method
  unsigned int workbench = 0; 
  int bitpos = 0;
  int totalBits = 0; 
  
  // cout << size << endl; 
  
  for (register int pos = 0; pos < size; pos++)
  {
   // workbench = 0;
   //cout << "TEST !!!!!" << message[pos] << endl; 
   //cout << "TEST DEPTHS "  << depths[message[pos]]  << endl; 
    if(freq[message[pos]]) {
     // if (pos < 40 )
       // cout << "TEST message " << (int) message[pos] << " Test code "  << codes[message[pos]] << endl; 
      workbench = workbench | (codes[message[pos]] << (32 - depths[message[pos]] - bitpos));
     // cout << "test workbench" << endl;
      /*
      for(unsigned int j = 0x80000000; j > 0; j >>= 1)
      {
        if(workbench & j)
          cout << '1';
        else
          cout << '0';
      }    
      cout << endl;
      */
      bitpos += depths[message[pos]];
      totalBits += depths[message[pos]];

    }
    
    while (bitpos >= 8)
    {
      unsigned int lastWB = workbench;
      lastWB = lastWB >> 24;
     // cout << "**TEST** (char)lastWB: " << (char)lastWB << endl;
      encodedMessageTemp[encodedCount] = 0; 
      encodedMessageTemp[encodedCount++] = (char)lastWB;
      // for(int j = 0x80; j > 0; j >>= 1) 
      // if(lastWB & j)
      //   cout << '1'; 
      // else
      //   cout << '0';
      workbench = workbench << 8;
      bitpos -= 8;
    }
    
  }
  
  //cout << bitpos << endl; 
  encodedMessageTemp[0] = bitpos; 
  //if (bitpos > 0)
  //{
  unsigned int lastWB = workbench;
  lastWB = lastWB >> 24;
  encodedMessageTemp[encodedCount++] = (char)lastWB;
  workbench = workbench << 8;
  bitpos -= 8;
  //=}
  
  /*
  cout << endl << endl; 
  for (int pos = 1024; pos < size/8; pos++)
  {
    //cout << "**TEST** encodedMessage[pos]: " << encodedMessage[pos] << endl;
  
    for(int j = 0x80; j > 0; j >>= 1) 
      if(encodedMessage[pos] & j)
        cout << '1'; 
      else
        cout << '0';
  }
  */
  
  // cout << "The freq in encoder" << endl; 
  
  //cout << endl << endl << endl << totalfreq << endl << endl;
  
    // for (int i = 0; i < 256; i++)
    // {
    //     if (freq[i])
    //       cout <<  "The char "  << (char) i << "  Test Freq"  << freq[i] << endl; 
    // }

  // printTrie(temp);
  // cout << "THE END!!" << endl << endl << endl << endl; 
  
   
  
  // totalfreq = 0; 
  // for (int i = 0; i < 256; i++)
  //   {
  //       if (freq[i])
  //       {
  //         cout << "Entering the loop i = " << i << endl; 
  //         cout << "Totalfreq before = "  << totalfreq << endl;
  //         cout <<  "The char "  << (char) i << "  Test Freq"  << freq[i] << endl; 
  //         totalfreq += (int)freq[i]; 
  //         cout << "Totalfreq after = " << totalfreq << endl << endl << endl; 

          
  //       }

  //   }    
  memcpy(encodedMessage, encodedMessageTemp, size + 1028);
  *encodedSize = encodedCount;
  //cout << encodedCount << "TEST" << endl; 
 // cout << endl << endl << *encodedSize << endl << endl; 
  heap.makeEmpty(); 
  
  // for (int i = 0; i < 300; i++)
  //   {
  //     cout << "TESTING encodedMessage "  << (int) encodedMessage[i] << endl; 
  //   }
  

  //cout << endl << endl<< endl << "THE END" << endl << endl << endl; 
}  // encode()



