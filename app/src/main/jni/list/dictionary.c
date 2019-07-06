//
// Created by 77915 on 2019/7/3.
//

#include "dictionary.h"


/* 1.初始化线性表，即置单链表的表头指针为空 */
void initDic(DicNode **pNode) {
    *pNode = NULL;
    printf("initList函数执行，初始化成功\n");
}

/* 2.创建线性表，此函数输入负数终止读取数据*/
DicNode *creatDic(DicNode *pHead, elemTypeDic element) {
    DicNode *p1;
    p1 = (DicNode *) malloc(sizeof(DicNode));
    if (p1 == NULL) {
        printf("内存分配失败\n");
    }
    memset(p1, 0, sizeof(DicNode));
    p1->element = element;
    p1->next = NULL;
    pHead = p1;
    printf("CreatList函数执行，链表创建成功\n");
    return pHead;
}

/* 2.创建线性表，此函数输入负数终止读取数据*/
DicNode *creatDicWithKey(DicNode *pHead, elemTypeDic element, int key) {
    DicNode *p1;
    p1 = (DicNode *) malloc(sizeof(DicNode));
    if (p1 == NULL) {
        printf("内存分配失败\n");
    }
    memset(p1, 0, sizeof(DicNode));
    p1->element = element;
    p1->key = key;
    p1->next = NULL;
    pHead = p1;
    printf("CreatList函数执行，链表创建成功\n");
    return pHead;
}


/* 3.打印链表，链表的遍历*/
void printDic(DicNode *pHead) {
    if (NULL == pHead) {
        printf("PrintList函数执行，链表为空\n");
    } else {
        while (NULL != pHead) {
            /*  LOGD("{%d,%d,%d,%d,%d,%d,%d},\n", pHead->element[0][0], pHead->element[1],
                   pHead->element[2], pHead->element[3], pHead->element[4], pHead->element[5],pHead->key);*/

            LOGD("printDic%d",pHead->key);
            printList(pHead->element);
            LOGD("printDic%d",pHead->key);

            pHead = pHead->next;
        }
    }

}


/* 4.清除线性表L中的所有元素，即释放单链表L中所有的结点，使之成为一个空表 */
void clearDic(DicNode *pHead) {
    DicNode *pNext;

    if (pHead == NULL) {
        printf("clearList函数执行，链表为空\n");
        return;
    }
    while (pHead->next != NULL) {
        pNext = pHead->next;
        free(pHead);
        pHead = pNext;
        // LOGD("clearList函数执行，链表已经清除！\n");
    }
    printf("clearList函数执行，链表已经清除！\n");

}

/* 5.返回链表的长度*/
int sizeDic(DicNode *pHead) {
    int size = 0;

    while (pHead != NULL) {
        size++;
        pHead = pHead->next;
    }
    printf("sizelist函数执行，链表长度为%d\n", size);
    return size;
}

/* 6.检查单链表是否为空，若为空则返回１，否则返回０ */
int isEmptyDic(DicNode *pHead) {
    if (pHead == NULL) {
        printf("isEmptylist函数执行，链表为空！\n");
        return 1;
    } else
        printf("isEmptylist函数执行，链表非空！\n");
    return 0;

}

/* 7.返回链表中第post节点的数据，若post超出范围，则停止程序运行*/
elemTypeDic getElementDic(DicNode *pHead, int pos) {
    int i = 0;
    if (pos < 1) {
        printf("getElement函数执行，pos值非法！");
    }
    if (pHead == NULL) {
        printf("getElement函数执行，链表为空！");
    }

    while (pHead != NULL) {
        ++i;
        if (i == pos) {
            break;
        }
        pHead = pHead->next;
    }
    if (i < pos) {
        printf("getElement函数执行，pos值超出链表长度\n");
    }
    //
    // LOGD("getElement函数执行，位置%d中的元素为%d\n", pos, pHead->element);

    return pHead->element;
}

/* 7.返回链表中第post节点的数据，若post超出范围，则停止程序运行*/
int getElementKeyDic(DicNode *pHead, int pos) {
    int i = 0;
    if (pos < 1) {
        printf("getElement函数执行，pos值非法！");
    }
    if (pHead == NULL) {
        printf("getElement函数执行，链表为空！");
    }

    while (pHead != NULL) {
        ++i;
        if (i == pos) {
            break;
        }
        pHead = pHead->next;
    }
    if (i < pos) {
        printf("getElement函数执行，pos值超出链表长度\n");
    }
    //
    // LOGD("getElement函数执行，位置%d中的元素为%d\n", pos, pHead->element);

    return pHead->key;
}

