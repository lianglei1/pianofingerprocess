//
// Created by mac on 2017/10/30.
//


#include "CalMain/CalModule.h"
#include "../Log/Log.h"
#include "logicMain/SingleFingerMain.h"
#include "logicMain/ChordFingerProcess.h"


#ifndef FINGERPIANO_FINGERPIANOMAIN_H

#define FINGERPIANO_FINGERPIANOMAIN_H


#endif //FINGERPIANO_FINGERPIANOMAIN_H

#define  MAXKEY_NUM 6
struct Entity {
    Node *fingerIndexArrArr;
    Node *keyIndexArrArr;
    /**
	 *  和弦：0合法，1不合法
	 * 	单指：0抬手  指法：1-5 顺、穿、跨、扩、缩
	 */
    int *statusArr;
    int statusArrSize;
    int *beatRenderIndexArr;

};

typedef struct Entity FingerEntity;


FingerEntity *mainProcess(Node *pitchArrArr, int beatRenderIndexArr[], int direction);