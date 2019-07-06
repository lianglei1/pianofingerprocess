//
// Created by 77915 on 2019/7/3.
//

#include "list.h"

#ifndef FINGERPIANO_DICTIONARY_H
#define FINGERPIANO_DICTIONARY_H

typedef Node *elemTypeDic;//定义存入的数据的类型可以是int char

typedef struct DICNODE { //定义链表的结构类型
    elemTypeDic element;
    int key;
    struct DICNODE *next;
} DicNode;
#endif //FINGERPIANO_LIST_H



void initDic(DicNode **pDicNode);

DicNode *creatDic(DicNode *pHead, elemTypeDic element);
DicNode *creatDicWithKey(DicNode *pHead, elemTypeDic element,int key);

void printDic(DicNode *pHead);

void clearDic(DicNode *pHead);

int sizeDic(DicNode *pHead);

int isEmptyDic(DicNode *pHead);

elemTypeDic getElementDic(DicNode *pHead, int pos);
int getElementKeyDic(DicNode *pHead, int pos);

elemTypeDic *getElemAddrDic(DicNode *pHead, elemTypeDic x);

int modifyElemDic(DicNode *pDicNode, int pos, elemTypeDic x);

int insertHeadDic(DicNode **pDicNode, elemTypeDic insertElem);

int insertLastDic(DicNode *pDicNode, elemTypeDic insertElem);


int insertLastDicWithKey(DicNode *pDicNode, elemTypeDic insertElem,int key);

int isAddPosDic(DicNode *pDicNode, int pos, elemTypeDic x);

int OrrderDic(DicNode *pDicNode, elemTypeDic x);

int DelHeadDic(DicNode **pDic);

int DelLastDic(DicNode *pDicNode);

int DelPosDic(DicNode *pDicNode, int pos);

int DelxDic(DicNode **pDicNode, int x);

int ArrangeDic(DicNode *pADicNode,int flag);


elemType * dimenslistToIntArrayDic(DicNode *pHead);