//8.从单一链表中查找具有给定值x的第一个元素，若查找成功后，返回该节点data域的存储位置，否则返回NULL
elemTypeDic *getElemAddrDic(DicNode *pHead, elemTypeDic x) {
    if (NULL == pHead) {
        printf("getEleAddr函数执行，链表为空");
        return NULL;
    }
    if (x < 0) {
        printf("getEleAddr函数执行，给定值x不合法\n");
        return NULL;
    }
    while ((pHead->element != x) && (NULL != pHead->next))//判断链表是否为空，并且是否存在所查找的元素
    {
        pHead = pHead->next;
    }
    if (pHead->element != x) {
        printf("getElemAddr函数执行，在链表中没有找到x值\n");
        return NULL;
    } else {
        // printf("getElemAddr函数执行，元素%d的地址为0x%x\n", x, &(pHead->element));
    }
    return &(pHead->element);

}


/* 10.向单链表的表头插入一个元素 */
int insertHeadDic(DicNode **pNode, elemTypeDic insertElem) {
    DicNode *pInsert;
    pInsert = (DicNode *) malloc(sizeof(DicNode));
    if (pInsert != NULL)
        memset(pInsert, 0, sizeof(DicNode));
    pInsert->element = insertElem;
    pInsert->next = *pNode;
    *pNode = pInsert;
    // printf("insertHeadList函数执行，向表头插入元素%d成功\n",insertElem);
    return 1;
}

/* 11.向单链表的末尾添加一个元素 */
int insertLastDic(DicNode *pNode, elemTypeDic insertElem) {
    DicNode *pInsert;
    DicNode *pHead;
    //Node *pTmp;

    pHead = pNode;
    // pTmp=pHead;
    pInsert = (DicNode *) malloc(sizeof(DicNode));
    if (pInsert == NULL)
        return 0;
    memset(pInsert, 0, sizeof(DicNode));
    pInsert->element = insertElem;
    pInsert->next = NULL;
    while (pHead->next != NULL) {
        pHead = pHead->next;
    }
    pHead->next = pInsert;
    //  printf("insertLastList函数执行，向表尾插入元素%d成功!\n", insertElem);
    return 1;
}


/* 11.向单链表的末尾添加一个元素 */
int insertLastDicWithKey(DicNode *pNode, elemTypeDic insertElem, int key) {
    DicNode *pInsert;
    DicNode *pHead;
    //Node *pTmp;

    pHead = pNode;
    // pTmp=pHead;
    pInsert = (DicNode *) malloc(sizeof(DicNode));
    if (pInsert == NULL)
        return 0;
    memset(pInsert, 0, sizeof(DicNode));
    pInsert->element = insertElem;
    pInsert->key = key;
    pInsert->next = NULL;
    while (pHead->next != NULL) {
        pHead = pHead->next;
    }
    pHead->next = pInsert;
    //  printf("insertLastList函数执行，向表尾插入元素%d成功!\n", insertElem);
    return 1;
}


void swapDicValue(elemTypeDic *p1, elemTypeDic *p2) {

    elemTypeDic temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int swapDicPosup(int *p1, int *p2, elemTypeDic *v1, elemTypeDic *v2) {
    int a;
    if (*p1 > *p2) {
        a = *p1;
        *p1 = *p2;
        *p2 = a;
        swapDicValue(v1, v2);
    }
    return 0;
}

int swapDicPosDown(int *p1, int *p2, elemTypeDic *v1, elemTypeDic *v2) {
    int a;
    if (*p1 < *p2) {
        a = *p1;
        *p1 = *p2;
        *p2 = a;
        swapValue(v1, v2);
    }
    return 0;
}



/* 19.将线性表进行冒泡排序 */
/**
 *
 * @param pNode
 * @param flag  0 popup 1 popdown
 * @return
 */
int ArrangeDic(DicNode *pNode, int flag) {
    DicNode *pHead;
    pHead = pNode;

    int a = 0, i, j;

    if (NULL == pHead) {
        printf("Arrange函数执行，链表为空\n");
        return 0;
    }

    while (pHead != NULL) {
        ++a;
        pHead = pHead->next;
    }

    pHead = pNode;
    for (i = 0; i < a - 1; i++) {
        for (j = 1; j < a - i; j++) {
            if (flag == 0) {
                swapDicPosup(&(pHead->key), &(pHead->next->key), &(pHead->element),
                             &(pHead->next->element));

            } else {
                swapDicPosDown(&(pHead->key), &(pHead->next->key), &(pHead->element),
                               &(pHead->next->element));

            }
            pHead = pHead->next;
        }
        pHead = pNode;
    }
    printf("Arrange函数执行，链表排序完毕!\n");
    return 0;
}
