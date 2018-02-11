#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "HashTable.h"
#include <string>



void degreeDistribution(Pinakas_katakermatismou* gr){
    int** degArr;
    char str[10];
    int i,j,k;
    int idt;
    int line=0,col=0;
    Node* tmp;
    Kouvas* curB;
    FILE *gp,*data;
    
    while(gr->getHash()[line]->getCur() == 0){
        line++;
    }
    cout<<"Starting line "<<line<<endl;
    tmp = gr->getHash()[line]->getBuck()[0];   //arxikopoihsh tmp
    degArr = (int**) malloc(2*sizeof(int*));    //desmeusi pinaka prwti grammi ta id deuteri oi vathmoi
    for(i=0;i<2;i++){
        degArr[i] = (int*) malloc(gr->getTotal()*sizeof(int));
    }
    for(j=0;j<gr->getTotal();j++){
        degArr[0][j]= -1;  //arxikopoihsh twn id
        degArr[1][j]= 0;   //arxikopoihsh twn degree
    }
    for(i=line;i<gr->getSize();i++){
        if(gr->getHash()[i] != NULL){
            for(j=0;j<gr->getHash()[i]->getCur();j++){
                tmp = gr->getHash()[i]->getBuck()[j];
                idt = tmp->getID();
            //    if(tmp != NULL && tmp->getNext() != NULL){
                    tmp = tmp->getNext();      //prwtos geitonas
            //    }
                    while(tmp!=NULL){       // kathe allos geitonas
                        for(k=0;k<gr->getTotal();k++){      //anazitisi ID
                            if((degArr[0][k] == tmp->getID()) || degArr[0][k] == -1){
                                degArr[0][k] = tmp->getID();
                                degArr[1][k]++;
                                break;
                            }
                        }
                        for(k=0;k<gr->getTotal();k++){      //anazitisi ID
                            if((degArr[0][k] == idt) || degArr[0][k] == -1){
                                degArr[0][k] = idt;
                                degArr[1][k]++;
                                break;
                            }
                        }
                    //    if(col<gr->getHash()[line]->getCur()){
                    //        col++;
                    //    }
                    //    else{
                    //        line++;
                    //        col = 0;
                    //    }
                        tmp = tmp->getNext();
                    }
                
            }
        }
    }
    data = fopen("data","w");
    
    for(j=0;j<gr->getTotal();j++){
        if(degArr[0][j] != -1){
            sprintf(str,"%d",degArr[0][j]);
            fprintf(data,str);
            fprintf(data," ");
            sprintf(str,"%d",degArr[1][j]/2);       //epeidi einai mi kateuthinomenos
            fprintf(data,str);
            fprintf(data,"\n");
        }
    }
    fclose(data);
    gp = popen("gnuplot -persist","w");
    if (gp == NULL){
        cout<<"\n\nError!!\n"<<endl;
    }
    fprintf(gp,"plot 'data' \n");
    fclose(gp);
}

int diameter(Pinakas_katakermatismou* gr){
    int i,j,k,tempi,tempj,temp;
    int max = -2;
    
    for(i=0; i <= gr->getSize()-1 ;i++){
        cout<<"I is "<<i<<endl;
        getchar();
            for(j=0;j<=gr->getHash()[i]->getCur()-1;j++){
                for(tempi=i;tempi<=gr->getSize()-1;tempi++){
                    if(tempi == i){
                        k = j;
                    }
                    else{
                        k = 0;
                    }
                    for(tempj=k;tempj<gr->getHash()[tempi]->getCur();tempj++){
                        if(i<gr->getSize()){
                        temp = gr->reachNode1(gr->getHash()[i]->getBuck()[j]->getID(),gr->getHash()[tempi]->getBuck()[tempj]->getID(),gr);
//                        cout<<"!!Distance "<<gr->getHash()[i]->getBuck()[j]->getID();
//                        cout<<" "<<gr->getHash()[tempi]->getBuck()[tempj]->getID();
//                        cout<<" is "<<temp<<endl;
//                        cout<<"Hash Size is "<<gr->getSize()<<endl;
                        }
                        if(temp>max){
                            max = temp;
                            cout<<"Max is "<<max<<endl;
                        }
     //                   cout<<"For 4"<<endl;
                        
                    }
    //                cout<<"For 3"<<endl;
                //    if(i>line-1){break;}
                }
    //            cout<<"For 2"<<endl;
            //    if(i>line-1){break;}
            }
    //        cout<<"For 1"<<endl;
    //        if(i>line-1){break;}
    }
    return max;
}

