#ifndef __KNN_H__
#define __KNN_H__
#include <stdint.h>
#include "MnistLoader.h"
extern uint8_t KnnFit(MNIST_CHAR_LIST* trainDataList,MNIST_CHAR* testChar,int kNb);

typedef struct _RESULT_PAIR
{
    uint32_t index;
    uint32_t distance;
}RESULT_PAIR;

#endif // __KNN_H__
