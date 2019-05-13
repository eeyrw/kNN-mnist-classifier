#include <stdio.h>
#include "MnistLoader.h"

int main(void)
{
    MNIST_CHAR* mnistCharList;
    mnistCharList=MnistLoad("./dataSet/train-images.idx3-ubyte","./dataSet/train-labels.idx1-ubyte");
    return 0;
}
