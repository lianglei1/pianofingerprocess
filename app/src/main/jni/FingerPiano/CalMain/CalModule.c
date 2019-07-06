//
// Created by mac on 2017/10/30.
//

#include "CalModule.h"
#include "string.h"
#include <math.h>


void initMainLists(Node **list1, Node **list2, Node **list3, ANode **list4) {
    initList(list1);
    initList(list2);
    initList(list3);
    initArray(list4);
}


void freeMainLists(Node **list1, Node **list2, Node **list3, ANode **list4) {

    if (*list1 != NULL) {
        clearList(*list1);
        *list1 = NULL;
    }
    if (*list2 != NULL) {
        clearList(*list2);
        *list2 = NULL;

    }
    if (*list3 != NULL) {
        clearList(*list3);
        *list3 = NULL;

    }
    if (*list4 != NULL) {
        clearArray(*list4);
        *list4 = NULL;
    }


}

/**
 * 获取有效被赋值的个数
 * @param element
 * @return
 */
int getElementSize(elemType element) {

    int size = 6;

    int count = 0;

    for (int i = 0; i < size; ++i) {

        if (element[i] != 0)
            count++;
    }

    return count;


}

void sortElements(elemType element) {


    int size = 6;
    //接下来进行排序
    for (int i = 0; i < size - 1; ++i)//n个数,总共需要进行n-1次
    {                 //n-1个数排完,第一个数一定已经归位
        //每次会将最大(升序)或最小(降序)放到最后面
        for (int j = 0; j < size - i - 1; ++j) {
            if (element[j] > element[j + 1])//每次冒泡,进行交换
            {
                int temp;
                temp = element[j];
                element[j] = element[j + 1];
                element[j + 1] = temp;
            }
        }

    }


}

void removeAllNodes(Node *list1) {

    int size = sizeList(list1);

    for (int i = 1; i < size; ++i) {

        DelLastList(list1);
    }

}

void removeAllANodes(ANode *list1) {

    int size = sizeArray(list1);

    for (int i = 1; i < size; ++i) {

        DelLastArray(list1);
    }

}
//求两个按键间隔的音节数同一个为0

int getKeyInterval(int keyCurrent, int keyNext) {

    int ret = 0;

    if (keyCurrent != keyNext) {
        int current = getPostionForWhiteKey(keyCurrent);
        int next = getPostionForWhiteKey(keyNext);
        int num = current - next;
        ret = abs(num) + 1;
    }

    return ret;

}


//以白键为标志计算
int getPostionForWhiteKey(int index) {
    int ret = -1;
    int intervalCount = whitekeysSize;

    for (int i = 0; i < intervalCount; i++) {
        int whiteKey = whiteKeyIndexArr[i];

        if (whiteKey >= index) {
            ret = i;
            break;
        }
    }

    return ret;
}


/**
 *
 * @param list **list
 * @param data
 */
void addList(Node **list, elemType data) {
    if (*list == NULL) {
        *list = creatList(*list, data);
    } else {
        insertLastList(*list, data);
    }


}

/**
 *
 * @param list **list
 * @param data
 */
void addListWithKey(Node **list, elemType data, int key) {
    if (*list == NULL) {
        *list = creatListWithKey(*list, data,key);
    } else {
        insertLastListWithKey(*list, data,key);
    }


}
void addListWithKeyDic(DicNode **list, elemTypeDic data, int key) {
    if (*list == NULL) {
        *list = creatDicWithKey(*list, data,key);
    } else {
        insertLastDicWithKey(*list, data,key);
    }


}


void addArray(ANode **list, elemTypeArray data) {
    if (*list == NULL) {
        *list = creatArray(*list, data);
    } else {
        insertLastArray(*list, data);
    }


}


int matchShunZhi(int direction, int currKeyPos, int prevKeyPos, int prevFinger) {
    int shunzhiFinger = -1;
    int keyOffset = 0;

    keyOffset = prevKeyPos - currKeyPos;

    if (abs(keyOffset) != 1) //考虑黑键 等于1 是黑键
    {
        currKeyPos = getPostionForWhiteKey(currKeyPos);
        prevKeyPos = getPostionForWhiteKey(prevKeyPos);

        keyOffset = prevKeyPos - currKeyPos;
    }

    for (int i = 0; i < 5; i++) {
        if (direction == 0) {
            if (i - prevFinger == keyOffset) {
                shunzhiFinger = i;
                break;
            }
        } else {
            if (prevFinger - i == keyOffset) {
                shunzhiFinger = i;
                break;
            }
        }
    }

    return shunzhiFinger;
}


