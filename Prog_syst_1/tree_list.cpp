#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "oracle.h"
#include "hash.h"
#include "tree_list.h"
#include "bloomfilter.h"

void Tree_creation(Tree_list **Tr_ptr){
    printf("aha\n");
    *Tr_ptr = NULL;
};

int Tree_empty(Tree_list **Tr_ptr){
     
    if((*Tr_ptr) == NULL){
        return 1;
    }
};


int Tree_insert(Tree_list **Tr_ptr, const char *wordd, Tree_list *parent,int bitnum, int* hasharray, int* bloomfilter, int megethoshasharray, int vathos, int *arithmos_anadromis, int *kleidi, Tree_list **arxiko_N){

    int i;
    int yparxei;
    int num;
    int theseis_pinaka;
    Tree_list *tmp_tr;
    Tree_list *tmp2_tr;
    Tree_list *newparent;
    const char **pin_word;
    const char *prev_word;
    const char *temp_word;
    int arith_pinaka_lexis;
    
    cout<<"Bikame stin insert pou leitourgei anadromika."<< endl;
    cout<<"Hmaste stin anadromi "<< *arithmos_anadromis << endl;
    cout<<"printarw to mexri twra dedro"<<endl;
    
    tmp_tr = (*Tr_ptr);
    while(tmp_tr != NULL){
        cout<< "Lexi :  " << tmp_tr->word << endl;
        tmp_tr = tmp_tr->next;
    }
    
    cout<<"wordd einai"<< wordd<<endl;
    pin_word = oracle(wordd); //VRETHIKE TO LATHOS(stamatis) : Eprepe topin_word na to adigrapsw se alli metavliti,giati
                                //kathe fora p ginete i oracle() allazoun ola ta periexomena
    arith_pinaka_lexis =0;
    theseis_pinaka = 0;
    
    if(pin_word == NULL){
        cout<<"H krifi lexi vrethike kai einai :"<< wordd<<endl;
        *kleidi = 1;
        return 1;
    }
    
    if((Tree_empty(Tr_ptr)) == 1){
        cout<<"BIKAME STIN PERIPTWSI TREE_EMPTY!!!"<< endl;
        getchar();
        (*Tr_ptr) = (Tree_list *)malloc(sizeof(Tree_list)); /*dimiourgoume kainourio komvo*/
        (*Tr_ptr)->word = wordd;
        (*Tr_ptr)->next = NULL;
        (*Tr_ptr)->parent = parent;
//        if( parent != NULL){
//            (parent)->next = Tr_ptr;
//        }
        parent = *Tr_ptr;
        *arxiko_N = *Tr_ptr;
        cout<<"desmeytike o prwtos komvos"<<endl;
        
        //paw na valw to " " sto bloomfilter
        for(i = 0; i< megethoshasharray; i++){
            hasharray[i] = hash_by(i, pin_word[arith_pinaka_lexis]);
            cout<<"i "<< i <<" hash einai:"<<abs(hasharray[i]%bitnum)<<endl;
            theseis_pinaka = bitnum/32;
            num = abs(hasharray[i]%bitnum);
            SetBit(bloomfilter, num);
        }
        
        
        while(pin_word[arith_pinaka_lexis] !=NULL){
            cout<<"O arithmos tis lexis tou pinaka einai "<< arith_pinaka_lexis<< endl;
            
            cout<<"i lexi sto "<<arith_pinaka_lexis<<" stoixio tou pinaka einai" << pin_word[arith_pinaka_lexis]<< endl;
            
            //paw na elenxw an ayto to stoixeio vriskete sto bloomfilter, kai an den einai to vazw
            yparxei = 0;
            for(i = 0; i< megethoshasharray; i++){
                hasharray[i] = hash_by(i, pin_word[arith_pinaka_lexis]);
                cout<<"bitnum ="<< bitnum<< endl;
                theseis_pinaka = bitnum/32;
                cout<<"Theseis pinaka einai"<< theseis_pinaka<< endl;
                cout<<"i "<<i<<"hash einai:"<<abs(hasharray[i]%bitnum)<<endl;
                
                if(TestBit(bloomfilter, abs(hasharray[i]%bitnum)) == 0){ //ara einai mesa
                    cout<<"yparxei + 1"<<endl;
                    yparxei = yparxei +1;
                }
                cout<<"yparxei = "<< yparxei<<endl;
            }
            if(yparxei < megethoshasharray){ //ara eisagete sto bloomfilter kai sto dedro
                cout<<"Pame na to valoume sto bloom kai sto dedro"<<endl;
                yparxei = 0;
                cout<<"eisagete sto bloomfilter"<<endl;
                for(i = 0; i< megethoshasharray; i++){
                    theseis_pinaka = bitnum/32;
                    cout<<"i "<<i<<"hash einai:"<<abs(hasharray[i]%bitnum)<<endl;
                    num = abs(hasharray[i]%bitnum);
                    SetBit(bloomfilter, num);
                }
                    
                //paw na to valw kai sto dedro an den xepernaei to vathos tou dedrou,alliws den kanw tipota
                if(*arithmos_anadromis <= vathos){
                    cout<<"eisagete sto dedro"<<endl;
                    if(*Tr_ptr == NULL){
                        cout<<"Oxxxxxxxxxxxxxxxxxx"<<endl;
                    }
                    tmp_tr = (*Tr_ptr);
                    cout<<"tmp_tr->word "<< tmp_tr->word<<endl;
                    cout<<"Tr_ptr->word "<< (*Tr_ptr)->word<<endl;
                    while(tmp_tr->next != NULL){ //tha fygei otan ftasei ston teleytaio mi keno komvo
                        tmp_tr = tmp_tr->next;
                        cout<<"tmp_tr->word"<< tmp_tr->word << endl;
                    }
                    
//                    tmp2_tr = (Tree_list *)malloc(sizeof(Tree_list)); /*dimiourgoume kainourio komvo*/
//                    tmp2_tr->word = pin_word[arith_pinaka_lexis];
//                    tmp2_tr->next = NULL;
//                    
//                    if((*Tr_ptr)->next == NULL){
//                        (*Tr_ptr)->next = tmp2_tr;
//                    }
//                    else{
//                        while((*Tr_ptr)->next != NULL){
//                            cout<<"exei epomeno ara prepei na proxwrisw"<< endl;
//                            (*Tr_ptr) = (*Tr_ptr)->next;
//                        }
//                        (*Tr_ptr)->next = tmp2_tr;
//                    }
//                    tmp_tr->next = tmp2_tr;
                    tmp_tr->next= (Tree_list *)malloc(sizeof(Tree_list)); /*dimiourgoume kainourio komvo*/
                    temp_word = pin_word[arith_pinaka_lexis];
                    tmp_tr->next->word = temp_word;
                    cout<<"tmp_tr->word einai : "<< tmp_tr->next->word << endl;
                    tmp_tr->next->next = NULL;
                    tmp_tr->next->parent = parent;
                    
                    
                    cout<<"ektypwnw kai to dedro"<<endl;
//                    tmp_tr = *arxiko_N;
//                    while(tmp_tr != NULL){
//                        cout<< "Lexi :  " << tmp_tr->word << endl;
//                        tmp_tr = tmp_tr->next;
//                    }

                    cout<<"Desmeytike o Komvos! kai tha paw stin epomeni anadromi" <<endl;
                    //kai afou bike sto dedro kalw tin anadromi mou
//                    *arithmos_anadromis = *arithmos_anadromis +1;
//                    Tree_insert(Tr_ptr,
//                            pin_word[arith_pinaka_lexis], 
//                            tmp_tr, 
//                            bitnum,
//                            hasharray, 
//                            bloomfilter,
//                            megethoshasharray, 
//                            vathos, 
//                            arithmos_anadromis,
//                            kleidi,
//                            arxiko_N);
//                    *arithmos_anadromis = *arithmos_anadromis -1;
//                    if( *kleidi == 1){
//                        cout<<"to kleidi vrethike"<<endl;
//                        return 0;
//                    }
                }
                 
                    *arithmos_anadromis = *arithmos_anadromis +1;
                    Tree_insert(Tr_ptr,
                            pin_word[arith_pinaka_lexis], 
                            tmp_tr, 
                            bitnum,
                            hasharray, 
                            bloomfilter,
                            megethoshasharray, 
                            vathos, 
                            arithmos_anadromis,
                            kleidi,
                            arxiko_N);
                    *arithmos_anadromis = *arithmos_anadromis -1;
                     if( *kleidi == 1){
                        cout<<"to kleidi vrethike"<<endl;
                        return 0;
                    }
                
            }
            
//            *arithmos_anadromis = *arithmos_anadromis +1;
//            Tree_insert(Tr_ptr,
//                    pin_word[arith_pinaka_lexis], 
//                    tmp_tr, 
//                    bitnum,
//                    hasharray, 
//                    bloomfilter,
//                    megethoshasharray, 
//                    vathos, 
//                    arithmos_anadromis,
//                    kleidi,
//                    arxiko_N);
//            *arithmos_anadromis = *arithmos_anadromis -1;
//            if( *kleidi == 1){
//                cout<<"to kleidi vrethike"<<endl;
//                return 0;
//            }
            
            arith_pinaka_lexis = arith_pinaka_lexis +1; //teleytaia edwli stin while
        }
        
    }
    else{ //pame na elenzoume an briskete 
        while(pin_word[arith_pinaka_lexis] !=NULL){
            cout<<"HMASTE STIN DEYTERI PERIPTWSI KAI OXI STIN EMPTY"<< endl;
            
            cout<<"O arithmos tis lexis tou pinaka einai "<< arith_pinaka_lexis<< endl;
            
            cout<<"i lexi sto "<<arith_pinaka_lexis<<" stoixio tou pinaka einai" << pin_word[arith_pinaka_lexis]<< endl;
            
            //paw na elenxw an ayto to stoixeio vriskete sto bloomfilter, kai an den einai to vazw
            yparxei = 0;
            for(i = 0; i< megethoshasharray; i++){
                hasharray[i] = hash_by(i, pin_word[arith_pinaka_lexis]);
                theseis_pinaka = bitnum/32;
                cout<<"i "<<i<<"hash einai:"<<abs(hasharray[i]%bitnum)<<endl;
                
                if(TestBit(bloomfilter, abs(hasharray[i]%bitnum)) == 0){ //ara einai mesa
                    cout<<"yparxei + 1"<<endl;
                    yparxei = yparxei +1;
                }
                cout<<"yparxei = " << yparxei<< endl;
            }
            if(yparxei < megethoshasharray){ //ara eisagete sto bloomfilter kai sto dedro
                cout<<"pame na to valoume sto bloom kai sto dedro"<< endl;
                yparxei = 0;
                for(i = 0; i< megethoshasharray; i++){
                    theseis_pinaka = bitnum/32;
                    cout<<"i "<<i<<"hash einai:"<<abs(hasharray[i]%bitnum)<<endl;
                    num = abs(hasharray[i]%bitnum);
                    SetBit(bloomfilter, num);
                }
                    
                //paw na to valw kai sto dedro an den xepernaei to vathos tou dedrou,alliws den kanw tipota
                if(*arithmos_anadromis <= vathos){
                    cout<<"tha bei kai sto dedro giati den exoume xeperasei to ypsos mas"<<endl;
                    
                    tmp_tr = (*Tr_ptr);
                    cout<<"tmp_tr->word "<< tmp_tr->word<<endl;
                    cout<<"Tr_ptr->word "<< (*Tr_ptr)->word<<endl;
                    while(tmp_tr->next != NULL){ //tha fygei otan ftasei ston teleytaio mi keno komvo
                        tmp_tr = tmp_tr->next;
                        cout<<"tmp_tr->word"<< tmp_tr->word << endl;
                    }
                    
//                    tmp2_tr = (Tree_list *)malloc(sizeof(Tree_list)); /*dimiourgoume kainourio komvo*/
//                    tmp2_tr->word = pin_word[arith_pinaka_lexis];
//                    tmp2_tr->next = NULL;
//                   
//                    if((*Tr_ptr)->next == NULL){
//                        (*Tr_ptr)->next = tmp2_tr;
//                    }
//                    else{
//                        while((*Tr_ptr)->next != NULL){
//                            cout<<"Exei epomeno ara prepei na proxwrisw"<<endl;
//                            (*Tr_ptr) = (*Tr_ptr)->next;
//                        }
//                        (*Tr_ptr)->next = tmp2_tr;
//                    }
//                    tmp_tr->next = tmp2_tr;
                    
                    tmp_tr->next= (Tree_list *)malloc(sizeof(Tree_list)); /*dimiourgoume kainourio komvo*/
                    temp_word = pin_word[arith_pinaka_lexis];
                    tmp_tr->next->word = temp_word;
                    cout<<"tmp_tr->word einai : "<< tmp_tr->next->word << endl;
                    tmp_tr->next->next = NULL;
                    tmp_tr->next->parent = parent;
                    
                    cout<<"ektypwnw kai to dedro"<<endl;
                    tmp_tr = *arxiko_N;
//                    while(tmp_tr != NULL){
//                        cout<< "Lexi :  " << tmp_tr->word << endl;
//                        tmp_tr = tmp_tr->next;
//                    }

                    //kai afou bike sto dedro kalw tin anadromi mou
//                    *arithmos_anadromis = *arithmos_anadromis +1;
//                    Tree_insert(Tr_ptr,
//                            pin_word[arith_pinaka_lexis], 
//                            tmp_tr, 
//                            bitnum,
//                            hasharray, 
//                            bloomfilter,
//                            megethoshasharray, 
//                            vathos, 
//                            arithmos_anadromis,
//                            kleidi,
//                            arxiko_N);
//                    *arithmos_anadromis = *arithmos_anadromis -1;
//                    if( *kleidi == 1){
//                        cout<<"to kleidi vrethike"<<endl;
//                        return 0;
//                    }
                }
               
                    *arithmos_anadromis = *arithmos_anadromis +1;
                    Tree_insert(Tr_ptr,
                            pin_word[arith_pinaka_lexis], 
                            tmp_tr, 
                            bitnum,
                            hasharray, 
                            bloomfilter,
                            megethoshasharray, 
                            vathos, 
                            arithmos_anadromis,
                            kleidi,
                            arxiko_N);
                    *arithmos_anadromis = *arithmos_anadromis -1;
                     if( *kleidi == 1){
                        cout<<"to kleidi vrethike"<<endl;
                        return 0;
                    }
            }
            
//            *arithmos_anadromis = *arithmos_anadromis +1;
//            Tree_insert(Tr_ptr,
//                    pin_word[arith_pinaka_lexis], 
//                    tmp_tr, 
//                    bitnum,
//                    hasharray, 
//                    bloomfilter,
//                    megethoshasharray, 
//                    vathos, 
//                    arithmos_anadromis,
//                    kleidi,
//                    arxiko_N);
//            *arithmos_anadromis = *arithmos_anadromis -1;
//            if( *kleidi == 1){
//                cout<<"to kleidi vrethike"<<endl;
//                return 0;
//            }
            
            arith_pinaka_lexis = arith_pinaka_lexis +1; //teleytaia edwli stin while
        }
    }
    cout<<"Telos insert,eisixthisan oloi oi komvoi"<<endl;
    return 0;
};


void Tree_Destroy(Tree_list **Tr_ptr){
     Tree_list **Tmp_ptr;

     if(!Tree_empty(Tr_ptr)){
       Tree_Destroy(&((*Tr_ptr)->next));
       
       (*Tr_ptr)=(*Tmp_ptr)->next;
       free(*Tmp_ptr);            
     }
};

void Tree_print(Tree_list *Tr_ptr){
    const char*prev_word;
    Tree_list *tmp_tr;
    cout<<"BIKAME STIN PRINT TOU DEDROU"<< endl;
    tmp_tr = Tr_ptr;
    while(tmp_tr != NULL){
        cout<< "Lexi :  " << tmp_tr->word << endl;
        tmp_tr = tmp_tr->next;
    }
};