int averagePath(Pinakas_katakermatismou* gr){
    int i,j,k,tempi,tempj,temp,count=0,sum=0;
    int max = -2;
    
    for(i=0; i <= gr->getSize()-1 ;i++){
            for(j=0;j<=gr->getHash()[i]->getCur()-1;j++){
                for(tempi=i;tempi<=gr->getSize()-1;tempi++){
                    if(tempi == i){
                        k = j;
                    }
                    else{
                        k = 0;
                    }
                    for(tempj=k;tempj<gr->getHash()[tempi]->getCur();tempj++){
                        if(i<gr->getSize()){
                        temp = gr->reachNode1(gr->getHash()[i]->getBuck()[j]->getID(),gr->getHash()[tempi]->getBuck()[tempj]->getID(),gr);
                        }
                        if(temp>0){
                            sum += temp;
                            count++;
                        }
     //                   cout<<"For 4"<<endl;
                        
                    }
    //                cout<<"For 3"<<endl;
                //    if(i>line-1){break;}
                }
    //            cout<<"For 2"<<endl;
            //    if(i>line-1){break;}
            }
    //        cout<<"For 1"<<endl;
    //        if(i>line-1){break;}
    }
    return (sum/count);
}

int CCnumber(Pinakas_katakermatismou* gr){
    int i,j;
    int flag=0;
    int max=0;
    LOL lol;
    LOL* temp;
    
    lol.head = NULL;
    lol.next = NULL;
    for(i=0;i<gr->getSize();i++){
        for(j=0;j<gr->getHash()[i]->getCur();j++){
            cout<<"I J"<<i<<" "<<j<<endl;
            if(gr->getHash()[i]->getBuck()[j] != NULL){
                if(lol.head == NULL){
                    lol.head = BFS(gr->getHash()[i]->getBuck()[j]->getID(),gr);
                    lol.next = NULL;
                }
                else{
                    temp = &lol;
                    if((temp->head)->search(temp->head,gr->getHash()[i]->getBuck()[j]->getID()) != NULL){
                        flag = 1;
                    }
                    while(temp->next != NULL){      //Diatrexoume tin lista apo listes
                        cout<<"ID "<<temp->head->getID()<<endl;
                        if((temp->head)->search(temp->head,gr->getHash()[i]->getBuck()[j]->getID()) != NULL){
                            flag = 1;
                            break;
                        }
                        temp = temp->next;
                    }
                    if(flag != 1){      //An den uparxei to stoixeio pou psaxnoume
                        temp->next = (LOL*)malloc(sizeof(LOL));
                        temp->next->head = BFS(gr->getHash()[i]->getBuck()[j]->getID(),gr);
                    }
                    flag = 0;
                }
            }
        }
    }
    temp = &lol;
    while(temp != NULL){
        if (temp->head->length(temp->head) > max){
            max = temp->head->length(temp->head);
        }
        temp = temp->next;
    }
    cout<<"Max component has "<<max<<" nodes"<<endl;
    return lol.length(&lol);
}

List* BFS(int k,Pinakas_katakermatismou* gr){
    List* l;
    List* cur;
    Node* temp;
    
    l = (List*)malloc(sizeof(List));
    l->setNext(NULL);
    l->setID(k);
    l->insert(l,k);
    cur = l;
    while(cur != NULL){
        cout<<"Mpike";
        temp = gr->lookupNode(cur->getID(),gr);
        while(temp != NULL){
            if(l->search(l,temp->getID()) == NULL){
                l->insert(l,temp->getID());
            }
            temp = temp->getNext();
        }
        cur = cur->getNext();
    }
//    l->print();
    return l;
}

int friends(Node* n,Node* k){
    Node* temp=n->getNext();
    while(temp != NULL){
        if(temp->getID() == k->getID()){
            return 1;
        }
        temp = temp->getNext();
    }
    return 0;
}