int matchKuaZhi(int direction, int prevFinger, int prevKeyPos, int currKeyPos, int next1KeyPos,
                int isMatch) {
    int ret = -1;
    int nextOffset = 0;

    //上一个键必须1指，跨度不超过4度，不别指
    if (prevFinger == 0 && !checkIsOutOf(prevKeyPos, currKeyPos, 4) &&
        !(isBlackKey(prevKeyPos) && isWhiteKey(currKeyPos))) {
        if (next1KeyPos == -1) {
            if (isMatch == -1) {
                ret = 1;
            }
        } else {
            if (isMatch == 0) {
                if ((direction == 0 && next1KeyPos > currKeyPos) ||
                    (direction == 1 && next1KeyPos < currKeyPos)) //和穿指相反
                {
                    //1、2、3指筛选
                    if (isBlackKey(currKeyPos))//跨黑键用中指，中指最长比较方便
                    {
                        ret = 2;
                    } else {
                        ret = 1;
                    }
                }
            } else {
                if (isBlackKey(currKeyPos))//跨黑键用中指，中指最长比较方便
                {
                    ret = 2;
                } else {
                    ret = 1;
                }
            }
        }
    }

    return ret;
}


int matchChuanZhi(int index, int direction, int prevFinger, int prevKeyPos, int currKeyPos,
                  int next1KeyPos, int next2KeyPos, int isMatch) {
    int chuanzhiFinger = -1;


    //上一个键不是1指和4指，穿的范围不超过4度，不别指
    Boolean isoutof = checkIsOutOf(prevKeyPos, currKeyPos, 4);
    Boolean iswKey = isWhiteKey(prevKeyPos);
    Boolean isBKey = isBlackKey(currKeyPos);

    if (prevFinger != 0 && prevFinger != 4 && isoutof == 0 && isBKey == 1 && iswKey == 0) {
        if (next1KeyPos == -1) //最后一个
        {
            chuanzhiFinger = -1;
        } else {
            if ((direction == 0 && next1KeyPos < currKeyPos) ||
                (direction == 1 && next1KeyPos > currKeyPos)) //left连续下行 或 right连续上行
            {
                chuanzhiFinger = 0;

                if (isMatch == 0) {
                    //连续顺指
                    if (getKeyInterval(currKeyPos, prevKeyPos) <= 2 &&
                        getKeyInterval(currKeyPos, next1KeyPos) <= 2) {
                        if (prevFinger == 2)//防止第四指边界问题
                        {
                            if (direction == 0 && next2KeyPos < next1KeyPos) {
                                chuanzhiFinger = 0;
                            } else if (direction == 1 && next2KeyPos > next1KeyPos) {
                                chuanzhiFinger = 0;
                            } else {
                                chuanzhiFinger = -1;
                            }
                        } else {
                            chuanzhiFinger = -1;
                        }
                    }

                    if (next2KeyPos != -1) {
                        if ((direction == 0 && next2KeyPos >= next1KeyPos) ||
                            (direction == 1 && next2KeyPos <= next1KeyPos)) //非连续下行或上行
                        {
                            chuanzhiFinger = -1;
                        }
                    }
                }
            }
        }
    }

    return chuanzhiFinger;
}


