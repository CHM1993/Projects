/* 
 * File:   HashTable.h
 * Author: george
 *
 * Created on October 28, 2014, 12:23 PM
 */


#ifndef HASHTABLE_H
#define	HASHTABLE_H
#include <string>

using namespace std;


class Matches{
public:
    int id;
    double score; //Jaccard
};

class List_of_Matches{
public:
    Matches M;
    List_of_Matches *next;
};

class Attr{
public:
    int name;               //Kathe xaraktiristiko exei sugkekrimeno arithmo
    Attr* next;
};

class intA: public Attr{
public:
    int value;
};

class strA: public Attr{
public:
    string value;
};

class ListA: public Attr{
public:
    Attr* head;
};

class List;

class Snode{            //stack node
public:
    int id;
    Snode* next;
};

class Stack{
public:
    Snode* first;
    int push(int);
    int pop();
    int empty();
};

class LOL{              //list of lists
public:
    List* head;
    LOL* next;
    int length(LOL*);
};

class Queue{
public:
    Snode* first;
    Snode* last;
    int enq(int);
    int deq();
    int empty();
};

class List{
    int id;
    List* par;          //parent 
    List* next; 
public:
    int setID(int);
    int getID();
    int setPar(List*);
    List* getPar(List*);
    List* getNext();
    void print();
    int length(List*);
    int setNext(List*);
    List* insert(List*,int);
    List* search(List*,int);
};

class Node{
    int id;
    Node* next;
public:
    Attr** prop;
    int getID();
    Attr* getAt();
    void setAt(Attr*);
    void setID(int);
    int setNext(Node*);
    Node* getNext();
};

class Kouvas{
    int c;
    int cur;
    Node** Buck;
  public:
    int     setNode(Node*);
    int     delNode(int);
    int     getC();
    int     setC(int);
    int     setBuck(Node**);
    int     getCur();
    int     Comp();
    void    setCur(int);
    Node**  getBuck();
};

class Pinakas_katakermatismou;

class ResultSet{
public:
    int id;
    int dist;
    int tempi;
    int tempj;
    void next(int,Pinakas_katakermatismou*);
};

class Pinakas_katakermatismou{
    Kouvas** HashArray;
    int countInsert;
    int size;
    int m;
    int n;
    int splitR;
    int total;
    int off;
  public:
    Pinakas_katakermatismou* createGraph(int m, int c); // m megethos pinaka katakermatismou kai c to plithos keliwn  
    int    destroyGraph(Pinakas_katakermatismou* p);    // pointer ston pinaka katakermatismou
    int    insertNode(Node* node, Pinakas_katakermatismou* gr);
    int    getSize();
    Node*    binary_search(Kouvas*,int,int,int);
    Kouvas**    getHash();
    int    getTotal();
    void   setTotal(int);
    int    insertEdge(int,Node*,Pinakas_katakermatismou*);
    Node*  lookupNode(int id, Pinakas_katakermatismou* gr);
    int    reachNode1(int ids, int idt, Pinakas_katakermatismou* gr);
    void   printAll();
    ResultSet* reachNodeN(int ids, Pinakas_katakermatismou* gr);
};

class Forum{
public:
    int size;
    string name;
};


class Tdata{
public:
    int* flag;
    Forum* arr;
    int startl;             //arxikh grammi
    int endl;               //telikh grammi 
    int n;
    int* count;             //metraei posa thread trexoun
    pthread_mutex_t* cblc;    //mutex gia to count
    pthread_mutex_t* lock;  //mutex gia ton arr
};

class ListTh{
public:
    pthread_t* thread;
    ListTh* next;
    ListTh* add(pthread_t*);
};

class forData{
public:
    Forum** fr;                          //TopN Forums
    Pinakas_katakermatismou* gr;        //arxiko hash
    Pinakas_katakermatismou** graphs;   //pinakas grafwn 
    int thesi;                          // thesi pinaka
};

class Click{
public:
    int id;
    int array[3];
    int akmi; //einai 1 an 2 komvoi clickas exoun koina k-1 koinous komvous
    Click *next;
};

//class Communities{
//public:
//    int comm_id;
//    int comm_array[200];
//    Communities *next_com;
//};


void* makeF(void*);
Pinakas_katakermatismou** createForums(Pinakas_katakermatismou*,int,Forum**);
void* countF(void*);
Forum* findTopN(Pinakas_katakermatismou*,int);
Attr** createProperties(int);
int Clicks(Pinakas_katakermatismou* ,int*, int*, int*,int ,int *, Click **,Node *);
int ClickinsertEdge(Click **, int);
int Clicksprint(Click *, int);
void setStringProperty(char const*, int, Attr**);
void setIntegerProperty(int, int, Attr**);
void degreeDistribution(Pinakas_katakermatismou*);
int  diameter(Pinakas_katakermatismou*);
int  averagePath(Pinakas_katakermatismou*);
int  CCnumber(Pinakas_katakermatismou*);
List* BFS(int,Pinakas_katakermatismou*);
Matches *matchSuggestion (Node*,int,int,int,int,Pinakas_katakermatismou*);

#endif	/* HASHTABLE_H */
