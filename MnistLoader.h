#ifndef __MNIST_LOADER_H__
#define __MNIST_LOADER_H__

#include <stdint.h>

#define CHAR_W 28
#define CHAR_H 28

typedef struct _MNIST_CHAR
{
    uint8_t pixels[CHAR_W*CHAR_H];
    uint8_t label;
}MNIST_CHAR;


extern MNIST_CHAR* MnistLoad(char* dataSetPath,char* dataLabelPath);
extern int MnistFree(MNIST_CHAR* charImages);

#endif