int matchKuoZhi(int direction, int prevFinger, int prevKeyPos, int currKeyPos, int next1KeyPos,
                int mode, int isMatch, int matchFinger) {
    int kuozhiFinger = -1;
    int kuozhiFingerLen = 0;
    int kuozhiFingerArr[4] = {0};
    int keyOffset = 0;
    int fingerOffset = 0;
    int isMust = 0;


    for (int i = 0; i < 4; i++) {
        kuozhiFingerArr[i] = -1;
    }
    if ((mode == direction && prevFinger != 4) || (mode != direction && prevFinger != 0)) {
        if (!checkIsOutOf(prevKeyPos, currKeyPos, 9)) {
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
                        kuozhiFingerArr[kuozhiFingerLen] = i;
                        kuozhiFingerLen++;
                    }
                }

                if (kuozhiFingerLen > 0) {
                    if (kuozhiFingerLen == 1) {
                        kuozhiFinger = kuozhiFingerArr[0];
                    } else {
                        //筛选
                        if ((direction == 0 && next1KeyPos < currKeyPos) ||
                            (direction == 1 && next1KeyPos > currKeyPos)) //left连续下行 或 right连续上行
                        {
                            kuozhiFinger = kuozhiFingerArr[0];
                            isMust = 1;
                        } else {
                            kuozhiFinger = kuozhiFingerArr[kuozhiFingerLen - 1];
                        }
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
                        kuozhiFingerArr[kuozhiFingerLen] = i;
                        kuozhiFingerLen++;
                    }
                }

                //筛选
                if (kuozhiFingerLen > 0) {
                    kuozhiFinger = kuozhiFingerArr[0];
                }
            }

            //筛选
            if (kuozhiFinger != -1 && isMatch != -1) {
//					Debug.Log("扩指 同时匹配: "+isMatch +"=== pervFinger = "+ prevFinger+ "=== pre = "+prevKeyPos +"=== curr = "+currKeyPos + "=== next = "+next1KeyPos + "=== kuozhiFinger ="+kuozhiFinger +"=== matchFinger"+matchFinger);
                if (isMatch == 0) //同时匹配顺指
                {
                    if (direction == 0) //left
                    {
                        if (!(matchFinger == 4 &&
                              next1KeyPos < currKeyPos))//当前顺指匹配4指，但是next大于4指，所以只能用扩指，不用顺指
                        {
                            if (kuozhiFinger == 2 || kuozhiFinger == 3) {
                                kuozhiFinger = -1;
                            }

                            if (kuozhiFinger == 1) {
                                if (prevFinger != 0) {
                                    kuozhiFinger = -1;
                                }
                            }
                        }
                    } else {
                        if (!(matchFinger == 4 && next1KeyPos > currKeyPos)) {
                            if (kuozhiFinger == 2 || kuozhiFinger == 3) {
                                kuozhiFinger = -1;
                            }

                            if (kuozhiFinger == 1) {
                                if (prevFinger != 0) {
                                    kuozhiFinger = -1;
                                }
                            }
                        }
                    }
                } else {
                    if (kuozhiFinger == 2 || kuozhiFinger == 3) //不常用
                    {
                        kuozhiFinger = -1;
                    }

                    if (kuozhiFinger == 1) {
                        if (prevFinger != 0)//不常用
                        {
                            kuozhiFinger = -1;
                        }
                    }
                }

                if (next1KeyPos == -1) //最后一个键
                {
                    kuozhiFinger = -1;
                }
            }
        }
    }

    return kuozhiFinger;
}

/**
	 *  缩指是为了往反方向走
	 */
int matchSuoZhi(int index, int direction, int prevFinger, int prevKeyPos, int currKeyPos,
                int next1KeyPos, int next2KeyPos, int mode, int isMatch) {
    int suozhiFinger = -1;
    int suozhiFingerLen = 0;
    int suozhiFingerArr[4] = {0};
    int keyOffset = 0;


    if (next1KeyPos == -1) {
        return -1;
    }
    if ((mode == direction && prevFinger != 4) || (mode != direction && prevFinger != 0)) {
        keyOffset = getKeyInterval(prevKeyPos, currKeyPos);
        if (direction == mode) {
            for (int i = prevFinger + 1; i < 5; i++) {
                if (keyOffset < i - prevFinger) //琴键间隔小于手指间隔
                {
                    suozhiFingerArr[suozhiFingerLen] = i;
                    suozhiFingerLen++;
                }
            }

            if (suozhiFingerLen > 0) {
                //筛选
                if ((direction == 0 && next1KeyPos > prevKeyPos) ||
                    (direction == 1 && next1KeyPos < prevKeyPos)) //left next上行 或 right next下行
                {
                    suozhiFinger = suozhiFingerArr[suozhiFingerLen - 1]; //一般是4指
                } else if (next1KeyPos == prevKeyPos) {
                    if (next2KeyPos != -1) {
                        if (direction == 0) {
                            if (next2KeyPos > prevKeyPos) {
                                suozhiFinger = suozhiFingerArr[suozhiFingerLen - 1]; //一般是4指
                            }
                        } else {
                            if (next2KeyPos < prevKeyPos) {
                                suozhiFinger = suozhiFingerArr[suozhiFingerLen - 1]; //一般是4指
                            }
                        }
                    }
                } else {
                    //todo
                }
            }
        } else {
            for (int i = 0; i < prevFinger; i++) {
                if (keyOffset < prevFinger - i)//琴键间隔小于手指间隔
                {
                    suozhiFingerArr[suozhiFingerLen] = i;
                    suozhiFingerLen++;
                }
            }

            if (suozhiFingerLen > 0) {
                //筛选
                if ((direction == 0 && next1KeyPos < prevKeyPos) ||
                    (direction == 1 && next1KeyPos > prevKeyPos)) //left next下行 或 right next上行
                {
                    suozhiFinger = suozhiFingerArr[0]; //一般是1指
                } else if (next1KeyPos == prevKeyPos) {
                    if (next2KeyPos != -1) {
                        if (direction == 0) {
                            if (next2KeyPos < prevKeyPos) {
                                suozhiFinger = suozhiFingerArr[suozhiFingerLen - 1]; //一般是4指
                            }
                        } else {
                            if (next2KeyPos > prevKeyPos) {
                                suozhiFinger = suozhiFingerArr[suozhiFingerLen - 1]; //一般是4指
                            }
                        }
                    }
                } else {
                    //todo
                }
            }
        }

        if (suozhiFinger != -1 && isMatch != -1) {
            if (suozhiFinger != 0 && suozhiFinger != 4) {
                suozhiFinger = -1;
            }

//				Debug.Log("缩指 同时匹配: " + isMatch + "=== pervFinger = "+ prevFinger+ "=== pre = "+prevKeyPos +"=== curr = "+currKeyPos + "=== next = "+next1KeyPos + "=== kuozhiFinger =" + suozhiFinger);
        }
    }

    return suozhiFinger;
}


