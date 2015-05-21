  //reading message
  
  //message is encodedMessage shifted 1024 bytes
  
  // temp is head
  
  
  unsigned char *mes = {};
  
  Trie look = temp;
  
  for (int pos = 1025; pos < encodedSize; pos++)
  {
    
    
    
    for(int j = 0x80; j > 0; j >>= 1) 
      if(encodedMessage[pos] & j)
        look = look->right;
      else
        look = look->left;
        
    if (!look->left && !look->right)
    {
      mes += look->value;
      look = temp;
    }
    
  }
