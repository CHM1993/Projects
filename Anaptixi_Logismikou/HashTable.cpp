#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "HashTable.h"
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

int List::setID(int i){
    this->id = i;
    return 1;
}

int List::getID(){
    return this->id;
}

int List::setNext(List* l){
    this->next = l;
    return 1;
}

List* List::getNext(){
    return this->next;
}

List* List::insert(List* start, int id){
    List* ins;
    while(start->getNext() != NULL){
        start = start->getNext();
    }
    ins = (List*) malloc(sizeof(List));
    ins->setID(id);
    ins->setPar(NULL);
    ins->setNext(NULL);
    start->setNext(ins);
    return ins;
}

void List::print(){
    List* temp=this;
    cout<<"Printing:\n"<<endl;
    while(temp->getNext() != NULL){
    cout<<temp->getID()<<" ";
    temp = temp->getNext();
    }
    cout<<temp->getID()<<endl;
}

int List::setPar(List* node){
    this->par = node;
}

List* List::getPar(List* node){
    return node->par;
}

List* List::search(List* start, int id){
//    if (start->id == id){
//    return start;
//    }
    while(start != NULL){
        if (start->getID() == id){
//            cout<<"Epistrefei gonea id:"<<start->id<<endl;
            return start;
        }
        start = start->getNext();
    }
//    cout<<"Epistrefei NULL"<<endl;
    return NULL;
}

int List::length(List* p){
    List* temp=p;
    int count = 0;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    return count-1;
}

int Node::getID(){
return this->id;
}

void Node::setID(int i){
    this->id = i;
}

//Attr* Node::getAt(){
//    return this->prop;
//}

//void Node::setAt(Attr* p){
//    this->prop = p;
//}

int Node::setNext(Node* nd){
    this->next = nd;
    return 1;
}

Node* Node::getNext(){
    return this->next;
}

int Kouvas::getCur(){
    return this->cur;
}

void Kouvas::setCur(int i){
    this->cur = i;
}

int Kouvas::setNode(Node* p){                     //insert node in cell c
    int i=0,flag=0;                 // DOULEUEI ALLA THELOUME DYADIKH!!
    Node* temp;
    while(i<(this->c) && flag == 0){    //den pername oria pinaka kai den exoume kanei eisagwgi
        cout<<i;
        cout<<"\n";
        if (this->Buck[i] == NULL){     //keni thesi
            this->Buck[i] = p;
            flag = 1;
            this->Buck[i]->setNext(NULL);
            i++; }
        else if(this->Buck[i]->getID() <= p->getID()){      //vriskoume mikrotero apo to ID tou p
            i++; }
        else if(this->Buck[i]->getID() > p->getID()){       //vriskoume megalutero
            temp = this->Buck[i];                           // metakinoume oles tis eggrafes mia thesi deksia
            this->Buck[i] = p;
            p = temp;                                       
            i++;}
    }
//    if(flag == 0){
//        this->setBuck((Node**)realloc(this,(this->getC()+3)*sizeof(Node*))); 
//        this->c = this->c + 3;
//        if(this->setNode(p) == 1){
//            this->cur = this->cur+1;
//            return 2;
//        }
//    }
    this->cur = this->cur+1; //
    return 1;
}

Node** Kouvas::getBuck(){
    return this->Buck;
}

int    Kouvas::setBuck(Node** buck){
    this->Buck = buck;
    return 1;
}

int Kouvas::Comp(){
    int i=0;
    int j=0;
    Node* temp;
    while(i<this->getC()){
        if(this->getBuck()[i] != NULL){
            temp=this->getBuck()[i];
            this->getBuck()[i]=NULL;
            this->getBuck()[j]= temp;
            j++;
        }
        i++;
    }
    return 1;
}

int    Kouvas::delNode(int i){
    this->Buck[i] = NULL;
    while(i < (this->cur-1)){
        if(((i+1)<this->c) && Buck[i+1] != NULL){
            Buck[i] = Buck[i+1];
            Buck[i+1] = NULL;
        }
        i++;
    }
    this->cur = this->cur-1; //
    return 1;
}

int Kouvas::getC(){
    return this->c;
}

int Kouvas::setC(int i){
    this->c = i;
    return 1;
}

Pinakas_katakermatismou* Pinakas_katakermatismou::createGraph(int m, int c){
    Node** Buc;
    int i,j,ok;
    this->size = m;                                         //poses einai oi theseis tou pinaka
    this->m = m;
    this->n = c;
    this->splitR = 0;                                       //arxikopoihsh splitting round
    this->countInsert = 0;                                          //thesi pinaka pou tha ginei split se periptwsi overflow
    this->total = 0;
    this->off = 0;
    this->HashArray =(Kouvas**) malloc(m*sizeof(Kouvas*));  //desmeusi pinaka
    for(i=0;i<m;i++){                                       //desmeusi gia tin class Kouvas
        this->HashArray[i] =(Kouvas*) malloc(sizeof(Kouvas));
        Buc = (Node**) malloc(c*sizeof(Node*));             //desmeusi keliwn Kouvas
        for(j=0;j<c;j++){                                   //Arxikopoihsh me NULL twn keliwn tou Kouvas
            Buc[j]=NULL;
        }                                           
        ok = (this->HashArray[i])->setBuck(Buc);            //elegxos
        this->HashArray[i]->setC(c);                        //arxikopoihsh tou c
        this->HashArray[i]->setCur(0);
        if(ok){
            cout<<"Kouvas Allocated!\n";
        }
    }
}

