//
// Created by mac on 2017/10/30.
//

#include "FingerPianoMain.h"


FingerEntity *createFingerEntity(Node *list1, Node *list2,int *beatRenderIndexArr, int *list3,int statusASize) {

    FingerEntity *fingerEntity;
    fingerEntity = (FingerEntity *) malloc(sizeof(FingerEntity));
    memset(fingerEntity, 0, sizeof(FingerEntity));
    fingerEntity->fingerIndexArrArr = list2;
    fingerEntity->statusArr = list3;
    fingerEntity->statusArrSize = statusASize;
    fingerEntity->keyIndexArrArr = list1;
    fingerEntity->beatRenderIndexArr= beatRenderIndexArr;

    return fingerEntity;
}

void printsomethis(int something) {

    LOGD("print:%d", something);

}


/**
 * 函数主入口     mainprocess(分组)
 *              |              |
 *      SingleFingerMain    ChodFingerProcess
 *      单音                   和弦
 * @param pitchArrArr
 * @param beatRenderIndexArr
 * @param direction
 * @return
 */
FingerEntity *mainProcess(Node *pitchArrArr, int *beatRenderIndexArr, int direction) {


    Node *keyArrList = NULL;
    Node *fingerArrList = NULL;
    Node *singleResult = NULL;
    ANode *singleFingerGroup = NULL;

    ANode *statusList = NULL;
    int *chordFingerArr = NULL;

    int *pitchArr;

    initMainLists(&keyArrList, &fingerArrList, &singleResult, &singleFingerGroup);

    int size = sizeList(pitchArrArr);


    for (int i = 1; i <= size; i++) {
        elemType p = getElement(pitchArrArr, i);

        for (int j = 0; j < 6; j++) {
            if (p[j] > 0) {
                p[j] -= 21;
            }

        }

        if (getElementSize(p) > 1) {
            sortElements(p);

        }

        pitchArr = p;

        addList(&keyArrList, pitchArr);

        if (getElementSize(pitchArr) == 1) {

            addArray(&singleFingerGroup, pitchArr[0]);

        } else {

            if (sizeArray(singleFingerGroup) > 0) {
                LOGD("element");
                printArray(singleFingerGroup);
                LOGD("element");

                singleResult = singleFingerProcess(singleFingerGroup, direction);

                if (singleResult != NULL) {
                    int srsize = sizeList(singleResult);
                    for (int i = 1; i <= srsize; ++i) {

                        elemType data = getElement(singleResult, i);
                        int temp[] = {0};
                        temp[0] = data[1];

                        addArray(&statusList, data[0]);
                        addList(&fingerArrList, temp);
                    }

                }
                //防止内存泄漏
                if (singleFingerGroup != NULL) {
                    clearArray(singleFingerGroup);
                    singleFingerGroup = NULL;
                }

                //防止内存泄漏
                if (singleResult != NULL) {
                    clearList(singleResult);
                    singleResult = NULL;

                }


            }

            //和弦
            chordFingerArr = chordFingerProcess(pitchArr, direction);

            addList(&fingerArrList, chordFingerArr);
            if (chordFingerArr == NULL) {

                //不合法
                addArray(&statusList, 1);
            } else {
                //合法
                addArray(&statusList, 2);
            }

            freeIntArray(&chordFingerArr);


        }

    }

    //二维数组的一个元素为单音模式
    if (sizeArray(singleFingerGroup) > 0) {
        LOGD("element out");
        printArray(singleFingerGroup);
        LOGD("element out");

        singleResult = singleFingerProcess(singleFingerGroup, direction);

        if (singleResult != NULL) {
            int srsize = sizeList(singleResult);
            for (int i = 1; i <= srsize; ++i) {

                elemType data = getElement(singleResult, i);
                int temp[] = {0};
                temp[0] = data[1];

                addArray(&statusList, data[0]);
                addList(&fingerArrList, temp);
            }

        }
        clearArray(singleFingerGroup);
        singleFingerGroup = NULL;

    }

    printList(pitchArrArr);

    FingerEntity *result = createFingerEntity(keyArrList, fingerArrList,beatRenderIndexArr,
                                              listToIntArray(statusList),sizeArray(statusList));
    freeMainLists(&keyArrList, &fingerArrList, &singleResult, &singleFingerGroup);


    if (chordFingerArr != NULL) {
        free(chordFingerArr);
        chordFingerArr = NULL;
    }
    clearArray(statusList);


    return result;
}