int calStartFinger(int keySize, int *keyIndexArr, int index, int direction) {
    int startFinger = -1;
    int currPos = -1;
    int next1 = -1;
    int next2 = -1;

    int max = 0;
    int min = 999;
    int count = 0;

    currPos = keyIndexArr[index];
    if (index + 1 < keySize) {
        next1 = keyIndexArr[index + 1];
    }

    if (index + 2 < keySize) {
        next2 = keyIndexArr[index + 2];
    }

    for (int i = index; i < keySize; i++) {
        int tempMin = min;
        int tempMax = max;

        if (keyIndexArr[i] > max) {
            tempMax = keyIndexArr[i];
        }

        if (keyIndexArr[i] < min) {
            tempMin = keyIndexArr[i];
        }

        if (getKeyInterval(tempMax, tempMin) > 5) {
            break;
        } else {
            max = tempMax;
            min = tempMin;
        }
        count++;
    }

    if (count >= 2) {
        if (direction == 0) {
            startFinger = getPostionForWhiteKey(max) - getPostionForWhiteKey(currPos);
        } else {
            startFinger = getPostionForWhiteKey(currPos) - getPostionForWhiteKey(min);
        }
//			Debug.Log("顺指start");
    } else {
        if (direction == 0) //左手
        {
            if (currPos > next1 && currPos > next2) //最右
            {
                startFinger = 1; //食指
            } else if (currPos < next1 && currPos < next2) //最左
            {
                startFinger = 4; //小指
            } else //中间
            {
                startFinger = 2;
            }
        } else {
            if (currPos > next1 && currPos > next2) //最右
            {
                startFinger = 4; //小指
            } else if (currPos < next1 && currPos < next2) //最左
            {
                startFinger = 1; //食指
            } else //中间
            {
                startFinger = 2;
            }
        }
    }

    return startFinger;
}


Boolean checkIsOutOf(int index1, int index2, int du) {
    int ret = FALSE;
    int m = 0;
    int n = 0;
    int offset = 0;

    if (index1 == index2) {
        offset = 0;
    } else {
        for (int i = 0; i < whitekeysSize; i++) {
            int whiteKey = whiteKeyIndexArr[i];

            if (whiteKey >= index1 && m == 0) {
                m = i;
            }

            if (whiteKey >= index2 && n == 0) {
                n = i;
            }

            if (m != 0 && n != 0) {
                break;
            }
        }
        offset = abs(m - n) + 1;
    }

    if (offset > du) {
        ret = TRUE;
    }
//		Debug.Log(index1+"==="+index2+"==="+du+"==="+ret);

    return ret;
}

Boolean isBlackKey(int index) {
    int ret = FALSE;
    int size = blackkeysSize;
    for (int i = 0; i < size; ++i) {

        if (index == blackKeyIndexArr[i]) {

            ret = TRUE;
            break;
        }

    }

    return ret;
}

Boolean isWhiteKey(int index) {
    int ret = FALSE;
    int size = whitekeysSize;
    for (int i = 0; i < size; ++i) {

        if (index == whiteKeyIndexArr[i]) {

            ret = TRUE;
            break;
        }

    }

    return ret;
}


int mallocIntArray(int **array, int size) {
    int ret = 1;

    if (*array == NULL) {
        *array = (int *) malloc(sizeof(int) * size);
        memset(*array, 0, sizeof(int) * size);
    } else {


        ret = 0;
    }


    return ret;

}

void freeIntArray(int **array) {

    if (*array != NULL) {

        free(*array);
        *array = NULL;
    }


}

void trimEmpty(int *p) {




}