int Pinakas_katakermatismou::insertNode(Node* node, Pinakas_katakermatismou* gr){
    int k,j,i=0,num,inserted=0,ok=0,flag=0;
    int w;
    Node** Buc;
    int power;
    Kouvas* startB;
    Kouvas* destB;
    Node*   temp; 
    
    power = (int)(pow(2,(gr->splitR)))*(gr->m);
    k = node->getID() % power;            //vriskoume ton arithmo tou Kouvas
    if (k<(gr->countInsert)){
        power = (int)(pow(2,(gr->splitR+1)))*(gr->m);
        k = node->getID() % power; 
    }
    for(j=0;j<gr->HashArray[k]->getC();j++){
        if (gr->HashArray[k]->getBuck()[j] == NULL){
            flag = 1;                   //vrikame keni thesi
            break;
        }
    }
    if(flag == 1){
        inserted = (gr->HashArray[k])->setNode(node);
        if(inserted == 1){
            this->total = this->total+1;
        //    HashArray[k]->setCur(HashArray[k]->getCur()+1);
            cout<<"Cur of "<<k<<" is "<<HashArray[k]->getCur()<<endl;
            cout<<"Node inserted! \n";
        }
    }
    else{
        flag = gr->HashArray[k]->getC();
//        cout<<"Trying to realloc size= "<<2*(gr->HashArray[k]->getC())<<endl;
        ok = gr->HashArray[k]->setBuck((Node**)realloc(gr->HashArray[k]->getBuck(),(gr->HashArray[k]->getC()+n)*sizeof(Node*)));
        for(j=flag;j<(gr->HashArray[k]->getC()+n);j++){
            cout<<"Null gia "<<j<<endl;
            gr->HashArray[k]->getBuck()[j] = NULL;
        }
        gr->HashArray[k]->setC(gr->HashArray[k]->getC()+n);
        cout<<"The size of the array is ";
        cout<<gr->HashArray[k]->getC();
        cout<< "\nAnd the first element is:";
        cout<<gr->HashArray[k]->getBuck()[0]->getID();
        if(ok == 1){
            cout<<"Kouvas Doubled! \n";
            ok = 0;
        }
       
    //    cout<<"To ID tou Node EINAI ";
    //    cout<<node->getID();
        inserted = (gr->HashArray[k])->setNode(node);
    //    cout<<"\nInserted meta = ";
    //    cout<< inserted;
        if(inserted == 1){
            this->total = this->total+1;
        //    this->HashArray[k]->setCur(HashArray[k]->getCur()+1);
    //        cout<<"Cur of "<<k<<" is "<<HashArray[k]->getCur()<<endl;
    //        cout<<"Node inserted! \n";
    //      cout<<"ID: ";
    //      cout<<node->getID();
    //      cout<<"\nk: ";
    //      cout<<k;
    //      cout<<"\n";
        }
        gr->HashArray = (Kouvas**)realloc(gr->HashArray,((gr->size)+1)*sizeof(Kouvas*));
        gr->size = gr->size + 1;
                             //
    //    cout<<"\n\n";
    //    cout<<"SIZE ";cout<<gr->size;
        gr->HashArray[size-1] =(Kouvas*) malloc(sizeof(Kouvas));
        gr->HashArray[size-1]->setC(gr->n); //**
        gr->HashArray[size-1]->setCur(0);
        Buc = (Node**) malloc(HashArray[size-1]->getC()*sizeof(Node*));             //desmeusi keliwn Kouvas
        for(j=0;j<HashArray[size-1]->getC();j++){                                   //Arxikopoihsh me NULL twn keliwn tou Kouvas
            Buc[j]=NULL;
        }
        gr->HashArray[size-1]->setBuck(Buc);
        startB = gr->HashArray[countInsert];
        num = gr->HashArray[countInsert]->getC();
        destB = (gr->HashArray[gr->size-1]);
    //    cout<<"PRIN TIN FOR\n";
    //    cout<<node->getID();
        i = 0;
        while(i<num){
    //        cout<<"Stin for gia i =";
    //        cout<<i;
    //        cout<<"\n";
    //        cout<<startB->getC();
    //        if(countInsert == 19 || gr->size-1 == 19){
    //            cout<<"19"<<endl;
    //        }
            if (startB->getBuck()[i] != NULL){
    //            cout<<"\n KANW : ";
    //            cout<<startB->getBuck()[i]->getID();
    //            cout<<"%";
    //            cout<<(int)pow(2,(splitR + 1))*gr->m;
    //            cout<<"==";
    //            cout<<gr->size-1;
    //            cout<<"?";
                if(countInsert == 1){
                    printAll();
                }
                if (startB->getBuck()[i]->getID() % ((int)pow(2,(splitR + 1))*gr->m) == (gr->size-1)){
                    temp = startB->getBuck()[i];
                    startB->delNode(i);
                    i=i-1;
          //          startB->setCur(startB->getCur()-1);
                    if(destB->getCur() == destB->getC()){
                        gr->HashArray[size-1]->setBuck((Node**)realloc(gr->HashArray[size-1]->getBuck(),(gr->HashArray[size-1]->getC()+n)*sizeof(Node*)));
                        for(j=gr->HashArray[size-1]->getC();j<(gr->HashArray[size-1]->getC()+n);j++){
                            cout<<"Null gia "<<j<<endl;
                            gr->HashArray[size-1]->getBuck()[j] = NULL;
                        }
                        gr->HashArray[size-1]->setC(gr->HashArray[size-1]->getC()+n);
                    }
                    destB->setNode(temp);
          //          destB->setCur(destB->getCur()+1);
    //                cout<<"\n\nJUST copied ";
    //                cout<<temp->getID();
    //                cout<<"\n\n";
                }
                
            }
            i++;
        }
//        startB->Comp();
        //Desmeuei xwro 3 gia kathe neo kouva
        countInsert++;
        if(countInsert==(int)pow(2,splitR)*m){             //prin 2^2+splitR
            splitR++;
            countInsert=0;
            printAll();
            cout<<"ok edw"<<endl;
        }
    }
        
}

