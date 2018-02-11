/* 
 * File:   Tree_list.h
 * Author: adminuser
 *
 * Created on March 5, 2015, 9:22 AM
 */

#ifndef TREE_LIST_H
#define	TREE_LIST_H

using namespace std;

class Tree_list{
public:
    const char *word;
    Tree_list *next;
    Tree_list *parent;
};

void Tree_creation(Tree_list **);
int Tree_empty(Tree_list **);
int Tree_insert(Tree_list **, const char *, Tree_list *, int , int *,int *, int , int , int *, int *, Tree_list **);
void Tree_Destroy(Tree_list **);
void Tree_print(Tree_list *);
#endif	/* TREE_LIST_H */