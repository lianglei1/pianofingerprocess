#include <jni.h>
#include "Log/Log.h"

#include "FingerPiano/FingerPianoMain.h"

JNIEXPORT void JNICALL
Java_com_example_mac_fingerpiano_MainActivity_test(JNIEnv *env, jobject instance) {


    Node *list = NULL;

    initList(&list);

    int test1[][6] = {
            {63},
            {60},
            {65},
            {60},
            {77, 75, 76, 78, 79},
            {60},
            {64},
            {60},
            {59},
            {60},
            {62},
            {55},
            {64},
            {60},
            {60},
            {65},
            {60},
            {60},
            {64},
            {60},
            {59},
            {60},
            {62},
            {55},
            {64},
            {64, 65, 66},
            {69},
            {69},
            {69},
            {60},
            {62},
            {64},
            {64},
            {64},
            {64},
            {64},
            {69},
            {69},
            {69},
            {67},
            {67},
            {67},
            {65},
            {64},
            {64},
            {64},
            {64},
            {69},
            {69},
            {60},
            {62},
            {64},
            {64},
            {64},
            {64},
            {60},
            {65},
            {65},
            {65},
            {65},
            {56, 60, 63, 65, 68},
            {60, 62, 63, 65, 67},
            {64},
            {64},
            {69},
            {69},
            {69},
            {60},
            {62},
            {64},
            {64},
            {64},
            {64},
            {64},
            {69},
            {69},
            {69},
            {67},
            {67},
            {67},
            {65},
            {64},
            {64},
            {64},
            {64},
            {69},
            {69},
            {60},
            {62},
            {64},
            {64},
            {64},
            {64},
            {60},
            {65},
            {65},
            {65},
            {65},
            {66, 67, 64, 68},
            {60, 62, 63},
            {67, 68},
            {69},
            {71, 72},
            {72},
            {71},
            {72},
            {72},
            {67},
            {69},
            {69},
            {67},
            {65},
            {64},
            {64},
            {64},
            {64},
            {64},
            {62},
            {62},
            {67},
            {69},
            {71},
            {72},
            {71},
            {72},
            {72},
            {67},
            {69},
            {69},
            {69},
            {71},
            {72},
            {72},
            {72},
            {72},
            {72},
            {74},
            {74},
            {67},
            {69},
            {71},
            {72},
            {71},
            {72},
            {72},
            {76},
            {81},
            {79},
            {79},
            {77, 75, 76, 78, 79},
            {76},
            {76},
            {74},
            {74},
            {69},
            {71},
            {72},
            {72},
            {74},
            {72},
            {72},
            {72},
            {71},
            {72},
            {74},
            {74},
            {72},
            {71},
            {72}};
    /*list = creatList(list, test1[0]);
    int test2[170] = {0};
    insertHeadList(&list, test1[0]);
    if(list ==NULL){


    }*/
    int *test2;

    test2 = (int *) malloc(sizeof(int) * 170);
    memset(test2, 0, sizeof(int) * 170);

    int testkey[] = {3, 4, 2, 5, 6, 7, 8};

    int size = sizeof(test1) / sizeof(test1[0]);
    for (int i = 1; i < size; ++i) {
        addListWithKey(&list, test1[i], testkey[i % 6]);

    }


    FingerEntity *fingerEntity = mainProcess(list, test2, 0);

    /*DicNode *dicNode = NULL;
    initDic(&dicNode);
    for (int i = 1; i <= 3; ++i) {
        addListWithKeyDic(&dicNode, list, i);

    }

    ArrangeDic(dicNode, 1);

    printDic(dicNode)

    if (dicNode != NULL) {
        free(dicNode);
        dicNode
        = NULL;
    }
    ;*/
    // printList(list);

    /*LOGD("range before");
    ArrangeList(list);
    LOGD("range after");*/

    // printList(list);




    /*LOGD("fingerEntity keyIndexArrArr-----------------------------------");
    printList(fingerEntity->keyIndexArrArr);
    LOGD("fingerEntity fingerIndexArrArr-----------------------------------");
    printList(fingerEntity->fingerIndexArrArr);
    LOGD("fingerEntity statusArrSize-----------------------------------");

    for (int i = 0; i < fingerEntity->statusArrSize; ++i) {

        LOGD("statusArr%d", fingerEntity->statusArr[i]);

    }*/


    //printList(resultList);

    if (fingerEntity != NULL) {
        free(fingerEntity);
        fingerEntity = NULL;
    }
    if (test2 != NULL) {
        free(test2);
        test2 = NULL;
    }

    clearList(list);
    list = NULL;


}