#ifndef __KNN_H__
#define __KNN_H__
#include <stdint.h>
#include "MnistLoader.h"

#ifdef __cplusplus
extern "C"
{
#endif
extern uint8_t KnnFit(MNIST_CHAR_LIST* trainDataList,MNIST_CHAR* testChar,int kNb);

typedef struct _RESULT_PAIR
{
    uint32_t index;
    uint32_t distance;
    uint32_t label;
    uint32_t occurTimes;
}RESULT_PAIR;

#ifdef __cplusplus
}
#endif

#endif // __KNN_H__