/*
Matches *matchSuggestion (Node *n, int k, int h, int x, int limit, Pinakas_katakermatismou *g){

    Attr *nAtt, *att;
    intA *Att_int;
    strA *Att_str;
    Node* curr;
    string FILO;
    int is_located,study_org;
    int interests[500];
    int kk, k_koina, filter1, filter2, filter3, filter4,filter5, i, j, w, ilikia;
    double jaccard;
    Matches Mat;
    List_of_Matches *temp = NULL;
    List_of_Matches* vima;
    List_of_Matches *first = NULL;
    List* l;
    string tyear;
    int dif;
    
    kk = 0;

        FILO =((strA*)n->prop[1])->value; //Apothikeysi tou filou
        
        if((nAtt->name == 9)){ //located place
            Att_int = (intA *)nAtt;
            is_located =Att_int->value;
        }
        if((nAtt->name == 10)){ //study/organisation
            Att_int = (intA *)nAtt;
            study_org= Att_int->value;
        }
        if((nAtt->name == 8)){ //interests
            Att_int =(intA *) nAtt;
            interests[kk] =Att_int->value;
            kk = kk+1;
        }
        if((nAtt->name == 4 )){ //ILIKIA
           
            Att_str = (strA*)nAtt;
            tyear = (Att_str->value).substr(0,4); //efoson to etos exei 4 xar
            ilikia= atoi(tyear.c_str());
        }
//        att = n->getAt()->next;
        nAtt = nAtt->next;
//    }
    l = BFS(n->getID(),g);
    while(l->getNext() != NULL){
        if(g->reachNode1(n->getID(),l->getNext()->getID(),g) <= h){
//    for(i=0;i<g->getSize();i++){
  //      if(g->getHash()[i] != NULL){
    //        for(j=0;j<g->getHash()[i]->getC();j++){
      //          if(g->getHash()[i]->getBuck()[j] != NULL){
                    curr = g->lookupNode(l->getNext()->getID(),g);
                    nAtt = curr->getAt();
                    while(nAtt !=NULL){
                        if (nAtt->name == 3){ //filo
                            Att_str = (strA *)nAtt;
                            if( Att_str->value == FILO){
                                filter1 = 1;
                            }
                        }
                        if(nAtt->name == 9){ //locatedplace
                            Att_int = (intA *)nAtt;
                            if(Att_int->value == is_located){
                                filter2 = 1;
                            }
                        }
                        if(nAtt->name == 10){ //organisation
                            Att_int =(intA *) nAtt;
                            if(Att_int->value == study_org){
                                filter2 = 1;
                            }
                        }
                        if(nAtt->name == 8){ //interests
                            Att_int =(intA *) nAtt;
                            for(w = 0; w< kk; w++){
                                if(Att_int->value == interests[w]){
                                    k_koina = k_koina+1;
                                }
                            }
                        }
                        if(nAtt->name == 4){
                            Att_str=(strA *)nAtt;
                            tyear = (Att_str->value).substr(0,4);
                            dif = ilikia - atoi(tyear.c_str());
                            if(dif<0){
                            dif = dif*(-1);
                            }
                            if (dif <= x){
                                filter3 = 1;
                            }
                        }
                        nAtt = nAtt->next;
                    }
                    if(k_koina >=k){
                        filter4=1;
                    }
                    if (friends(n,curr) == 0){
                        filter5 = 1;
                    }
                    if((filter1 ==1) &&(filter2 ==1) &&(filter3==1)&& (filter4 == 1) && (filter5 == 0)){
                        filter1 = 0;
                        filter2 = 0;
                        filter3 = 0;
                        filter4 = 0;
                        filter5 = 0;
                        jaccard = (k_koina-kk)/(k_koina+kk);
                        Mat.id = curr->getID();
                        Mat.score = jaccard;
                        if(first == NULL){
                            first = (List_of_Matches*)malloc(sizeof(List_of_Matches));
                            first->M.id = Mat.id;
                            first->M.score = Mat.score;
                            first->next = NULL;
                            
                        }
                        else if(first->M.score < Mat.score){
                            temp = (List_of_Matches*)malloc(sizeof(List_of_Matches));
                            temp->M.id = Mat.id;
                            temp->M.score = Mat.score;
                            temp->next = first;
                            first = temp;
                        }
                        else{
                          vima = first;
                          while(vima->next != NULL && vima->next->M.score > Mat.score){
                              vima = vima->next;
                          }
                          temp = vima->next;
                          vima->next = (List_of_Matches*)malloc(sizeof(List_of_Matches));
                          vima->next->M.id = Mat.id;
                          vima->next->M.score = Mat.score;
                          vima->next->next = temp;
                        }
                    }
                    
                   
        }
        l = l->getNext();
    }
   //     }
 //   }
}
 */