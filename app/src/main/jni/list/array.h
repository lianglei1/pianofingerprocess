//
// Created by 77915 on 2019/7/1.
//

#include "../Log/Log.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef FINGERPIANO_ARRAY_H
#define FINGERPIANO_ARRAY_H
typedef int elemTypeArray;//定义存入的数据的类型可以是int char

typedef struct ANODE { //定义链表的结构类型
    elemTypeArray element;
    struct ANODE *next;
} ANode;

#endif //FINGERPIANO_ARRAY_H

void initArray(ANode **pANode);

ANode *creatArray(ANode *pHead, elemTypeArray element);

void printArray(ANode *pHead);

void clearArray(ANode *pHead);

int sizeArray(ANode *pHead);

int isEmptyArray(ANode *pHead);

elemTypeArray getElementArray(ANode *pHead, int pos);

elemTypeArray *getElemArrayAddr(ANode *pHead, elemTypeArray x);

int modifyElemArray(ANode *pANode, int pos, elemTypeArray x);

int insertHeadArray(ANode **pANode, elemTypeArray insertElem);

int insertLastArray(ANode *pANode, elemTypeArray insertElem);

int isAddPosArray(ANode *pANode, int pos, elemTypeArray x);

int OrrderArray(ANode *pANode, elemTypeArray x);

int DelHeadArray(ANode **pList);

int DelLastArray(ANode *pANode);

int DelPosArray(ANode *pANode, int pos);

int DelxArray(ANode **pANode, int x);

int exchange2posArray(ANode *pANode, int pos1, int pos2);

int ArrangeArray(ANode *pANode);

extern elemTypeArray *listToIntArray(ANode *pHead);