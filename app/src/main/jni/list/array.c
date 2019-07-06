//
// Created by 77915 on 2019/7/1.
//

#include "array.h"

/************************************************************************/
/*             以下是关于线性表链接存储（单链表）操作的19种算法        */

/* 1.初始化线性表，即置单链表的表头指针为空 */
/* 2.创建线性表，此函数输入负数终止读取数据*/
/* 3.打印链表，链表的遍历*/
/* 4.清除线性表L中的所有元素，即释放单链表L中所有的结点，使之成为一个空表 */
/* 5.返回单链表的长度 */
/* 6.检查单链表是否为空，若为空则返回１，否则返回０ */
/* 7.返回单链表中第pos个结点中的元素，若pos超出范围，则停止程序运行 */
/* 8.从单链表中查找具有给定值x的第一个元素，若查找成功则返回该结点data域的存储地址，否则返回NULL */
/* 9.把单链表中第pos个结点的值修改为x的值，若修改成功返回１，否则返回０ */
/* 10.向单链表的表头插入一个元素 */
/* 11.向单链表的末尾添加一个元素 */
/* 12.向单链表中第pos个结点位置插入元素为x的结点，若插入成功返回１，否则返回０ */
/* 13.向有序单链表中插入元素x结点，使得插入后仍然有序 */
/* 14.从单链表中删除表头结点，并把该结点的值返回，若删除失败则停止程序运行 */
/* 15.从单链表中删除表尾结点并返回它的值，若删除失败则停止程序运行 */
/* 16.从单链表中删除第pos个结点并返回它的值，若删除失败则停止程序运行 */
/* 17.从单链表中删除值为x的第一个结点，若删除成功则返回1,否则返回0 */
/* 18.交换2个元素的位置 */
/* 19.将线性表进行冒排序 */



/*注意检查分配到的动态内存是否为空*/




/* 1.初始化线性表，即置单链表的表头指针为空 */
void initArray(ANode **pANode) {
    *pANode = NULL;
    printf("initList函数执行，初始化成功\n");
}

/* 2.创建线性表，此函数输入负数终止读取数据*/
ANode *creatArray(ANode *pHead, elemTypeArray element) {

    ANode *p1;
    p1 = (ANode *) malloc(sizeof(ANode));
    if (p1 == NULL) {
        printf("内存分配失败\n");
    }
    memset(p1, 0, sizeof(ANode));
    p1->element = element;
    p1->next = NULL;
    pHead = p1;
    printf("CreatList函数执行，链表创建成功\n");
    return pHead;
}

/* 3.打印链表，链表的遍历*/
void printArray(ANode *pHead) {
    if (NULL == pHead) {
        printf("PrintList函数执行，链表为空\n");
    } else {
        while (NULL != pHead) {
            LOGD("1:{%d},\n", pHead->element);

            pHead = pHead->next;
        }
    }

}


/* 4.清除线性表L中的所有元素，即释放单链表L中所有的结点，使之成为一个空表 */
void clearArray(ANode *pHead) {
    ANode *pNext;

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
int sizeArray(ANode *pHead) {
    int size = 0;

    while (pHead != NULL) {
        size++;
        pHead = pHead->next;
    }
    printf("sizelist函数执行，链表长度为%d\n", size);
    return size;
}

/* 6.检查单链表是否为空，若为空则返回１，否则返回０ */
int isEmptyArray(ANode *pHead) {
    if (pHead == NULL) {
        printf("isEmptylist函数执行，链表为空！\n");
        return 1;
    } else
        printf("isEmptylist函数执行，链表非空！\n");
    return 0;

}

/* 7从 1 开始 否则报错返回链表中第post节点的数据，若post超出范围，则停止程序运行*/
elemTypeArray getElementArray(ANode *pHead, int pos) {
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
    printf("getElement函数执行，位置%d中的元素为%d\n", pos, pHead->element);

    return pHead->element;
}

//8.从单一链表中查找具有给定值x的第一个元素，若查找成功后，返回该节点data域的存储位置，否则返回NULL
elemTypeArray *getElemAddrArray(ANode *pHead, elemTypeArray x) {
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
        //  printf("getElemAddr函数执行，元素%d的地址为0x%x\n", x, &(pHead->element));
    }
    return &(pHead->element);

}


/*9.修改链表中第pos个点X的值，如果修改成功，则返回1,否则返回0*/
int modifyElemArray(ANode *pANode, int pos, elemTypeArray x) {
    ANode *pHead;
    pHead = pANode;
    int i = 0;
    if (NULL == pHead) {
        printf("modifyElem函数执行，链表为空\n");
        return 0;
    }

    if (pos < 1) {
        printf("modifyElem函数执行，pos值非法\n");
        return 0;
    }

    while (pHead != NULL) {
        ++i;
        if (i == pos) {
            break;
        }
        pHead = pHead->next;
    }

    if (i < pos) {
        printf("modifyElem函数执行，pos值超出链表长度\n");
        return 0;
    }
    pANode = pHead;
    pANode->element = x;
    printf("modifyElem函数执行,修改第%d点的元素为%d\n", pos, x);

    return 1;

}