int Pinakas_katakermatismou::insertEdge(int id, Node* akm, Pinakas_katakermatismou* gr){
    Node* komv;
    Node* temp;
    Node* a;
    a = (Node*)malloc(sizeof(Node));
    a->setID(akm->getID());
    a->setNext(NULL);
    komv = lookupNode(id,gr);
    if(komv == NULL){
        cout<<"Node not found!\n";
        return -1;
    }
    if(komv->getNext() == NULL){
        akm->setNext(NULL);
        komv->setNext(a);
        return 1;
    //    cout<<"Inserted first edge with id = ";
    //    cout<<akm->getID();
    //    cout<<"\n";
    }
    else{
        //while(komv->getNext()!=NULL){
        //    komv = komv->getNext();
        //}
        temp = komv->getNext();
        komv->setNext(a); 
        komv->getNext()->setNext(temp);
//        temp = komv->getNext();
//        komv->setNext(akm);
//        akm->setNext(temp);
//        cout<<"Inserted edge with id = ";
//        cout<<akm->getID();
//        cout<<"\n";
//        if(id == 6){
//            temp = lookupNode(6,gr);
//            cout<<"\n\nFound 6 "<<endl;
//            while(temp->getNext()!=NULL){
//            cout<<temp->getNext()->getID()<<" ";
//            temp = temp->getNext();
//            }
//            cout<<"\nWs Edw\n\n"<<endl;
//        }
        return 1;
    }
    return -1;
}

Node* Pinakas_katakermatismou::lookupNode(int id, Pinakas_katakermatismou* gr){
    int k,i=0,power;
    Kouvas* buck;
    Node* n = NULL;
    power = (int)pow(2,(gr->splitR))*(gr->m);
    k = id % power;
    cout<<"Power is "<<power<<endl;
    buck = gr->HashArray[k];
    if(k >= countInsert){
        i=0;
//        while(buck->getBuck()[i] != NULL){
//        i++;
//        }
        cout<<k<<" "<<splitR<<" "<<i<<endl;
    //    cout<<"Searching for "<<id<<" in "<<k+(int)pow(2,(splitR))*m<<" till "<<HashArray[k]->getCur()<<endl;
        cout<<"Searching for "<<id<<" in "<<k<<endl;
        n=binary_search(buck,id,0,HashArray[k]->getC()-1);
        if (n != NULL){
    //        cout<<"Just found a node with id = ";
    //        cout<<n->getID();
    //        cout<<"\n";
            return n;
        }
        i=0;
    }
    else {
        buck = HashArray[k+(int)pow(2,(splitR))*m];
//        while(buck->getBuck()[i] != NULL){
//        i++;
//        }
        cout<<"Searching for "<<id<<" in "<<k+(int)pow(2,(splitR))*m<<" till "<<i-1<<endl;
        cout<<"Kai GetCur tou "<<k+(int)pow(2,(splitR))*m<<" = "<< HashArray[k+(int)pow(2,(splitR))*m]->getCur()<<endl;
        n = binary_search(buck,id,0,HashArray[k+(int)pow(2,(splitR))*m]->getC()-1);
        if (n == NULL){
        buck = HashArray[k];
        cout<<"Second Search "<<endl;
        n = binary_search(buck,id,0,HashArray[k]->getC()-1);
        }
        if (n != NULL){
            cout<<"Found in Buck "<<k<<endl;
    //          cout<<"Just found a node with id = ";
    //        cout<<n->getID();
    //        cout<<"\n";
            return n;
        }
        i=0;
    }
    return NULL;
}

Node* Pinakas_katakermatismou::binary_search(Kouvas* deiktis_kouva, int id, int min, int max){
    int mesos=min + (max-min)/2;
    int z;
    if (mesos > deiktis_kouva->getC()-1){
        max = deiktis_kouva->getC()-1;
        mesos = min + (max-min)/2;
    }
    
    if (min>max){
        cout<<"Den vrethike\n";
        return NULL;
    }
    if (deiktis_kouva->getBuck()[mesos] == NULL){
        return binary_search(deiktis_kouva,id,min,mesos-1);
    }
//    if(deiktis_kouva->getBuck()[mesos] == NULL){
//        cout<<"Den vrethike\n";
//        return NULL;
//    }
    if(deiktis_kouva->getBuck()[mesos]->getID() == id){
        cout<<"ID found!\n";
        z = deiktis_kouva->getBuck()[mesos]->getID();
        cout<<z;
        return deiktis_kouva->getBuck()[mesos];
    }
    else if(deiktis_kouva->getBuck()[mesos]->getID() > id){
        return binary_search(deiktis_kouva,id,min,mesos-1);
    }
    return binary_search(deiktis_kouva,id,mesos+1,max);
}

int Pinakas_katakermatismou::reachNode1(int ids, int idt, Pinakas_katakermatismou* gr){
    List visited,*temp;
    int min = 0;
//    int flag = ids;
    Node* child;
    List *goneas,*inserted;
    if ((lookupNode(ids,gr) == NULL) || (lookupNode(idt,gr) == NULL)){
        cout<<"Starting or finishing node can't be found!\n";
        return -1;
    }
    if (ids == idt){
        return 0;
    }
    visited.setID(ids);
    visited.setPar(NULL);
    visited.setNext(NULL);
//    goneas->setPar(NULL);
    while(ids != idt){
        child = lookupNode(ids,gr);
        if (child == NULL){
            cout<<"Can't locate node "<<ids<<endl;
            return -1;
        }
    //    cout<<"CHILD ID "<<child->getID()<<endl;
    //    cout<<"CHILD NEXT"<<child->getNext()->getID()<<endl;
        goneas = visited.search(&visited,ids);
    //    cout<<"Goneas Id: "<<goneas->getID()<<endl;
        while(child->getNext() != NULL){            //diatrexoume olous tous geitones
            if(child->getNext()->getID() == idt){
                inserted = visited.insert(&visited,child->getNext()->getID());
                (*inserted).setPar(goneas);
//                visited.print();
    //            cout<<"To inserted exei id: "<<inserted->getID()<<endl;
    //            cout<<"Kai parent id:"<<inserted->getPar(inserted)->getID()<<endl;
                while(inserted->getPar(inserted) != NULL){
                    min++;
                    inserted = inserted->getPar(inserted);
                }    //lathos
                return min;
            }
            if(visited.search(&visited,child->getNext()->getID()) == NULL){        //an den einai sto visited
                inserted = visited.insert(&visited,child->getNext()->getID());
                (*inserted).setPar(goneas);
//                visited.print();
            }
            child = child->getNext();
    //        cout<< "Child ID \n";
            cout << child->getID()<<endl;
//            cout<< child->getNext()->getID()<<endl;
        }
        temp = &visited;
        while(temp != NULL && temp->getID()!=ids){
            temp = temp->getNext();
        }
        if(temp != NULL && temp->getNext() != NULL){
            ids = temp->getNext()->getID();
    //        cout<<"IDS "<<ids<<endl;
        }
        else{
            cout<<"Nodes not connected"<<endl;
            return -1;
        }
    }
}


