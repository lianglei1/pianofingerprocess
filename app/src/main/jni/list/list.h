//
// Created by lianlgei on 2019/6/27.
//


#include "../Log/Log.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef FINGERPIANO_LIST_H

#define FINGERPIANO_LIST_H
typedef int *elemType;//定义存入的数据的类型可以是int char

typedef struct NODE { //定义链表的结构类型
    elemType element;
    int key;
    struct NODE *next;
} Node;

#endif //FINGERPIANO_LIST_H



void initList(Node **pNode);

Node *creatList(Node *pHead, elemType element);
Node *creatListWithKey(Node *pHead, elemType element,int key);

void printList(Node *pHead);

void clearList(Node *pHead);

int sizeList(Node *pHead);

int isEmptyList(Node *pHead);

elemType getElement(Node *pHead, int pos);
int getElementKey(Node *pHead, int pos);

elemType *getElemAddr(Node *pHead, elemType x);

int modifyElem(Node *pNode, int pos, elemType x);

int insertHeadList(Node **pNode, elemType insertElem);

int insertLastList(Node *pNode, elemType insertElem);


int insertLastListWithKey(Node *pNode, elemType insertElem,int key);

int isAddPos(Node *pNode, int pos, elemType x);

int OrrderList(Node *pNode, elemType x);

int DelHeadList(Node **pList);

int DelLastList(Node *pNode);

int DelPos(Node *pNode, int pos);

int Delx(Node **pNode, int x);

int ArrangeList(Node *pANode);


elemType * dimenslistToIntArray(Node *pHead);