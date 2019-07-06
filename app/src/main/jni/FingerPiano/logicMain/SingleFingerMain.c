//
// Created by 77915 on 2019/7/1.
//

#include "SingleFingerMain.h"

/**
	 *  direction:	0left  1right
	 *  mode：	0下行  1上行
	 *
	 *  mode == direction 适合穿指 否则适合跨指
	 */
int *
matchFingering(int keySize, int *keyIndexArr, int index, int direction, int mode, int prevFinger) {
    int prevKeyPos = -1;
    int currKeyPos = -1;
    int next1KeyPos = -1;
    int next2KeyPos = -1;

    int matchFinger = -1;
    int isMatch = -1;
    int matchResult = -1;

    int *result = NULL;

    mallocIntArray(&result, 2);


    //0:status 1:finger

    prevKeyPos = keyIndexArr[index - 1];
    currKeyPos = keyIndexArr[index];

    //next1 next2 与前一个元素不相等
    for (int i = index + 1; i < keySize; i++) {
        if (next1KeyPos == -1) {
            if (keyIndexArr[i] != currKeyPos) {
                next1KeyPos = keyIndexArr[i];
            }
        } else {
            if (keyIndexArr[i] != next1KeyPos) {
                next2KeyPos = keyIndexArr[i];
                break;
            }
        }
    }

//		Debug.Log(currKeyPos + "********************"+next1KeyPos + "********************"+next2KeyPos);
    //判断是否适合顺指
    matchResult = matchShunZhi(direction, currKeyPos, prevKeyPos, prevFinger);
    if (matchResult != -1) {
        isMatch = 0;
        matchFinger = matchResult;
    }

    if (mode == direction) //左手：当前键在上一个键的左边  右手：当前键在上一个键的右边
    {
        //判断是否适合穿指
        matchResult = matchChuanZhi(index, direction, prevFinger, prevKeyPos, currKeyPos,
                                    next1KeyPos, next2KeyPos, isMatch);
    } else {
        //判断是否适合跨指
        matchResult = matchKuaZhi(direction, prevFinger, prevKeyPos, currKeyPos, next1KeyPos,
                                  isMatch);
    }

    if (matchResult != -1) {
        isMatch = 1;
        matchFinger = matchResult;
    }

    //判断是否适合扩指
    matchResult = matchKuoZhi(direction, prevFinger, prevKeyPos, currKeyPos, next1KeyPos, mode,
                              isMatch, matchFinger);
    if (matchResult != -1) {
        isMatch = 2;
        matchFinger = matchResult;
    }

    //判断是否适合缩指
    matchResult = matchSuoZhi(index, direction, prevFinger, prevKeyPos, currKeyPos, next1KeyPos,
                              next2KeyPos, mode, isMatch);
    if (matchResult != -1) {
        isMatch = 3;
        matchFinger = matchResult;
    }

    if (isMatch == -1 || matchFinger == -1) //未匹配到
    {
        matchFinger = calStartFinger(keySize, keyIndexArr, index, direction);
        result[0] = 0;
//			Debug.Log("index =" + index+"============抬手");
    } else {
        if (isMatch == 0) {
            result[0] = 1;
        } else if (isMatch == 1) {
            if (mode == direction) {
                result[0] = 2;
            } else {
                result[0] = 3;
            }
        } else if (isMatch == 2) {
            result[0] = 4;
        } else if (isMatch == 3) {
            result[0] = 5;
        }

//			Debug.Log("index =" + index +" 匹配到 ============" + isMatch);
    }

    result[1] = matchFinger;
    return result;
}

/**
 *
 * @param keyPosArr
 * @param direction
 * @param firstFinger -1
 * @return
 */
Node *calSingleGroupFinger(int keySize, int *keyPosArr, int direction, int firstFinger) {


    //List<int[]> resultDataList = null;
    Node *resultDataList = NULL;
    int prevKeyPos = -1;
    int currKeyPos = -1;
    int prevFinger = -1;

    int *resultData = NULL;


    //0:status 1:finger

    for (int i = 0; i < keySize; i++) {
        if (i == 0)//第一个
        {

            //和free搭配使用
            mallocIntArray(&resultData, 2);
            resultData[0] = 0;
            resultData[1] = 0;
            if (firstFinger == -1) {
                resultData[1] = calStartFinger(keySize, keyPosArr, 0, direction);
                resultData[0] = 0;
            } else {
                resultData[1] = firstFinger;
                resultData[0] = 4;
            }
            addList(&resultDataList, resultData);

            freeIntArray(&resultData);

        } else {
            prevKeyPos = keyPosArr[i - 1];
            currKeyPos = keyPosArr[i];

            elemType preArray = getElement(resultDataList, i);
            prevFinger = preArray[1];

            if (currKeyPos == prevKeyPos) //相同
            {

                mallocIntArray(&resultData, 2);
                resultData[0] = 1;
                resultData[1] = prevFinger;
                addList(&resultDataList, resultData);
                freeIntArray(&resultData);
            } else if (currKeyPos > prevKeyPos) //上行
            {
                addList(&resultDataList,
                        matchFingering(keySize, keyPosArr, i, direction, 1, prevFinger));

            } else//下行
            {
                addList(&resultDataList,
                        matchFingering(keySize, keyPosArr, i, direction, 0, prevFinger));

            }
        }
    }

    return resultDataList;

}

