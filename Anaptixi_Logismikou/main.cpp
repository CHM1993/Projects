/* 
 * File:   main.cpp
 * Author: george
 *
 * Created on October 28, 2014, 12:20 PM
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "HashTable.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    ifstream fp ("person.csv");
    ifstream pkp("person_knows_person.csv");
    ifstream intr("person_hasInterest_tag.csv");
    ifstream place("person_isLocatedIn_place.csv");
    ifstream org("person_studyAt_organisation.csv");
    ifstream orgw("person_workAt_organisation.csv");
    ofstream nod("nodes");
    strA *stringAt;
    Pinakas_katakermatismou hash;
    intA* intAt;
    Attr* vima;
    Attr** propert;
    int   flag = 0;
    int f,i,idakm,k,kstart;
    Node* n;
    Node akm;
    string temp;
    string field;
    string names[8];
    List_of_Matches* lm;
    Forum* pin[3];
    Pinakas_katakermatismou** pn;
    Forum z,o,r;
    Node *arxikoNode;
    int recN,stoix,clid,clsiz, ii;
    int* clarr;
    Click *click;
    hash.createGraph(4,3);
    z.name = "Wall of Xiomara Fernandez";
    z.size = 82;
    o.name = "Album 23 of Xiomara Fernandez";
    o.size = 11;
    r.name = "Album 4 of Xiomara Fernandez";
    r.size = 62;
    
    pin[0] = &z;
    pin[1] = &o;
    pin[2] = &r;
    click = NULL;
    
    getline(fp,temp);                       //fortwma person
    while(getline(fp,temp)){                    //apo to person pairnoume
        k=0;                                    // k=0-2, ta onoma, fulo, birthday 
        n = (Node*)malloc(sizeof(Node));
        propert = createProperties(10);
        istringstream t(temp);
        for(i=0;i<5;i++){
        getline(t,field,'|');
            if(i==0){
                stringstream conv(field);
                conv>>f;            //metatropi se akeraio  
                nod<<f<<endl;
                n->setID(f);         //katoxurwsh id
            //    n->setAt(NULL);      //arxikopoihsh listas Attributes
                n->setNext(NULL);
            }
            else{
                if(i==2){
                continue;}
                setStringProperty(field.c_str(),k,propert);
                k++;        //index tou pinaka prop
            //    if(n->getAt() == NULL){
            //        n->setAt(stringAt);
            //    }
            //    else{
            //        vima = n->getAt();
            //        while(vima->next != NULL){
            //            vima = vima->next;
            //        }
            //        vima->next = stringAt;
                }
        }
        
        n->prop = propert;
        hash.insertNode(n,&hash);
//        hash.printAll();
        
    }
    cout<hash.lookupNode(495,&hash);
    //fortwma person
    getline(pkp,temp);                           //prwti grammi person knows person 
    while(getline(pkp,temp)){
        istringstream t(temp);
        stringstream conv;
        getline(t,field,'|');
        conv<<field<<" ";
        getline(t,field);
        conv<<field<<endl;
        conv>>f;
        conv>>idakm;
        cout<<f<<" knows "<<idakm<<endl; 
        
//        getchar();
        akm.setID(f);
        akm.setNext(NULL);
        hash.insertEdge(idakm,&akm,&hash);
//        if(f==38){
//        getchar();}
    }
//    hash.printAll();
    n = hash.lookupNode(7107,&hash);
    getline(intr,temp);                 //Prwti grammi twn interests
    while(getline(intr,temp)){          //Interests lista stin thesi 3
        istringstream t(temp);
        stringstream conv;
        getline(t,field,'|');
        conv<<field<<" ";
        getline(t,field);
        conv<<field<<endl;
        conv>>f;            //person id
        conv>>idakm;        // tag id
        if(f != n->getID()){
            n = hash.lookupNode(f,&hash);
        }
        intAt = new intA;
        intAt->name = 3;
        intAt->value = idakm;  
        intAt->next = n->prop[3];
        n->prop[3] = intAt;
    //    vima->next = intAt;
    //    vima = vima->next;
    }

    getline(place,temp);                 //Prwti grammi twn places
    while(getline(place,temp)){
        istringstream t(temp);
        stringstream conv;
        getline(t,field,'|');
        conv<<field<<" ";
        getline(t,field);
        conv<<field<<endl;
        conv>>f;            //person id
        conv>>idakm;        // place id
        if(f != n->getID()){      //to teleutaio tag den itan ston idio komvo
            n = hash.lookupNode(f,&hash);
        }
        intAt = new intA;
        intAt->name = 4;
        intAt->value = idakm;  
        intAt->next = n->prop[4];
        n->prop[4] = intAt;
    }

    getline(org,temp);                 //Prwti grammi twn organisations
    while(getline(org,temp)){
        istringstream t(temp);
        stringstream conv;
        getline(t,field,'|');
        conv<<field<<" ";
        getline(t,field);
        conv<<field<<endl;
        conv>>f;            //person id
        conv>>idakm;        // org id
        if(f != n->getID()){      //to teleutaio org den itan ston idio komvo
            n = hash.lookupNode(f,&hash);
        }
        intAt = new intA;
        intAt->name = 5;
        intAt->value = idakm;  
        intAt->next = n->prop[5];
        n->prop[5] = intAt;
    }
    
    getline(orgw,temp);                 //Prwti grammi twn interests
    while(getline(orgw,temp)){          //Interests lista stin thesi 3
        istringstream t(temp);
        stringstream conv;
        getline(t,field,'|');
        conv<<field<<" ";
        getline(t,field);
        conv<<field<<endl;
        conv>>f;            //person id
        conv>>idakm;        // organisation id id
        if(f != n->getID()){
            n = hash.lookupNode(f,&hash);
        }
        intAt = new intA;
        intAt->name = 6;
        intAt->value = idakm;  
        intAt->next = n->prop[6];
        n->prop[6] = intAt;
    //    vima->next = intAt;
    //    vima = vima->next;
    }

 
    cout<<"Size "<<hash.getSize()<<endl;
//    getchar();
//    hash.printAll();
//    getchar();
    n = hash.lookupNode(7107,&hash);
//    vima = n->getAt();
    cout<<" To 7107 exei xar "<<endl;
    for(i=0;i<7;i++){
        if(i<3){
            cout<<((strA*)(n->prop[i]))->value<<endl;
        }
        else if(i==3){
            vima = (intA*)(n->prop[i]);
            cout<<"Interests "<<endl;
            while(vima != NULL){
                cout<<((intA*)vima)->value<<endl;
                vima = vima->next;
            }
            
        }
        else if(i==4){
            vima = (intA*)(n->prop[i]);
            cout<<"Places "<<endl;
            while(vima != NULL){
                cout<<((intA*)vima)->value<<endl;
                vima = vima->next;
            }
            
        }
        else if(i==5){
            vima = (intA*)(n->prop[i]);
            cout<<"Orgs "<<endl;
            while(vima != NULL){
                cout<<((intA*)vima)->value<<endl;
                vima = vima->next;
            }
            
        }
        else if(i == 6){
            vima = (intA*)(n->prop[i]);
            cout<<"Orgs Work"<<endl;
            while(vima != NULL){
                cout<<((intA*)vima)->value<<endl;
                vima = vima->next;
            }
        }
    }
 
    cout<<endl;
//    cout<<"Connected Components are "<<CCnumber(&hash)<<endl;
//    cout<<"Diameter is"<<diameter(&hash)<<endl;
//    n = hash.lookupNode(3755,&hash);
//    lm = matchSuggestion (n,1,3,30,1,&hash);
//    while(lm != NULL){
//        cout<<lm->M.id<<endl;
//        cout<<lm->M.score<<endl;
//        lm = lm->next;
//    }
//    hash.printAll();
//    hash.lookupNode(1489,&hash);
    getchar();
    n = hash.lookupNode(3568,&hash);
    while(n != NULL){
        cout<<n->getID()<<endl;
        n = n->getNext();
    }
    pn = createForums(&hash,3,pin);
    n = pn[0]->lookupNode(3568,pn[0]);
    cout.flush();
    while(n->getNext()!=NULL){
        cout<<n->getID()<<endl;
        n = n->getNext();
    }
    clsiz = 3;
    click = NULL;
    clarr= (int*)malloc((clsiz)*sizeof(int));
    for(i = 0; i< clsiz; i++){
        clarr[i] = 0;
    }
    getchar();
    clid = 0;
    recN = 0;
    stoix = 0;
    arxikoNode = NULL;
    i = Clicks(&hash ,&recN,&stoix,&clid,clsiz,clarr, &click,arxikoNode);  
    cout<<"Ektypwnoume tis klikes pou vrikame"<<endl;
    getchar();
    
   if(click !=NULL){
        i = ClickinsertEdge(&click, clsiz);
        i = Clicksprint(click, clsiz);
    }
    cout<<"Edw"<<endl;
    
    return 0;
}