/* 10.向单链表的表头插入一个元素 */
int insertHeadArray(ANode **pANode, elemTypeArray insertElem) {
    ANode *pInsert;
    pInsert = (ANode *) malloc(sizeof(ANode));
    if (pInsert == NULL) exit(1);
    memset(pInsert, 0, sizeof(ANode));
    pInsert->element = insertElem;
    pInsert->next = *pANode;
    *pANode = pInsert;
    printf("insertHeadList函数执行，向表头插入元素%d成功\n", insertElem);
    return 1;
}

/* 11.向单链表的末尾添加一个元素 */
int insertLastArray(ANode *pANode, elemTypeArray insertElem) {
    ANode *pInsert;
    ANode *pHead;
    //ANode *pTmp;

    pHead = pANode;
    // pTmp=pHead;
    pInsert = (ANode *) malloc(sizeof(ANode));
    if (pInsert == NULL)
        return 0;
    memset(pInsert, 0, sizeof(ANode));
    pInsert->element = insertElem;
    pInsert->next = NULL;
    while (pHead->next != NULL) {
        pHead = pHead->next;
    }
    pHead->next = pInsert;
    printf("insertLastList函数执行，向表尾插入元素%d成功!\n", insertElem);
    return 1;
}

/* 12.向单链表中第pos个结点位置插入元素为x的结点，若插入成功返回１，否则返回０*/
int isAddPosArray(ANode *pANode, int pos, elemTypeArray x) {
    ANode *pHead;
    pHead = pANode;
    ANode *pTmp;
    int i = 0;

    if (NULL == pHead) {
        printf("AddPos函数执行，链表为空\n");
        return 0;
    }

    if (pos < 1) {
        printf("AddPos函数执行，pos值非法\n");
        return 0;
    }

    while (pHead != NULL) {
        ++i;
        if (i == pos)
            break;
        pHead = pHead->next;
    }

    if (i < pos) {
        printf("AddPos函数执行，pos值超出链表长度\n");
        return 0;
    }

    pTmp = (ANode *) malloc(sizeof(ANode));
    if (pTmp == NULL) exit(1);
    memset(pTmp, 0, sizeof(ANode));
    pTmp->next = pHead->next;
    pHead->next = pTmp;
    pTmp->element = x;

    printf("AddPos函数执行成功，向节点%d后插入数值%d\n", pos, x);
    return 1;
}

/* 13.向有序单链表中插入元素x结点，使得插入后仍然有序 */
int OrrderArray(ANode *pANode, elemTypeArray x) {
//注意如果此数值要排到行尾要修改本代码
    ANode *pHead;
    pHead = pANode;
    ANode *pTmp;

    if (NULL == pHead) {
        printf("OrrderList函数执行，链表为空\n");
        return 0;
    }

    if (x < 1) {
        printf("OrrderList函数执行，x值非法\n");
        return 0;
    }

    while (pHead != NULL) {
        if ((pHead->element) >= x)
            break;
        pHead = pHead->next;
    }


    if (pHead == NULL) {
        printf("OrrderList函数查找完毕，该函数中没有该值\n");
        return 0;
    }


    pTmp = (ANode *) malloc(sizeof(ANode));
    if (pTmp == NULL) exit(1);
    memset(pTmp, 0, sizeof(ANode));
    pTmp->next = pHead->next;
    pHead->next = pTmp;
    pTmp->element = x;

    printf("OrrderList函数成功插入数值%d\n", x);
    return 1;
}

/*14.从单链表中删除表头结点，并把该结点的值返回，若删除失败则停止程序运行*/
int DelHeadArray(ANode **pList) {
    ANode *pHead;
    pHead = *pList;
    if (pHead != NULL)
        printf("DelHeadList函数执行,函数首元素为%d删除成功\n", pHead->element);
    else {
        printf("DelHeadList函数执行,链表为空!");
        return 0;
    }
    *pList = pHead->next;
    return 1;
}

/* 15.从单链表中删除表尾结点并返回它的值，若删除失败则停止程序运行 */
int DelLastArray(ANode *pANode) {
    ANode *pHead;
    ANode *pTmp;

    pHead = pANode;
    while (pHead->next != NULL) {
        pTmp = pHead;
        pHead = pHead->next;
    }
    printf("链表尾删除元素%d成功!\n", pHead->element);
    free(pHead);
    pTmp->next = NULL;
    return 1;
}

