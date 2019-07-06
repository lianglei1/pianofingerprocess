//
// Created by 77915 on 2019/7/1.
//

#ifndef FINGERPIANO_GLOBALDATA_H


#define FINGERPIANO_GLOBALDATA_H

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

 static int blackKeyIndexArr[] = {1, 4, 6, 9, 11, 13, 16, 18, 21, 23, 25, 28, 30, 33, 35, 37, 40, 42,
                                45,
                                47, 49, 52, 54, 57, 59, 61, 64, 66, 69, 71, 73, 76, 78, 81, 83, 85};

 static int whiteKeyIndexArr[] = {0, 2, 3, 5, 7, 8, 10, 12, 14, 15, 17, 19, 20, 22, 24, 26, 27, 29,
                                31, 32,
                                34, 36, 38, 39, 41, 43, 44, 46, 48, 50, 51, 53, 55, 56, 58, 60, 62,
                                63,
                                65, 67, 68, 70, 72, 74, 75, 77, 79, 80, 82, 84, 86, 87};

 static int blackkeysSize = ARRAY_SIZE(blackKeyIndexArr);

 static int whitekeysSize = ARRAY_SIZE(whiteKeyIndexArr);

#define TRUE 1;
#define FALSE 0;
typedef int Boolean;


#endif //FINGERPIANO_GLOBALDATA_H