int Pinakas_katakermatismou::destroyGraph(Pinakas_katakermatismou* p){
    int i,j,c;
    Node ** Buc;
    for(i=0;i<(p->size);i++){
    Buc = ((p->HashArray[i])->getBuck());
    c = (p->HashArray[i])->getC();
    for(j=0;j<c;j++){
        if(Buc[j]!= NULL){
            free(Buc[j]);
        }     
    }
    free(Buc);
    free(HashArray[i]);
    }
}

void Pinakas_katakermatismou::printAll(){
    int i,j=0;
    for(i=0;i<this->size;i++){
        j = 0;
        cout<< "Kouvas ";
        cout<<i;
        cout<<"\n";
        cout<<"Kouvas size: ";
        cout<<HashArray[i]->getC();
        cout<<"\n";
        while (j<HashArray[i]->getC()){
            if (HashArray[i]->getBuck()[j] != NULL){
            cout<<HashArray[i]->getBuck()[j]->getID();}
            cout<<",";
            j++;
        }
        cout<<"\n";
    }
    
}

int Pinakas_katakermatismou::getSize(){
return this->size;}

Kouvas** Pinakas_katakermatismou::getHash(){
return this->HashArray;}

int Pinakas_katakermatismou::getTotal(){
    return this->total;
}

void Pinakas_katakermatismou::setTotal(int t){
    this->total = t;
}

ResultSet* Pinakas_katakermatismou::reachNodeN(int ids, Pinakas_katakermatismou* gr){
    ResultSet* rs;
    
    rs = (ResultSet*)malloc(sizeof(ResultSet));
    rs->tempi = -1;
    rs->next(ids,gr);
    return rs;
    
}

void ResultSet::next(int ids, Pinakas_katakermatismou* gr){
    int i=0;
    if(this->tempi == -1){
        while(gr->getHash()[i]->getCur() == 0){
            i++;    //Vriskoume prwti gemati thesi
        }
        tempi = i;
        tempj = 0;
        this->id = gr->getHash()[tempi]->getBuck()[tempj]->getID();
        this->dist = gr->reachNode1(ids,this->id,gr);
    }
    else{
        if((gr->getHash()[tempi]->getCur() - 1 > tempj + 1) && (tempi == gr->getSize()-1)){
            //this->tempi = -1;
        }
        if(gr->getHash()[tempi]->getCur() - 1 > tempj + 1){
            while(gr->getHash()[tempi]->getCur() == 0){
                tempi++;
            }
            tempj = 0;
            this->id = gr->getHash()[tempi]->getBuck()[tempj]->getID();
            this->dist = gr->reachNode1(ids,this->id,gr);
        }
        else{
            tempj++;
            this->id = gr->getHash()[tempi]->getBuck()[tempj]->getID();
            this->dist = gr->reachNode1(ids,this->id,gr);
        }
    }
}

/*int ResultSet::setID_dist(int ida, int dista){
    this->id = ida;
    this->dist = dista;
    return 1;
}
    
int ResultSet::setNext(ResultSet* r){
    this->next = r;
    return 1;
}

ResultSet* ResultSet::getNext(){
    return this->next;
}
 */

int LOL::length(LOL*l){
    int counter = 1;
    if(l == NULL){
        return -1;
    }
    while(l->next != NULL){
        counter++;
        l = l->next;
    }
    return counter;
}

Attr** createProperties(int number) {
    	Attr** at;
	int i;
	at = (Attr**)malloc(number*sizeof(Attr));
	for(i=0;i<number;i++){
		at[i]=NULL;	
	}
    return at;
}

void setStringProperty(char const* property, int index, Attr** p) {
        strA* str;
	string s(property);
	str = new strA;
	str->value = s;
	str->next = NULL;
	str->name = -1;		//arxikopoihsh
	p[index] = str;	
}

void setIntegerProperty(int property, int index, Attr** p) {
    	intA* intp;
	intp = new intA;
	intp->value = property;
	p[index] = intp;
}

int Stack::push(int i){         //Kratame tin korufh kai pame pros ta katw
    Snode* nod = (Snode*) malloc(sizeof(Snode));
    Snode* temp;
    nod->id = i;
    if(this->first == NULL){
        nod->next = NULL;
        this->first = nod;
    }
    else{
        temp = first->next;
        first = nod;
        nod->next = temp;
    }
};

int Stack::pop(){
    Snode* temp;
    int idt;
    if (this->first != NULL){
        temp = first->next;
        idt = first->id;
        free(first);
        first = temp;
        return idt;
    }
    else{
        cout<<"Nothing to pop!"<<endl;
    }
}

