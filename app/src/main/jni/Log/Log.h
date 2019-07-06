//
// Created by mac on 2017/10/30.
//

#ifndef MYAPPLICATION3_LOG_H
#define MYAPPLICATION3_LOG_H

#include <android/log.h>
#define LOG_TAG "kali"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#endif //MYAPPLICATION3_LOG_H