/* 16.从单链表中删除第pos个结点并返回它的值，若删除失败则停止程序运行 */
int DelPosArray(ANode *pANode, int pos) {
    ANode *pHead;
    pHead = pANode;
    ANode *pTmp;

    int i = 0;

    if (NULL == pHead) {
        printf("DelPos函数执行，链表为空\n");
        return 0;
    }

    if (pos < 1) {
        printf("DelPos函数执行，pos值非法\n");
        return 0;
    }

    while (pHead != NULL) {
        ++i;
        if (i == pos)
            break;
        pTmp = pHead;
        pHead = pHead->next;
    }

    if (i < pos) {
        printf("DelPos函数执行，pos值超出链表长度\n");
        return 0;
    }
    printf("DelPos函数执行成功，节点%d删除数值%d\n", pos, pHead->element);
    pTmp->next = pHead->next;
    free(pHead);
    return 1;
}

/* 17.从单链表中删除值为x的第一个结点，若删除成功则返回1,否则返回0 */
int DelxArray(ANode **pANode, int x) {
    ANode *pHead;
    ANode *pTmp;
    pHead = *pANode;
    int i = 0;

    if (NULL == pHead) {
        printf("Delx函数执行，链表为空");
        return 0;
    }
    if (x < 0) {
        printf("Delx函数执行，给定值x不合法\n");
        return 0;
    }
    while ((pHead->element != x) && (NULL != pHead->next))//判断链表是否为空，并且是否存在所查找的元素
    {
        ++i;
        pTmp = pHead;
        pHead = pHead->next;
    }
    if (pHead->element != x) {
        printf("Delx函数执行，在链表中没有找到x值\n");
        return 0;
    }
    if ((i == 0) && (NULL != pHead->next)) {
        printf("Delx函数执行，在链表首部找到此元素,此元素已经被删除\n");
        *pANode = pHead->next;
        free(pHead);
        return 1;
    }
    printf("Delx函数执行，首个为%d元素被删除\n", x);
    pTmp->next = pHead->next;
    free(pHead);
    return 1;
}

/* 18.交换2个元素的位置 */
int exchange2posArray(ANode *pANode, int pos1, int pos2) {
    ANode *pHead;
    int *pTmp;
    int *pInsert;
    int a;
    int i = 0;

    if (pos1 < 1 || pos2 < 1) {
        printf("DelPos函数执行，pos值非法\n");
        return 0;
    }

    pHead = pANode;
    while (pHead != NULL) {
        ++i;
        if (i == pos1)
            break;
        pHead = pHead->next;
    }

    if (i < pos1) {
        printf("DelPos函数执行，pos1值超出链表长度\n");
        return 0;
    }

    pTmp = &(pHead->element);
    i = 0;
    pHead = pANode;
    while (pHead != NULL) {
        ++i;
        if (i == pos2)
            break;
        pHead = pHead->next;
    }

    if (i < pos2) {
        printf("DelPos函数执行，pos2值超出链表长度\n");
        return 0;
    }

    pInsert = &(pHead->element);
    a = *pTmp;
    *pTmp = *pInsert;
    *pInsert = a;

    printf("DelPos函数执行,交换第%d个和第%d个pos点的值\n", pos1, pos2);
    return 1;
}

int swapPos(int *p1, int *p2) {
    int a;
    if (*p1 > *p2) {
        a = *p1;
        *p1 = *p2;
        *p2 = a;
    }
    return 0;
}

/* 19.将线性表进行冒泡排序 */
int ArrangeArray(ANode *pANode) {
    ANode *pHead;
    pHead = pANode;

    int a = 0, i, j;

    if (NULL == pHead) {
        printf("Arrange函数执行，链表为空\n");
        return 0;
    }

    while (pHead != NULL) {
        ++a;
        pHead = pHead->next;
    }

    pHead = pANode;
    for (i = 0; i < a - 1; i++) {
        for (j = 1; j < a - i; j++) {
            swapPos(&(pHead->element), &(pHead->next->element));
            pHead = pHead->next;
        }
        pHead = pANode;
    }
    printf("Arrange函数执行，链表排序完毕!\n");
    return 0;
}


elemTypeArray *listToIntArray(ANode *pHead) {
    int size = sizeArray(pHead);
    elemTypeArray *result = NULL;

    result = (elemTypeArray *) malloc(sizeof(elemTypeArray) * size);

    if (result != NULL) {
        memset(result, 0, sizeof(int) * size);
    }

    for (int i = 1; i <= size; ++i) {

        elemTypeArray element = getElementArray(pHead, i);

        result[i-1] = element;
    }

    return result;

}