/* 
 * File:   main.c
 * Author: adminuser
 *
 * Created on March 3, 2015, 10:47 AM
 */

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <limits.h>
#include "oracle.h"
#include "hash.h"
#include "tree_list.h"
#include "bloomfilter.h"


using namespace std;

int main(int argc, char** argv) {

    const char **word;
    const char **word2;
    const char *firstw;
    int seed, arithmos_anadromis;
    int bitnum, vathos;
    int *hasharray;
    int arithmo_pinaka_lexis;
    int *bloomfilter; //pinakas apo bits
    Tree_list *Tr_ptr;
    Tree_list *arxiko_N;
    int i, j, megethoshasharray, kleidi;
    int theseis_pinaka;
    ofstream oracl("oracle");
    
    //bloomfilter = malloc(argv[2]/(8 * sizeof(long)));
    if(argv[1] != NULL){
        megethoshasharray = atoi(argv[1]);
        hasharray = (int *)malloc(atoi(argv[1]) *sizeof(int));
        for(i = 0; i<atoi(argv[1]); i++){
            hasharray[i] =0;
        }
    }
    if (argv[2] != NULL){
        //prwta vriskoume posa bits einai ta bytes pou dothikan san orisma
        cout<< atoi(argv[2])<< endl;
        bitnum = atoi(argv[2]) *8;
        cout<<"To bitnum einai: "<< bitnum<< endl;
        getchar();
        theseis_pinaka = bitnum/32;
        bloomfilter = (int *)malloc((theseis_pinaka) *sizeof(int));
        cout<<"desmeytike" <<endl;
    }
//    for(i = 0; i<atoi(argv[2]); i++){
//        bloomfilter[i] = 0;
//    }
    if(argv[3] != NULL){
        vathos = atoi(argv[3]);
        cout<< "to vathos einai"<<vathos<<endl;
    }
    
    seed = 152;
    //seed = 39;
    //seed = 1233;
    initSeed(seed);
    i = 0;
    firstw = " ";
    //word = oracle(firstw);
    
    arithmo_pinaka_lexis = 0;
    arithmos_anadromis = 0;
    kleidi = 0;
    
    //tha valw sto dedro mou san 1o komvo to " "
    Tree_creation(&Tr_ptr);
    cout<<"Kaloyme tin anadromiki synartisi eisagwgis"<< endl;
    Tree_insert(&Tr_ptr, firstw, NULL, bitnum, hasharray, bloomfilter, megethoshasharray, vathos, &arithmos_anadromis, &kleidi, &arxiko_N);
    cout<<"Teleiwsan oles oi eisagwges tou dedrou mexri to vathos"<< vathos <<endl;

    getchar();
    if(kleidi == 0){
        cout<<"DEN VRETHIKE POTE I KRIFI LEXI!!"<< endl;
    }
    cout<<"twra pame na to ektypwsoume"<<endl;
    Tree_print(Tr_ptr);
    cout<<"Kai telos tha katastrepsoume to dedro"<< endl;
    Tree_Destroy(&Tr_ptr);
    cout<<"katastrafike, TELOS"<<endl;
//    if(word == NULL){ //vrikame tin krifi lexi
//    
//    }
//    if(word !=NULL){ //tha prepei na elenxoyme ta periexomena me to bloomfilter kai meta 
//        //an den vriskode mesa na ta eisagoyme stin domi mas
//        //Tree_insert(Tr_ptr, firstw, NULL );
//        while(word !=NULL){
//            //elegxw an einai sto bloomfilter kai an den einai tin eisagw sto dedro
//            for(j =0; j<atoi(argv[1]); j++){
//                
//            }
//            cout<< word[i]<< endl;
//            i = i +1;
//        }
//    }
//    word2 = static_cast <const char **> (word);
//    cout<< word2<<endl;
    //oracl<< word;
    return 0;
}