int Stack::empty(){
    if (this->first == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int Queue::enq(int i){
    Snode* nod = (Snode*) malloc(sizeof(Snode));
    nod->id = i;
    if(this->first == NULL){
        nod->next = NULL;
        this->first = nod;
        this->last = nod;
    }
    else{
        nod->next = NULL;
        this->last->next = nod;
        this->last = nod;
    }
}

/*int Queue::deq(){
    Snode* temp;
    int id;
    if(this->first != NULL){
        temp = this->first;
        if(temp->next == NULL){
            id = this->first->id;
            free(this->first);
            this->first = NULL;
            this->last = NULL;
            return id;
        }
        while(temp->next != NULL){
            if(temp->next->next == NULL){
                id = this->last;
                free(this->last);
                this->last = temp;
                this->last->next = NULL;
            }
            else{
                temp = temp->next;
            }
        }
        return id;
    }
}
*/
int Queue::empty(){
    if(this->first == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

/*double betweennessCentrality(Node* n, Pinakas_katakermatismou* g){
    double* cb;
    Stack S;
    List P;
    int* sig;
    int* d;
    int* del;
    int* dict;
    Queue Q;
    int i,c=0,l=0,v;
    Node* n,edge;
    
    P.setID(-1);        //arxikopoihsh
    P.setNext(NULL);
    P.setPar(NULL);
    S.first = NULL;
    Q.first = NULL;
    Q.last = NULL;
    cb = (double*)malloc(g->getTotal()*sizeof(double));
    sig = (int*)malloc(g->getTotal()*sizeof(int));
    d = (int*)malloc(g->getTotal()*sizeof(int));
    del = (int*)malloc(g->getTotal()*sizeof(int));
    dict = (int*)malloc(g->getTotal()*sizeof(int));
    
    for(i=0;i<g->getTotal();i++){       //arxikopoihsh dict
        cb[i] = 0;                      // kai cb
        if(g->getHash()[l]->getBuck()[c] == NULL){
            l++;
            while(g->getHash()[l]->getBuck()[c] == NULL){
                l++;
            }
            c=0;
        }
        dict[i] = g->getHash()[l]->getBuck()[c]->getID();
        c++;
    }
    for(i=0;i<g->getTotal();i++){       //Gia kathe komvo
        Q.enq(dict[i]);
        while(Q.empty() != 1){     //while Q not empty
            v = Q.deq();
            S.push(v);
            n = g->lookupNode(v,g);
            for(l=0;l<g->getTotal();l++){
                if(dict[l] == n->getID()){
                    break;
                }
            }
            edge = n->getNext();
            while(edge != NULL){    //for each neighbor
                for(c=0;c<g->getTotal();c++){
                    if(dict[c] == edge->getID()){
                        break;
                    }
                }
                if(d[c] < 0){
                    Q.enq(edge->getID());
                    d[c] = d[l] + 1;
                }
                if(d[c] == (d[l] + 1)){
                    sig[c] = sig[c] + sig[l];
                    P.insert(&P,n->getID());
                }
            }
        }
        for(i=0;i<g->getTotal();i++){
            del[i] = 0;
        }
        while(S.empty() == 0){
            c = S.pop();
        }
    }
}

 */
//Find Top Forums 

void* countF(void* dat){
    long int idp,idc,countAp,i,min;
    long int idint;
    string temp;
    string conv;
    string fname;
    string ids;
    string idstring;
    ifstream fornam;
    ifstream formem;
    int line = 0;
    long int ins = 0;
    ifstream f("forum.csv");
    Tdata* tdat;
    Forum* tempf;
    tdat = (Tdata*)dat;
    tempf = new Forum;
    idp = -1;
    
    while(line < tdat->startl && getline(f,temp)){
        line++;
        if(tdat->startl == 1){
        cout<<temp<<endl;
        }
    }
    while(line <= tdat->endl && getline(f,temp)){
        if(tdat->startl == 1){
        cout<<temp<<endl;
        }
        pthread_mutex_lock(tdat->cblc);
        (*tdat->count)++;
        pthread_mutex_unlock(tdat->cblc);
        cout<<*(tdat->count)<<endl;
        line++;
        formem.open("forum_hasMember_person.csv");
        istringstream t(temp);
        getline(t,conv,'|');
        idp = atoi(conv.c_str());
        getline(t,fname,'|');
        cout<<fname<<endl;
        countAp = 0;
        while(getline(formem,temp)){
            istringstream tid(temp);
            getline(tid,conv,'|');
            idc = atoi(conv.c_str());
            if(idp == idc){
                countAp++;
            }
        }
        formem.close();
//        cout<<"CountAp for "<<fname<<" is "<<countAp<<endl;
        pthread_mutex_lock(tdat->lock);
        if(*(tdat->flag) < tdat->n){     //den exei gemisei o pin
            (tdat->arr[*(tdat->flag)]).name = fname;
            tdat->arr[*(tdat->flag)].size = countAp;
            (*tdat->flag)++;
        }
        else{
            min = 0;
            for(i=0;i<tdat->n;i++){
                if(tdat->arr[i].size < tdat->arr[min].size){
                    min = i;
                }
            }
            if(tdat->arr[min].size < countAp){
                tdat->arr[min].name = fname;
                tdat->arr[min].size = countAp;
//                cout<<"ID "<<idc<<" plithos "<<countAp<<endl;
            }
        }
        pthread_mutex_unlock(tdat->lock);
    }
    free(tdat);
}

Forum* findTopN(Pinakas_katakermatismou* gr,int N){
    Forum* idPin;
    int fl=0;
    int base,i,frag;
    int gram=1;
    int c = 0;
    Tdata* data;
    string fnam;
    pthread_t thr;
    string temp;
    string conv;
    int thrC = 0;
    ListTh* first;
    int thrno = 4;
    int coun = 0;
    pthread_mutex_t mut;
    pthread_mutex_t cmut;
    
    ifstream forums("forum.csv");
    idPin = new Forum[N];
    base = 1;
    pthread_mutex_init(&mut,NULL);
    pthread_mutex_init(&cmut,NULL);
    first = (ListTh*)malloc(sizeof(ListTh));
    first->next = NULL;
    first->thread = NULL;
    
    getline(forums,temp); //prwth grammh
    while(getline(forums,temp)){
//        cout<<temp<<endl;
        gram++;
    }
    frag = gram/thrno;
    cout<<"Grammes "<<gram<<endl;
//    while(getline(forums,temp)){
//        istringstream t(temp);
//        getline(t,conv,'|');
//        getline(t,fnam,'|');
//        cout<<"Forum name "<<fnam<<endl;
    for(i=0;i<thrno;i++){           //thrno threads
        data = new Tdata;
        data->n = N;
        data->arr = idPin;
        data->flag = &fl;
        data->lock = &mut;
        data->startl = base;
        data->count = &coun;
        if(i<thrno-1){
            data->endl = base + frag;
        }
        else if(i == (thrno-1)){
            data->endl = gram;
        }
        cout<<"From "<<data->startl<<" Till "<<data->endl<<endl;
        data->count = &c;
        data->cblc = &cmut;
        pthread_create(&thr,0,countF,(void*)data);
        first = first->add(&thr);
        base = base + frag + 1;
    }
    
    
//    while((*data->count)!=0){}       //perimenoume na teleiwsoun ta thread
    while(first->next != NULL){
        pthread_join(*(first->thread),NULL);
        first = first->next;
    }
    return data->arr;
}

ListTh* ListTh::add(pthread_t* th){
    ListTh* lth;
    lth = (ListTh*)malloc(sizeof(ListTh));
    lth->thread = th;
    lth->next = this;
    return lth;
}

Pinakas_katakermatismou** createForums(Pinakas_katakermatismou* gr,int N,Forum** pin){
    Pinakas_katakermatismou** forums;
    int i;
    pthread_t thr;
    ListTh* first;
    forData* dt;
    
    first = (ListTh*)malloc(sizeof(ListTh));
    first->next = NULL;
    first->thread = NULL;
    forums = (Pinakas_katakermatismou**)malloc(N*sizeof(Pinakas_katakermatismou*));
    for(i=0;i<N;i++){
        forums[i] = new Pinakas_katakermatismou;
        forums[i]->createGraph(4,3);
    }
    for(i=0;i<N;i++){           //gia kathe forum
        dt = (forData*)malloc(sizeof(forData));
        dt->fr = pin;
        dt->gr = gr;
        dt->graphs = forums;
        dt->thesi = i;
        pthread_create(&thr,0,makeF,(void*)dt);
        first = first->add(&thr);
    }
    while(first->next != NULL){
        pthread_join(*(first->thread),NULL);
        first = first->next;
    }
    return forums;
}

void* makeF(void* dt){
    forData* data;
    ifstream fhm;
    ifstream fornam,members;
    string names,idstring;
    Node* node;
    Node* alpha;
    Node* akm;
    Node* kappa;
    int id,idm;
    int i,j,m,n;
    
    data = (forData*)dt;
    fornam.open("forum.csv");       //euresi id apo name
    getline(fornam,names);           //prwti grammi 
    while(getline(fornam,names)){    //perasma sta id kai name
        istringstream nm(names);
        getline(nm,idstring,'|');
        getline(nm,names,'|');
        if(names == data->fr[data->thesi]->name){
            id = atoi(idstring.c_str());
        }
    }
    fornam.close();
    members.open("forum_hasMember_person.csv");
    getline(members,idstring);      //prwti grammi
    while(getline(members,idstring)){   //gia kathe melos tou forum
        istringstream nm(idstring);
        getline(nm,idstring,'|');
        idm = atoi(idstring.c_str());
        if(id == idm){
            node = new Node;
            getline(nm,idstring,'|');
            idm = atoi(idstring.c_str());
            cout<<"\nIDM "<<idm<<endl;
            if(data->graphs[data->thesi]->lookupNode(idm,data->graphs[data->thesi]) == NULL){
            node->setID(idm);
            node->setNext(NULL);
            data->graphs[data->thesi]->insertNode(node,data->graphs[data->thesi]);
//            node = data->graphs[data->thesi]->lookupNode(idm,data->graphs[data->thesi]);
            }
        }
    }
    members.close();    
//    getchar();
//    data->graphs[data->thesi]->printAll();
    m = data->graphs[data->thesi]->getSize();   //gia kathe komvo katharise geitones
    for(i=0;i<m;i++){
        n = data->graphs[data->thesi]->getHash()[i]->getCur();
        for(j=0;j<n;j++){
            node = data->graphs[data->thesi]->getHash()[i]->getBuck()[j];
            if(node->getID() == 3568){
            cout<<"ID "<<node->getID()<<endl;
            }
            alpha = data->gr->lookupNode(node->getID(),data->gr);
            while(alpha->getNext() != NULL){
                alpha = alpha->getNext();
                akm = new Node;
                akm->setID(alpha->getID());
                if(data->graphs[data->thesi]->lookupNode(akm->getID(),data->graphs[data->thesi]) != NULL){
                if(node->getID() == 3568){
                    cout<<"Inserting "<<akm->getID()<<endl;
                    cout<<endl;
                }
                data->graphs[data->thesi]->insertEdge(node->getID(),akm,data->graphs[data->thesi]);
                }
                free(akm);
            }
        
        }
    }
    alpha = data->graphs[data->thesi]->lookupNode(3568,data->graphs[data->thesi]);
    while(alpha->getNext() != NULL){
        cout<<alpha->getNext()->getID()<<endl;
        alpha = alpha->getNext();
    }
}

int Clicks(Pinakas_katakermatismou *gr,
        int *arithmos_anadromis,
        int *stoixio, 
        int *clickid,
        int megethos_click,
        int *clickarray,
        Click **click,
        Node *arxikoNode){   //to fo einai to gr tis domis, to stoixeio einai to stoixio t pinaka clickarray sto opoio exoume
                                     //minei stin arxi einai 0
    Click *tmpc1;
    Click *tmpc2;
    Node *forumNode;
    Node *arxikoforumNode;
    Node *nlg;
    Node *nextnode;
    int countmeloi, i, telos, j, flag, w, z, br;
    
    cout<<"hmaste stin anadromi : "<< *arithmos_anadromis <<endl;
    cout<<"stoixio :"<<*stoixio<<endl;
    if(*arithmos_anadromis == 0){
        for(w=0;w<gr->getSize();w++){
            if(gr->getHash()[w] != NULL){
                for(z=0;z<gr->getHash()[w]->getCur();z++){
                    forumNode = gr->getHash()[w]->getBuck()[z];
                    if(forumNode !=NULL){ //einai o prwtos komvos

                        cout<<"psaxnoume 3-clikes"<<endl;
                        //getchar();
                        arxikoNode = forumNode;
                        nextnode = forumNode;

                        while( nextnode !=NULL){
                            cout<<"periexomeno tou nextnode einai "<<nextnode->getID()<< endl;      
                            clickarray[*stoixio] = nextnode->getID();
                    //        for(i =0; i<*stoixio; i++){
                    //            if(clickarray[*stoixio] == clickarray[i]){
                    //                nextnode=nextnode->getNext();
                    //                if(nextnode!=NULL){
                    //                    clickarray[*stoixio] = nextnode->getID();
                    //                }
                    //                else{
                    //                    return 1;
                    //                }
                    //            }
                    //        }
                    //        if(*stoixio == 0){
                    //           i = Clicks(fo,(arithmos_anadromis+1),forumID, 
                    //                   (stoixio+1), 
                    //                   clickid, 
                    //                   megethos_click,
                    //                   clickarray);
                    //        }
                            flag = 0;
                            if(*stoixio != 0){ //vlepoume an ena stoixio vriskete idi mesa
                                for(i =0; i<*stoixio; i++){
                                    if(nextnode->getID() == clickarray[i]){
                                        flag = 1;
                                    }
                                }
                            }
                            for(i=0; i<(megethos_click); i++){
                                cout<<i<<" stoixio tou pinaka"<<clickarray[i]<<endl;
                            }
                            if(flag == 0){
                                nlg = gr->lookupNode(nextnode->getID(), gr);
                                cout<<"o nlg exei mesa periexomeno"<<nlg->getID()<<endl;
                                telos = 0;
                                while(nlg!=NULL){
                                    cout<<"epomeno nlg einai:"<<nlg->getID()<<endl;
                                    for(j=0; j<*stoixio; j++){
                                        if((nlg->getID() == clickarray[j]) /*&&(nlg->getID() != clickarray[1])*/){
                                            telos = telos +1;
                                        } 
                                    }
                                    nlg= nlg->getNext();
                                }
                                cout<<"telos einai: "<<telos<<endl;
                                if((telos == *arithmos_anadromis) || (*stoixio == 0)){
                                     //clickarray[*stoixio] = nlg->getID();
                                     telos =0;
                                     if((*arithmos_anadromis) < (megethos_click-1)){
                                        //kalese anadromi
                                         cout<<"kaloume anadromika tin synartisi"<<endl;
                                         *stoixio = *stoixio+1;
                                         *arithmos_anadromis=*arithmos_anadromis+1;
                                         i = Clicks(gr,
                                                 arithmos_anadromis,
                                                 stoixio, 
                                                 clickid, 
                                                 megethos_click,
                                                 clickarray,
                                                 click,
                                                 arxikoNode);
                                        *stoixio = *stoixio-1;
                                        *arithmos_anadromis=*arithmos_anadromis-1;
                                     }
                                     else/*if((*arithmos_anadromis) == (megethos_click-1))*/{
                                         //vrikame clicka
                                         cout<<"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvrikame clicka!"<<endl;
                                         *clickid = *clickid+1;
                                         br = 0;
                                        if((*click) == NULL){
                                            (*click)=(Click *)malloc(sizeof(Click));
                                            (*click)->id = *clickid;
                                            for(j =0; j<=*stoixio; j++){
                                                (*click)->array[j] = clickarray[j]; 
                                            }
                                            (*click)->next = NULL;
                                        }
                                        else{
                                            tmpc1 = (*click);
                                            while(tmpc1->next !=NULL){
                                                if((tmpc1->array[1] == clickarray[2]) ||(tmpc1->array[2] == clickarray[1])){
                                                br = br+1;
                                                }
                                                if((tmpc1->array[2] == clickarray[3]) || (tmpc1->array[3] == clickarray[2])){
                                                    br=br+1;
                                                }
                                                if((tmpc1->array[1] == clickarray[3]) || (tmpc1->array[3] == clickarray[1])){
                                                    br = br+1;
                                                }
                                                tmpc1=tmpc1->next;
                                            }

                                            if(br >= 3){
                                                *clickid = *clickid-1;
                                            }
                                            if(br<3){
                                                tmpc2 = tmpc1->next;
                                                tmpc1->next = (Click *) malloc(sizeof(Click));
                                                tmpc1->next->id = *clickid;
                                                for(j =0; j<=*stoixio; j++){
                                                    tmpc1->next->array[j] = clickarray[j]; 
                                                }
                                                tmpc1->next->next = NULL;
                                            }
                                        }

                                    }
                                }
                        //        else{
                        //            return 1;
                        //        } 
                            }
                            cout<<"pame sto epomeno komvo-melos, hmaste stin anadromi: "<< *arithmos_anadromis<< endl;
                            clickarray[*stoixio] = 0;
                            nextnode = nextnode->getNext();
                        }
                    }
                }
            }
        }
    }
    else{ //an den vriskomaste stin 1i anadromi tha elenxoume tous geitones mono tou 1ou
        nextnode = arxikoNode;
        
        while( nextnode !=NULL){
            cout<<"periexomeno tou nextnode einai "<<nextnode->getID()<< endl;      
            clickarray[*stoixio] = nextnode->getID();
    //        for(i =0; i<*stoixio; i++){
    //            if(clickarray[*stoixio] == clickarray[i]){
    //                nextnode=nextnode->getNext();
    //                if(nextnode!=NULL){
    //                    clickarray[*stoixio] = nextnode->getID();
    //                }
    //                else{
    //                    return 1;
    //                }
    //            }
    //        }
    //        if(*stoixio == 0){
    //           i = Clicks(fo,(arithmos_anadromis+1),forumID, 
    //                   (stoixio+1), 
    //                   clickid, 
    //                   megethos_click,
    //                   clickarray);
    //        }
            flag = 0;
            if(*stoixio != 0){ //vlepoume an ena stoixio vriskete idi mesa
                for(i =0; i<*stoixio; i++){
                    if(nextnode->getID() == clickarray[i]){
                        flag = 1;
                    }
                }
            }
            for(i=0; i<(megethos_click); i++){
                cout<<i<<" stoixio tou pinaka"<<clickarray[i]<<endl;
            }
            if(flag == 0){
                nlg = gr->lookupNode(nextnode->getID(), gr);
                cout<<"o nlg exei mesa periexomeno"<<nlg->getID()<<endl;
                telos = 0;
                while(nlg!=NULL){
                    cout<<"epomeno nlg einai:"<<nlg->getID()<<endl;
                    for(j=0; j<*stoixio; j++){
                        if((nlg->getID() == clickarray[j]) /*&&(nlg->getID() != clickarray[1])*/){
                            telos = telos +1;
                        } 
                    }
                    nlg= nlg->getNext();
                }
                cout<<"telos einai: "<<telos<<endl;
                if((telos == *arithmos_anadromis) || (*stoixio == 0)){
                     //clickarray[*stoixio] = nlg->getID();
                     telos =0;
                     if((*arithmos_anadromis) < (megethos_click-1)){
                        //kalese anadromi
                         cout<<"kaloume anadromika tin synartisi"<<endl;
                         *stoixio = *stoixio+1;
                         *arithmos_anadromis=*arithmos_anadromis+1;
                         i = Clicks(gr,
                                 arithmos_anadromis,
                                 stoixio, 
                                 clickid, 
                                 megethos_click,
                                 clickarray,
                                 click,
                                 arxikoNode);
                        *stoixio = *stoixio-1;
                        *arithmos_anadromis=*arithmos_anadromis-1;
                     }
                     else/*if((*arithmos_anadromis) == (megethos_click-1))*/{
                         //vrikame clicka
                         cout<<"vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvrikame clicka!"<<endl;
                         *clickid = *clickid + 1;
                         br = 0;
                        if((*click) == NULL){
                            (*click)=(Click *)malloc(sizeof(Click));
                            (*click)->id = *clickid;
                            (*click)->akmi = 0; //oles oi akmes metaxi twn yperkomvwn arxikopoioude me 0
                            for(j =0; j<=*stoixio; j++){
                                (*click)->array[j] = clickarray[j]; 
                            }
                            (*click)->next = NULL;
                        }
                        else{
                            tmpc1 = (*click);
                            while(tmpc1->next !=NULL){
                                if((tmpc1->array[1] == clickarray[2]) ||(tmpc1->array[2] == clickarray[1])){
                                br = br+1;
                                }
                                if((tmpc1->array[2] == clickarray[3]) || (tmpc1->array[3] == clickarray[2])){
                                    br=br+1;
                                }
                                if((tmpc1->array[1] == clickarray[3]) || (tmpc1->array[3] == clickarray[1])){
                                    br = br+1;
                                }
                                tmpc1=tmpc1->next;
                            }
                            
                            if(br >= 3){
                                *clickid = *clickid-1;
                            }
                            if(br <3){
                                tmpc2 = tmpc1->next;
                                tmpc1->next = (Click *) malloc(sizeof(Click));
                                tmpc1->next->id = *clickid;
                                (*click)->akmi = 0; //oles oi akmes metaxi twn yperkomvwn arxikopoioude me 0
                                for(j =0; j<=*stoixio; j++){
                                    tmpc1->next->array[j] = clickarray[j]; 
                                }
                                tmpc1->next->next = NULL;
                            }
                        }

                    }
                }
        //        else{
        //            return 1;
        //        } 
            }
            cout<<"pame sto epomeno komvo-melos, hmaste stin anadromi: "<< *arithmos_anadromis<< endl;
            clickarray[*stoixio] = 0;
            nextnode = nextnode->getNext();
        }
        
    }
}

int ClickinsertEdge(Click **click, int megethos){
    
    Click *tmpc;
    Click *prwtos;
    Click *deyteros;
    int i, z, koina, synexia;
    
    tmpc= (*click);
    while (tmpc !=NULL){ //mia akmi //einai 1 an 2 komvoi clickas exoun koina k-1 koinous komvous
        koina = 0;
        synexia = 0;
        prwtos = tmpc;
        deyteros = tmpc->next;
        if(deyteros !=NULL){
            synexia = 1;
        }
        //pame na syggrinoume to kathe stoixio tou prwtou me to kathe stoixio tou deyterou
        if(synexia == 1){
            for(i=0; i<megethos; i++){
                for(z=0; z<megethos; z++){
                    if(prwtos->array[i] == deyteros->array[z]){
                        koina = koina + 1;
                    }
                }
            }
            if(koina == (megethos -1)){
                tmpc->akmi = 1;
            }
        }
        tmpc= tmpc->next;
    }
    return 1;
}

int Clicksprint(Click *click, int megethos){

    Click *tmpc;
    int j,neo_comm;
    
    tmpc = click;
    neo_comm =0;
    while (tmpc->next !=NULL){
        if(neo_comm==1){
            cout<<"Neo community"<<endl;
            neo_comm=0;
        }
        cout<<"clicka"<<endl;
        cout<<"click ID :"<<tmpc->id<<endl;
        cout<<"click akmi :"<<tmpc->akmi<<endl;
        if(tmpc->akmi ==0){
            neo_comm = 1;
        }
        for(j =0; j<megethos; j++){           
            cout<<tmpc->array[j]<<","<<endl;
        }
        tmpc=tmpc->next;
    }
    return 1;
}