//
// Created by 77915 on 2019/7/2.
//

#include "ChordFingerProcess.h"


int *chordFingerProcess(int *keyPosArr, int direction) {
    Boolean isValidData = TRUE;
    int keyOffset = -1;

    int keyPosLen = getElementSize(keyPosArr);
    int *fingerArr = NULL;
    //检查合法性
    if (keyPosLen > 6) {
        isValidData = FALSE;
    } else if (getKeyInterval(keyPosArr[0], keyPosArr[keyPosLen - 1]) > 8) {
        isValidData = FALSE;
    }


    if (isValidData == 1) {
        /*fingerArr = malloc(sizeof(int) * keyPosLen);
        memset(fingerArr, 0, sizeof(int) * keyPosLen);*/
        mallocIntArray(&fingerArr,keyPosLen);
        if (keyPosLen == 6) {
            //大拇指按两个键
            if (direction == 0 && getKeyInterval(keyPosArr[4], keyPosArr[5]) <= 2) {
                fingerArr[0] = 0;
                fingerArr[1] = 0;
                fingerArr[2] = 1;
                fingerArr[3] = 2;
                fingerArr[4] = 3;
                fingerArr[5] = 4;
            } else if (direction == 0 && getKeyInterval(keyPosArr[0], keyPosArr[1]) <= 2) {
                fingerArr[0] = 4;
                fingerArr[1] = 3;
                fingerArr[2] = 2;
                fingerArr[3] = 1;
                fingerArr[4] = 0;
                fingerArr[5] = 0;
            } else {
                freeIntArray(&fingerArr);
            }
        } else if (keyPosLen == 5) {
            for (int i = 0; i < 5; i++) {
                if (direction == 0) {
                    fingerArr[i] = i;
                } else {
                    fingerArr[i] = 4 - i;
                }
            }
        } else if (keyPosLen == 2) {
            keyOffset = getKeyInterval(keyPosArr[0], keyPosArr[keyPosLen - 1]);
            if (keyOffset >= 5) {
                if (direction == 0) {
                    fingerArr[0] = 4;
                    fingerArr[1] = 0;
                } else {
                    fingerArr[0] = 0;
                    fingerArr[1] = 4;
                }
            } else {
                if (isBlackKey(keyPosArr[0]) && isBlackKey(keyPosArr[1])) {
                    if (keyOffset <= 2) {
                        if (direction == 0) {
                            fingerArr[0] = 2;
                            fingerArr[1] = 1;
                        } else {
                            fingerArr[0] = 1;
                            fingerArr[1] = 2;
                        }
                    } else {
                        if (direction == 0) {
                            fingerArr[0] = 3;
                            fingerArr[1] = 1;
                        } else {
                            fingerArr[0] = 1;
                            fingerArr[1] = 3;
                        }
                    }
                } else {
                    if (direction == 0) {
                        fingerArr[0] = keyOffset;
                        fingerArr[1] = 0;
                    } else {
                        fingerArr[0] = 0;
                        fingerArr[1] = keyOffset;
                    }
                }
            }
        } else {
            if (direction == 0) {
                fingerArr[0] = 4;
                fingerArr[keyPosLen - 1] = 0;
            } else {
                fingerArr[0] = 0;
                fingerArr[keyPosLen - 1] = 4;
            }

            if (getKeyInterval(keyPosArr[0], keyPosArr[keyPosLen - 1]) > 5) //音程大于5
            {
                if (keyPosLen == 3) {
                    if (getKeyInterval(keyPosArr[0], keyPosArr[1]) <= 2) {
                        if (direction == 0) {
                            fingerArr[1] = 3;
                        } else {
                            fingerArr[1] = 1;
                        }
                    } else if (getKeyInterval(keyPosArr[2], keyPosArr[1]) <= 2) {
                        if (direction == 0) {
                            fingerArr[1] = 1;
                        } else {
                            fingerArr[1] = 3;
                        }
                    } else {
                        fingerArr[1] = 2;
                    }
                } else if (keyPosLen == 4) {
                    int offset1 = abs(keyPosArr[0] - keyPosArr[1]);
                    int offset2 = abs(keyPosArr[1] - keyPosArr[2]);
                    int offset3 = abs(keyPosArr[2] - keyPosArr[3]);

                    if (offset1 > offset2 && offset1 > offset3) //4210 0234
                    {
                        if (direction == 0) {
                            fingerArr[1] = 2;
                            fingerArr[2] = 1;
                        } else {
                            fingerArr[1] = 2;
                            fingerArr[2] = 3;
                        }
                    } else if (offset2 > offset1 && offset2 > offset3) //4310 0134
                    {
                        if (direction == 0) {
                            fingerArr[1] = 3;
                            fingerArr[2] = 1;
                        } else {
                            fingerArr[1] = 1;
                            fingerArr[2] = 3;
                        }
                    } else if (offset3 > offset2 && offset3 > offset1) //4320 0124
                    {
                        if (direction == 0) {
                            fingerArr[1] = 3;
                            fingerArr[2] = 2;
                        } else {
                            fingerArr[1] = 1;
                            fingerArr[2] = 2;
                        }
                    } else {
                        //4210 0234
                        if (direction == 0) {
                            fingerArr[1] = 2;
                            fingerArr[2] = 1;
                        } else {
                            fingerArr[1] = 1;
                            fingerArr[2] = 2;
                        }
                    }
                }
            } else {
                for (int i = 1; i < keyPosLen; i++) {
                    int offset = getKeyInterval(keyPosArr[0], keyPosArr[i]) - 1;

                    if (direction == 0) {
                        fingerArr[i] = 4 - offset;
                    } else {
                        fingerArr[i] = 0 + offset;
                    }
                }
            }
        }
    }

    return fingerArr;
}