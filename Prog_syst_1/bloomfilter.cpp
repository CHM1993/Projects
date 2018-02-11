#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include "oracle.h"
#include "hash.h"
#include "tree_list.h"

void  SetBit( int *bloomfilter,  int k ){ //k einai i thesi pou mas epistrefei mia hash function
    int i;
    int pos;

    unsigned int flag = 1;   // flag = 0000.....00001

    i = k/32;
    pos= k%32;

    flag = flag << pos;      // flag = 0000...010...000   (shifted k positions)

    bloomfilter[i] = bloomfilter[i] | flag;      // Set the bit at the k-th position in A[i]
    cout<<"egine i setBit"<< endl;
};


int TestBit( int *bloomfilter,  int k ){
  
    int i;
    int pos;

    unsigned int flag = 1;  // flag = 0000.....00001


    i = k/32;
    pos = k%32;

    flag = flag << pos;     // flag = 0000...010...000   (shifted k positions)

    if ( (bloomfilter[i] & flag) !=0 )  {    // Test the bit at the k-th position in A[i]
        cout<<"egine to test kai htan"<<endl;
        return 0;
    }
    else{
        cout<<"egine to test kai den htan"<< endl;
        return 1;
    }
};