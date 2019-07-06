//
// Created by mac on 2017/10/30.
//

#ifndef FINGERPIANO_CALMAIN_H
#define FINGERPIANO_CALMAIN_H


#endif //FINGERPIANO_CALMAIN_H

#include "../../list/list.h"
#include "../../list/dictionary.h"

#include "stdio.h"
#include "../../list/array.h"
#include "../globalData.h"


extern void initMainLists(Node **list1, Node **list2, Node **list3, ANode **list4);


extern void freeMainLists(Node **list1, Node **list2, Node **list3, ANode **list4);


extern int getElementSize(elemType element);

extern void sortElements(elemType element);

extern void removeAllNodes(Node *list1);

extern void removeAllANodes(ANode *list1);

extern int getKeyInterval(int keyCurrent, int keyNext);

extern int getArrayLenght(int *array);

int getPostionForWhiteKey(int index);

extern void addList(Node **list, elemType data);

extern void addListWithKey(Node **list, elemType data, int key);

extern void addListWithKeyDic(DicNode **list, elemTypeDic data, int key);

extern void addArray(ANode **list, elemTypeArray data);

extern int pArrayLength(int *array);


extern int matchShunZhi(int direction, int currKeyPos, int prevKeyPos, int prevFinger);

extern int
matchKuaZhi(int direction, int prevFinger, int prevKeyPos, int currKeyPos, int next1KeyPos,
            int isMatch);

extern int matchChuanZhi(int index, int direction, int prevFinger, int prevKeyPos,
                         int currKeyPos,
                         int next1KeyPos, int next2KeyPos, int isMatch);

extern int
matchKuoZhi(int direction, int prevFinger, int prevKeyPos, int currKeyPos, int next1KeyPos,
            int mode, int isMatch, int matchFinger);

extern int matchSuoZhi(int index, int direction, int prevFinger, int prevKeyPos, int currKeyPos,
                       int next1KeyPos, int next2KeyPos, int mode, int isMatch);

extern int calStartFinger(int keySize, int *keyIndexArr, int index, int direction);

extern Boolean checkIsOutOf(int index1, int index2, int du);

extern Boolean isBlackKey(int index);

extern Boolean isWhiteKey(int index);

extern int mallocIntArray(int **array, int size);

extern void freeIntArray(int **array);


extern void trimEmpty(int *p);