ANode *matchKuoZhiArr(int direction, int prevFinger, int prevKeyPos, int currKeyPos) {
    ANode *kuozhiFingerArr;
    int fingerOffset = 0;
    int keyOffset = 0;
    int mode = 0;

    initArray(&kuozhiFingerArr);


    if (currKeyPos > prevKeyPos) {
        mode = 1; //上行
    } else {
        mode = 0; //下行
    }
    keyOffset = getKeyInterval(prevKeyPos, currKeyPos);//音程
    if (direction == mode) {
        for (int i = prevFinger + 1; i < 5; i++) {
            fingerOffset = i - prevFinger;
            if (keyOffset - 1 > fingerOffset) //琴键间隔大于手指间隔
            {
                if (fingerOffset == 1 && i != 0 && prevFinger != 0 &&
                    keyOffset > 4) //相邻的两个手指，除了1、2指，扩度不能超过4度
                {
                    continue;
                }
                // kuozhiFingerArr.Add(i);
                addArray(&kuozhiFingerArr, i);

            }
        }
    } else {
        for (int i = 0; i < prevFinger; i++) {
            fingerOffset = prevFinger - i;
            if (keyOffset - 1 > fingerOffset)//琴键间隔大于手指间隔
            {
                if (fingerOffset == 1 && i != 0 && prevFinger != 0 &&
                    keyOffset > 4) //相邻的两个手指，除了1、2指，扩度不能超过4度
                {
                    continue;
                }
                addArray(&kuozhiFingerArr, i);
            }
        }
    }

    return kuozhiFingerArr;

}

Node *calMultiGroupFinger(Node *keyPosArrArr, int direction, int totalLength) {
    Node *result = NULL;
    Node *singleResult = NULL;
    DicNode *matchGroupDic = NULL;
    DicNode *notMatchGroupDic = NULL;

    //Dictionary<int[][], int> matchGroupDic = null;//存储匹配到的组
    // Dictionary<int[][], int> notMatchGroupDic = null;//存储匹配到的组

    /*HashTable matchGroupDic = create_HashTable(5);
    HashTable notMatchGroupDic = create_HashTable(5);*/


    int defaultStartFingerArr[] = {-1, 0, 1, 2, 3, 4};
    int *startFingerArr = NULL;
    int startFinger = -1;
    int firstStartFinger = -111; //默认循环第一次匹配到的起手手指

    int currLastFinger = -1;
    int currLastKeyPos = -1;
    int nextFirstKeyPos = -1;
    int nextSecondKeyPos = -1;

    int currFirstKeyPos = -1;
    int currSecondKeyPos = -1;
    int prevLastKeyPos = -1;
    int prevLastFinger = -1;

    Node *matchedSingleResult = NULL;
    int currCopyOffset = 0;

    int keyOffset = 0;
    int *keyPosArr;
    Boolean isMatch = FALSE;
    int priority = 0;//优先级 //5-1
    Boolean nextUpHand = FALSE;

    int lastMatchMode = -1;
    int lastMatchFinger = -1;

    int addLastLen = 0;

    int keyPosArrArrSize = sizeList(keyPosArrArr);

    for (int i = 1; i <= keyPosArrArrSize; i++) {
        elemType innerArray = getElement(keyPosArrArr, i);
        keyPosArr = innerArray;
        int innerArraySize = getElementKey(keyPosArrArr, i);

        currLastKeyPos = keyPosArr[innerArraySize - 1];
        addLastLen = 0;
        if (i + 1 < innerArraySize) {
            addLastLen++;

            elemType nextFirstKeyTyep = getElement(keyPosArrArr, i + 1);
            int nextKeyPosSize = getElementKey(keyPosArrArr, i + 1);
            nextFirstKeyPos = nextFirstKeyTyep[0];
            nextSecondKeyPos = -1; //找到第二个不相等的


            for (int index = 1; index < nextKeyPosSize; index++) {
                nextSecondKeyPos = nextFirstKeyTyep[index];
                if (nextFirstKeyPos != nextSecondKeyPos) {
                    addLastLen++;
                    break;
                }
            }

            //每组最后添加两个下一组的前两个元素


            freeIntArray(&keyPosArr);
            mallocIntArray(&keyPosArr, innerArraySize + addLastLen);

            keyPosArr[innerArraySize] = nextFirstKeyPos;

            if (nextSecondKeyPos != -1 && addLastLen == 2) {
                keyPosArr[innerArraySize + 1] = nextSecondKeyPos;
            }
        }

        int kuozhiArraySize = 0;
        if (i == 1 || nextUpHand == 1) {

            startFingerArr = defaultStartFingerArr;
        } else {
            //根据上一组最后的手指，计算当前组开始扩指的可用的扩指手指数组
            currFirstKeyPos = keyPosArr[0];
            elemType preinnerArray = getElement(keyPosArrArr, i - 1);
            int preinnerArraySize = getElementKey(keyPosArrArr, i - 1);

            prevLastKeyPos = preinnerArray[preinnerArraySize - 1];

            if (currCopyOffset - 1 >= 1) {
                elemType resultElem = getElement(result, currCopyOffset - 1);
                prevLastFinger = resultElem[1];

            }

            ANode *kuozhiArray = matchKuoZhiArr(direction, prevLastFinger, prevLastKeyPos,
                                                currFirstKeyPos);
            kuozhiArraySize = sizeArray(kuozhiArray);
            startFingerArr = listToIntArray(kuozhiArray);
            if (kuozhiArray == NULL) {

                free(kuozhiArray);
                kuozhiArray = NULL;
            }


        }

        if (matchedSingleResult != NULL) {
            free(matchedSingleResult);
            matchedSingleResult = NULL;
        }

        if (matchGroupDic != NULL) {
            free(matchGroupDic);
            matchGroupDic = NULL;
        }
        if (notMatchGroupDic != NULL) {
            free(notMatchGroupDic);
            notMatchGroupDic = NULL;
        }


        firstStartFinger = -111;

        for (int j = 0; j < kuozhiArraySize; j++) //每组最多循环5次
        {
            startFinger = startFingerArr[j];

            if (startFinger == firstStartFinger) //减少一次循环，排除和计算的起手手指一样的情况
            {
                continue;
            }

            isMatch = FALSE;
            priority = 0;
            singleResult = calSingleGroupFinger(innerArraySize + addLastLen, keyPosArr, direction,
                                                startFinger);


            if (j == 0) {
                matchedSingleResult = singleResult; //默认数据，在下组需要抬手时使用
                elemType _elemType = getElement(singleResult, 1);
                firstStartFinger = _elemType[1];
            }

            //判断连接下一组
            keyOffset = getKeyInterval(currLastKeyPos, nextFirstKeyPos);
            if (i + 1 < keyPosArrArrSize && keyOffset <= 8) {
                elemType _elemType = getElement(singleResult, sizeList(singleResult) - addLastLen);

                currLastFinger = _elemType[1];
                if (currLastKeyPos - nextFirstKeyPos > 0) //下行
                {
                    if (direction == 0) //left
                    {
                        if (currLastFinger == 0) {
                            isMatch = TRUE;
                            priority = 5;
                        } else if (currLastFinger == 1) {
                            isMatch = TRUE;
                            priority = 4;
                        } else if (currLastFinger == 2) {
                            isMatch = TRUE;
                            priority = 3;
                        } else if (currLastFinger == 3) {
                            isMatch = FALSE;
                        } else if (currLastFinger == 4) {
                            isMatch = FALSE;
                        }
                    } else {
                        if (currLastFinger == 0) {
                            isMatch = FALSE;
                        } else if (currLastFinger == 1) {
                            if (keyOffset <= 6) {
                                isMatch = TRUE;
                                priority = 4;
                            } else {
                                isMatch = FALSE;
                            }
                        } else if (currLastFinger == 2) {
                            isMatch = TRUE;
                            priority = 4;
                        } else if (currLastFinger == 3) {
                            isMatch = TRUE;
                            priority = 5;
                        } else if (currLastFinger == 4) {
                            isMatch = TRUE;
                            priority = 5;
                        }
                    }
                } else //上行
                {
                    if (direction == 0) //left
                    {
                        if (currLastFinger == 0) {
                            isMatch = FALSE;
                        } else if (currLastFinger == 1) {
                            if (keyOffset <= 6) {
                                isMatch = TRUE;
                                priority = 4;
                            } else {
                                isMatch = FALSE;
                            }
                        } else if (currLastFinger == 2) {
                            isMatch = TRUE;
                            priority = 4;
                        } else if (currLastFinger == 3) {
                            isMatch = TRUE;
                            priority = 5;
                        } else if (currLastFinger == 4) {
                            isMatch = TRUE;
                            priority = 5;
                        }
                    } else {
                        if (currLastFinger == 0) {
                            isMatch = TRUE;
                            priority = 5;
                        } else if (currLastFinger == 1) {
                            isMatch = TRUE;
                            priority = 4;
                        } else if (currLastFinger == 2) {
                            isMatch = TRUE;
                            priority = 3;
                        } else if (currLastFinger == 3) {
                            isMatch = FALSE;
                        } else if (currLastFinger == 4) {
                            isMatch = FALSE;
                        }
                    }
                }

                if (isMatch == 1) {
                    addListWithKeyDic(&matchGroupDic, singleResult, priority);

                    Boolean hasUpHand = FALSE;
                    if (priority == 5) //优先级5且过程中没有抬手直接跳出循环
                    {
                        for (int i = 1; i <= sizeList(singleResult); ++i) {

                            elemType object = getElement(singleResult, i);
                            if (object[0] == 0) {
                                hasUpHand = TRUE;
                                break;
                            }

                        }
                        if (hasUpHand == 0) {

                            break;
                        }
                    }
                } else {
                    int upHandCount = 0;
                    for (int i = 1; i <= sizeList(singleResult); ++i) {

                        elemType object = getElement(singleResult, i);
                        if (object[0] == 0) {
                            upHandCount++;
                        }

                    }
                    addListWithKeyDic(&notMatchGroupDic, singleResult, upHandCount);
                }
            } else //最后一组,或间隔大于8度
            {
                int upHandCount = 0;
                for (int i = 1; i <= sizeList(singleResult); ++i) {

                    elemType object = getElement(singleResult, i);
                    if (object[0] == 0) {
                        upHandCount++;
                    }

                }
                addListWithKeyDic(&notMatchGroupDic, singleResult, upHandCount);

                if (upHandCount == 0) {
                    break; //减少循环次数
                }
            }
        }

        //筛选
        if (sizeDic(matchGroupDic) > 0) {
            //找到抬手次数最少的，并且优先级最高的
            ArrangeDic(matchGroupDic, 1);
            int minCountUpHand = 999;
            for (int i = 1; i <= sizeDic(matchGroupDic); i++) {

                int upHandCount = 0;

                elemTypeDic object = getElementDic(matchGroupDic, i);

                for (int i = 1; i <= sizeList(object); i++) {
                    elemType p = getElement(object, i);
                    if (p[0] == 0) {
                        upHandCount++;

                    }


                }
                if (upHandCount < minCountUpHand) {
                    matchedSingleResult = object;
                    minCountUpHand = upHandCount;
                }

            }

            nextUpHand = FALSE;
        } else {
            //找到抬手次数最少的
            ArrangeDic(notMatchGroupDic, 0);

            elemTypeDic elemTypeDic1 = getElementDic(notMatchGroupDic, 1);
            matchedSingleResult = elemTypeDic1;
            nextUpHand = TRUE;
        }

        //copy data
        // matchedSingleResult.CopyTo(result, currCopyOffset);

        for (int i = currCopyOffset; i <= sizeList(result); ++i) {

            elemType elemType1 = getElement(result, i);
            addList(&matchedSingleResult, elemType1);

        }

        currCopyOffset += sizeList(matchedSingleResult);
        currCopyOffset -= addLastLen;
    }
    return result;
}


/**
 *
 * 处理单音节逻辑
 * @param keyArr
 * @param direction
 * @return
 */
Node *singleFingerProcess(ANode *keyArr, int direction) {


    Node *result = NULL;
    //int list
    ANode *keyIndexList = NULL;
    //int[]  list
    Node *multiGroupList = NULL;

    initList(&result);
    initArray(&keyIndexList);
    initList(&multiGroupList);

    //分组
    int size = sizeArray(keyArr);
    for (int i = 1; i <= size; i++) {
        elemTypeArray p = getElementArray(keyArr, i);
        addArray(&keyIndexList, p);

        if (i <= size - 1) {
            elemTypeArray pNext = getElementArray(keyArr, i + 1);

            int interValue = getKeyInterval(p, pNext);
            if (interValue > 5) {

                addListWithKey(&multiGroupList, listToIntArray(keyIndexList),
                               sizeArray(keyIndexList));

                clearArray(keyIndexList);
                keyIndexList = NULL;

            }

        }
    }
    int mulSize = sizeList(multiGroupList);
    if (mulSize == 0) {//只有一组

        result = calSingleGroupFinger(size, listToIntArray(keyArr), direction, -1);

    } else {

        if (sizeArray(keyIndexList) > 0) {//最后一组

            addListWithKey(&multiGroupList, listToIntArray(keyIndexList), sizeArray(keyIndexList));
            clearArray(keyIndexList);
            keyIndexList = NULL;

        }
        result = calMultiGroupFinger(multiGroupList, direction, sizeList(keyArr));

    }

    clearArray(keyIndexList);
    clearList(multiGroupList);
    keyIndexList = NULL;
    multiGroupList = NULL;

    return result;


}


